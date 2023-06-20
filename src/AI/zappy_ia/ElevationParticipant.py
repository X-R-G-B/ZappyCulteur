from zappy_ia.Log import LogGood
from typing import Dict, List, Tuple
from zappy_ia.Enums import Message
from zappy_ia.ClientManager import ClientManager
from zappy_ia.DecisionTree import DecisionTree

cmdDirections: Dict = {
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
        for message in messages:
            self._clientManager.requestClient(message)

    def joinEmitter(self):
        res = self._clientManager.checkBroadcastResponse()
        while res[1] != "come":
            res = self._clientManager.checkBroadcastResponse()
        while res[3] != 0 and res[1] == "come":
            self.sendAllCommand(cmdDirections[res[3]])
            res = self._clientManager.checkBroadcastResponse()
            while res[1] != "come":
                res = self._clientManager.checkBroadcastResponse()
        self._clientManager.sendBroadcast(Message.OK.value, [self._emitter])
        out = self._clientManager.waitOutput()
        if out == "ko\n":
            return self.errorReturn()
        out = self._clientManager.waitOutput()
        if out != "ko\n":
            self._emitter = 0
            return True
        else:
            return self.errorReturn()

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
        if self.waitNextStep() == False:
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
