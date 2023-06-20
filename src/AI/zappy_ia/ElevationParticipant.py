from zappy_ia.Log import LogGood
from typing import Dict, List, Tuple
from zappy_ia.Enums import Message, ServerRes
from zappy_ia.ClientManager import ClientManager
from zappy_ia.DecisionTree import DecisionTree

cmdDirections: Dict = {
    0: [],
    1: ["Forward\n"],
    2: ["Forward\n", "Left\n", "Forward\n"],
    3: ["Left\n", "Forward\n"],
    4: ["Left\n", "Forward\n", "Left\n", "Forward\n"],
    5: ["Right\n", "Right\n", "Forward\n"],
    6: ["Right\n", "Forward\n", "Right\n", "Forward\n"],
    7: ["Right\n", "Forward\n"],
    8: ["Forward\n", "Right\n", "Forward\n"],
}


class ElevationParticipant:
    def __init__(
        self, clientManager: ClientManager, decisionTree: DecisionTree, log: LogGood
    ):
        self._emitter: int = 0
        self._log = log
        self._clientManager: ClientManager = clientManager
        self._decisionTree: DecisionTree = decisionTree

    def errorReturn(self) -> bool:
        self._emitter = 0
        return False

    def sendAllCommand(self, messages: List[str]):
        self._log.debug("sendAllCommand start")
        for message in messages:
            self._clientManager.requestClient(message)
        self._log.debug("sendAllCommand end")

    def checkWaitNextLastOK(self) -> int:
        out = self._clientManager.output()
        if out == ServerRes.ELEVATION_UNDERWAY.value:
            out = self._clientManager.waitOutput()
            if out == ServerRes.KO.value:
                return 1
            else:
                self._emitter = 0
                return 2
        return 0

    def checkElevationResponse(self):
        self._clientManager.sendBroadcast(Message.OK.value, [self._emitter])
        res: Tuple(int, str, List[int], int) = [0, "", [0], 0]
        while res[1] != Message.KO.value:
            checkRes = self.checkWaitNextLastOK()
            if checkRes == 1:
                return self.errorReturn()
            elif checkRes == 2:
                return True
            res = self._clientManager.checkBroadcastResponse()
        return self.errorReturn()

    def joinEmitter(self) -> bool:
        receivedDir0 = 2
        res: Tuple(int, str, List[int], int) = [0, "", [0], 0]
        while receivedDir0 > 0:
            self._log.debug("join emitter, receivedDir0: " + str(receivedDir0))
            res = self._clientManager.checkBroadcastResponse()
            while res[1] != Message.COME.value:
                res = self._clientManager.checkBroadcastResponse()
            self._log.debug("res: " + res[1])
            if res[3] == 0:
                receivedDir0 -= 1
            elif receivedDir0 < 2 and res[3] != 0:
                receivedDir0 = 2
            self.sendAllCommand(cmdDirections[res[3]])
            self._decisionTree.takeFoodIfAtFeet()
            if self._decisionTree.getCurrentFood() < 8:
                self._decisionTree.takeClosestFood()

    def checkBroadcastEmitter(self) -> List[Tuple[int, str, List[int], int]]:
        broadcasts = self._clientManager.checkBroadcast()
        res: List[Tuple[int, str, List[int], int]] = []
        for mess in broadcasts:
            if mess[2][0] == 0:
                if mess[0] == self._emitter:
                    continue
                else:
                    self._clientManager.sendBroadcast(Message.KO.value, [mess[0]])
            elif mess[0] == self._emitter:
                res.append(mess)
            else:
                self._log.debug("weird message in check broadcast emitter: " + mess[1])
        return res

    def waitNextStep(self) -> bool:
        okNb = 0
        res: Tuple[int, str, List[int], int] = [0, "", [], 0]
        while okNb < 2:
            res = self.checkBroadcastEmitter()
            for mess in res:
                if mess[1] == Message.KO.value:
                    return False
                elif mess[1] == Message.OK.value:
                    okNb += 1
                else:
                    self._log.debug("weird message in wait next step: " + mess[1])
            self._decisionTree.takeClosestFood()
        return True

    def elevationParticipant(self) -> bool:
        if self.waitNextStep() is False:
            return self.errorReturn()
        haveToCome = False
        ready = False
        while haveToCome is False or ready is False:
            self._log.debug(
                "in havetocome loop, haveToCome: "
                + str(haveToCome)
                + " ,ready: "
                + str(ready)
            )
            self._decisionTree.takeClosestFood()
            if self._decisionTree.getCurrentFood() >= 13 and ready is False:
                ready = True
                self._clientManager.sendBroadcast(Message.OK.value, [self._emitter])
            res = self._clientManager.checkBroadcastResponse()
            if res[1] == Message.COME.value:
                haveToCome = True
        return self.joinEmitter()

    def checkElevationParticipant(self, currentLevel: int) -> bool:
        broadcasts: List[
            Tuple[int, str, List[int], int]
        ] = self._clientManager.checkBroadcast()
        response: List[int] = []
        if len(broadcasts) == 0:
            return self.errorReturn()
        for broadcast_ in broadcasts:
            if (
                broadcast_[1][:-1] == "levelup"
                and self._emitter == 0
                and int(broadcast_[1][-1]) == currentLevel
            ):
                self._emitter = broadcast_[0]
                response.append(broadcast_[0])
                self._clientManager.sendBroadcast(Message.OK.value, [self._emitter])
            elif broadcast_[0] in response:
                continue
            else:
                response.append(broadcast_[0])
                self._clientManager.sendBroadcast(Message.KO.value, [broadcast_[0]])
        if self._emitter != 0:
            return self.elevationParticipant()
        return self.errorReturn()
