from zappy_ia.Client import Client
from zappy_ia.Log import LogGood
from typing import List, Tuple
from typing import Union
from zappy_ia.Enums import Message, Element, Command


class ClientManager:
    def __init__(
        self, port: int, machineName: str, teamName: str, id: int, log: LogGood
    ):
        self._teamName: str = teamName
        self._log: LogGood = log
        self._id: int = id
        self._client: Client = Client(port, machineName)
        self.connect()

    def stopClient(self):
        self._client.stopClient

    def output(self) -> str:
        res = self._client.output()
        return res

    def connect(self):
        res = self.output()
        while res != "WELCOME\n":
            res = self.output()
            pass
        self._log.info("Received: " + res)
        resSetup = self.requestClient(self._teamName + "\n").split("\n")
        self._log.info("Received: " + resSetup[0] + "\n")
        if resSetup[0] == "ko":
            self.stopClient()
            raise Exception("Team name already taken")
        resSetup = self.waitOutput()
        self._log.info("Received: " + resSetup)

    def isIdInList(self, list_: List[int], toFindId: int) -> bool:
        for id_ in list_:
            if toFindId == id_:
                return True
        return False

    def isMyIdInList(self, list_: List[int]) -> bool:
        return self.isIdInList(list_, self._id)

    def checkBroadcast(self) -> List[Tuple[int, str, List[int], int]]:
        """
        This function is call to get received broadcast since last get,
            check if client received broadcast from other ia, parse and return it

        Returns:
        List of parsed broadcast List[[senderId, message, targets, dir]]
        """
        outList: List[str] = self._client.outputBroadcast()
        if len(outList) == 0:
            return []
        resList: List[Tuple[int, str, List[int], int]] = []
        for res in outList:
            res = res.split(",")
            direc = int(res[0].split(" ")[1])
            splittedRes = res[1].split("|")
            if len(splittedRes) != 4 or splittedRes[0].strip() != Message.CODE.value:
                continue
            toSend = list(map(int, splittedRes[3].strip().split(" ")))
            if toSend[0] != 0 and self.isMyIdInList(toSend) is False:
                continue
            resList.append((int(splittedRes[1]), splittedRes[2], toSend, direc))
        if len(resList) > 0:
            self._log.info("Received Broadcast:\n")
            for broadcast in resList:
                toSendStr = " ".join(map(str, broadcast[2]))
                self._log.info(
                    "    from: "
                    + str(broadcast[0])
                    + " : "
                    + broadcast[1]
                    + " to "
                    + toSendStr
                    + " dir: "
                    + str(broadcast[3])
                    + "\n"
                )
        return resList

    def checkBroadcastWithoutNewElevation(
        self,
    ) -> List[Tuple[int, str, List[int], int]]:
        """
        This function is call to get received broadcast since last get without new elevation broadcast,

        Returns:
        List of parsed broadcast List[[senderId, message, targets, dir]]
        """
        broadcasts = self.checkBroadcast()
        res: List[Tuple[int, str, List[int], int]] = []
        for broadcast in broadcasts:
            if broadcast[1].find(Message.L2.value[:-1]) == -1:
                res.append(broadcast)
            else:
                self.sendBroadcast(Message.KO.value, [broadcast[0]])
        return res

    def checkBroadcastResponse(self) -> Tuple[int, str, List[int], int]:
        liste = self.checkBroadcastWithoutNewElevation()
        if len(liste) == 0:
            return (0, "", [0], 0)
        return liste[0]

    def waitOutput(self) -> str:
        i = 0
        res = ""
        while res == "":
            res = self.output()
            i += 1
            if i > 15:
                self._log.debug("15 check without response")
                i = 0
        self._log.info("Received: " + res)
        return res

    def requestClient(
        self, command: Union[Command, str], arg: Union[Element, str] = ""
    ) -> str:
        """
        This function send command to the server, wait the response and return it

        Parameters:
        command (Union[Command, str]): command to send to the server,
            can be Command or str.

        Returns:
        Server response
        """
        toSend: str = ""
        argToSend: str = ""
        if isinstance(command, Command):
            toSend = command.value
        else:
            toSend = command
        if isinstance(arg, Element):
            argToSend = arg.value
        else:
            argToSend = arg
        self._log.info("[Send: " + toSend.split("\n")[0] + " " + argToSend + "]\n")
        self._client.input(toSend, argToSend)
        res = self.waitOutput()
        if res == "ko\n":
            toSendOrd = list(map(ord, toSend))
            argToSendOrd = list(map(ord, argToSend))
            self._log.info(
                "Server responded ko to : " + toSend + " " + argToSend)
            return "ko\n"
        return res

    def sendBroadcast(self, message: str, toSend: List[int] = []):
        toSendStr: str = "|"
        if len(toSend) == 0:
            toSendStr += "0"
        else:
            toSendStr += " ".join(map(str, toSend))
        codeStr: str = Message.CODE.value
        completeMessage: str = codeStr + "|" + str(self._id) + "|" + message + toSendStr
        self.requestClient(Command.BROADCAST, completeMessage)
