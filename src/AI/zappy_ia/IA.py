from enum import Enum
from typing import List, Tuple, Dict
from zappy_ia.Client import Client
from typing import Union
import zappy_ia.Log as log 
import pandas as pd
import time
import os
import joblib
import random
import sys
from zappy_ia.Client import Client
from zappy_ia.MessageEnum import Message


class Element(Enum):
    EMPTY = "empty"
    FOOD = "food"
    PLAYER = "player"
    LINEMATE = "linemate"
    DERAUMERE = "deraumere"
    SIBUR = "sibur"
    MENDIANE = "mendiane"
    PHIRAS = "phiras"
    THYSTAME = "thystame"


class Command(Enum):
    FORWARD = "Forward\n"
    RIGHT = "Right\n"
    LEFT = "Left\n"
    LOOK = "Look\n"
    INVENTORY = "Inventory\n"
    BROADCAST = "Broadcast"
    CONNECT_NBR = "Connect_nbr\n"
    FORK = "Fork\n"
    EJECT = "Eject\n"
    TAKE_OBJECT = "Take"
    SET_OBJECT = "Set"
    INCANTATION = "Incantation\n"


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


levelCosts: List[List[Tuple[Element, int]]] = [
    [(Element.LINEMATE, 1)],
    [(Element.LINEMATE, 1), (Element.DERAUMERE, 1), (Element.SIBUR, 1)],
    [(Element.LINEMATE, 2), (Element.SIBUR, 1), (Element.PHIRAS, 2)],
    [
        (Element.LINEMATE, 1),
        (Element.DERAUMERE, 1),
        (Element.SIBUR, 2),
        (Element.PHIRAS, 1),
    ],
    [
        (Element.LINEMATE, 1),
        (Element.DERAUMERE, 2),
        (Element.SIBUR, 1),
        (Element.MENDIANE, 3),
    ],
    [
        (Element.LINEMATE, 1),
        (Element.DERAUMERE, 2),
        (Element.SIBUR, 3),
        (Element.PHIRAS, 1),
    ],
    [
        (Element.LINEMATE, 2),
        (Element.DERAUMERE, 2),
        (Element.SIBUR, 2),
        (Element.MENDIANE, 2),
        (Element.PHIRAS, 2),
        (Element.THYSTAME, 1),
    ],
]


levelParticpantsNb: List[int] = [0, 0, 1, 1, 3, 3, 5, 5]


class IA:
    def __init__(self, port: int, machineName: str, teamName: str):
        self._port: int = port
        self._machineName: str = machineName
        self._teamName: str = teamName
        self.build(7)

    def build(self, neededChild: int = 0):
        self._neededChild = neededChild
        self._mapSize: Tuple[int, int] = (0, 0)
        self._clientNb: int = 0
        self._level: int = 1
        self._emitter: int = 0
        self._lastLook: List[List[Element]] = []
        self.setId()
        self._filename = f"log/{self._id}ia.log"
        log.configure_file(self._filename)
        self._client: Client = Client(self._port, self._id ,self._machineName)
        self._inputTree: Dict = {
            "mfood": [0],
            "mlinemate": [0],
            "mderaumere": [0],
            "msibur": [0],
            "mmendiane": [0],
            "mphiras": [0],
            "mthystame": [0],
            "lfood": [0],
            "llinemate": [0],
            "lderaumere": [0],
            "lsibur": [0],
            "lmendiane": [0],
            "lphiras": [0],
            "lthystame": [0],
            "enemy": [0],
        }

        self._outputTree: Dict = {
            "Find food": self.findFood,
            "Take food": self.takeFood,
            "Take linemate": self.takeLinemate,
            "Take deraumere": self.takeDeraumere,
            "Take sibur": self.takeSibur,
            "Take mendiane": self.takeMendiane,
            "Take phiras": self.takePhiras,
            "Take thystame": self.takeThystame,
            "Elevation": self.chooseElevation,
            "Fork": self.fork,
        }

        try:
            self._levelTree = joblib.load("src/AI/joblib/level1.joblib")
        except FileNotFoundError:
            raise Exception("Level not found")
        self.connect()
        self.run()

    def setId(self):
        self._id = random.randint(10000, 99999)

    def connect(self):
        while self._client.output() != "WELCOME\n":
            pass
        self._client.input(self._teamName + "\n")
        resSetup = ""
        while resSetup == "":
            resSetup = self._client.output()
        if resSetup == "ko\n":
            raise Exception("Team name already taken")
        elif len(resSetup.split("\n")) == 2:
            self._client.output()

    def loadTree(self):
        try:
            self._levelTree = joblib.load(
                "src/AI/joblib/level" + str(self._level) + ".joblib"
            )
        except FileNotFoundError:
            print("File joblib not found", file=sys.stderr)
            self._client.stopClient()
            sys.exit(84)

    def checkNeededChilds(self):
        while self._neededChild > 0:
            if int(self.requestClient(Command.CONNECT_NBR.value).split("\n")[0]) > 0:
                log.write_to_file(self._filename, "New child\n")
                self.connectNewIA()
            elif self._inputTree["mfood"][0] > 2:
                log.write_to_file(self._filename, "New egg\n")
                self.createEgg()
            else:
                break
            self._neededChild -= 1

    def run(self):
        continueRun = True
        try:
            while continueRun:
                self.checkElevationParticipant()
                self.inventory()
                self.checkNeededChilds()
                self.lookForTree()
                predictions = self._levelTree.predict(pd.DataFrame(self._inputTree))
                for prediction in predictions:
                    log.write_to_file(self._filename, "Pred: " + prediction + "\n")
                    self._outputTree[prediction]()
        except KeyboardInterrupt:
            self._client.stopClient()
            return

    def checkElevationParticipant(self):
        broadcasts: List[Tuple[int, str, List[int], int]] = self.checkBroadcast()
        response: List[int] = []
        if len(broadcasts) == 0:
            return
        for broadcast_ in broadcasts:
            if (
                broadcast_[1][:-1] == "levelup"
                and self._emitter == 0
                and int(broadcast_[1][-1]) == self._level
            ):
                self._emitter = broadcast_[0]
                response.append(broadcast_[0])
                self.sendBroadcast(Message.OK.value, [self._emitter])
            elif broadcast_[0] in response:
                continue
            else:
                response.append(broadcast_[0])
                self.sendBroadcast(Message.KO.value, [broadcast_[0]])
        if self._emitter != 0:
            self.elevationParticipant()
        return

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
            log.write_to_file(
                    self._filename,
                    "Received broadcast from :"
                    + str(splittedRes[1])
                    + " : "
                    + splittedRes[2]
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
        res = ""
        while res == "":
            res = self._client.output()
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
        self._client.input(toSend, argToSend)
        res = self.waitOutput()
        if res == "ko":
            raise Exception("Server responsed ko to : " + toSend)
        return res

    def inventory(self):
        """
        This function send the inventory command to the server and
            parse response in self._inputTree which is List
        """
        res = self.requestClient(Command.INVENTORY)
        try:
            res = res.split("[")[1].split("]")[0]
        except IndexError:
            print(f"ID : {self._id}")
            self._client.stopClient()
            return

        for elem in res.split(","):
            parsedElem = elem.strip().split(" ")
            self._inputTree["m" + parsedElem[0]][0] = int(parsedElem[1])

    def lookForTree(self):
        """
        This function get the list of the closest items on the look to
            put in self._inputTree
        """
        self.look()
        for elem in Element:
            if "l" + elem.value in self._inputTree.keys():
                case = self.findClosestElemInLastLook(elem)
                self._inputTree["l" + elem.value][0] = 1 if case >= 0 else 0
        case = self.findClosestElemInLastLook(Element.PLAYER)
        self._inputTree["enemy"][0] = 1 if case >= 0 else 0

    def look(self):
        """
        This function send the look command to the server and parse response in
            self._lastLook which is List[List[Element]]
        """
        self._lastLook.clear()

        res = self.requestClient(Command.LOOK)
        try:
            res = res.split("[")[1].split("]")[0]
        except IndexError:
            print(f"ID : {self._id}")
            self._client.stopClient()
            return

        i = 0
        for tile in res.split(","):
            self._lastLook.append([])
            for elem in tile.split(" "):
                if elem == "":
                    self._lastLook[i].append(Element.EMPTY)
                else:
                    self._lastLook[i].append(Element(elem))
            i += 1

    def pathFinding(self, pos: int):
        """
        This function move the ia to the pos in parameters

        Parameters:
        pos (int): pos which represent an index in the array of tile return
            by server to command look
        """
        if pos <= 0:
            return
        for i in range(1, 9):
            self.requestClient(Command.FORWARD)
            mid = i * (i + 1)
            if mid == pos:
                return
            if mid - i <= pos and pos < mid:
                self.requestClient(Command.LEFT)
                for _ in range(mid - pos):
                    self.requestClient(Command.FORWARD)
                return
            if mid + i >= pos and pos > mid:
                self.requestClient(Command.RIGHT)
                for _ in range(pos - mid):
                    self.requestClient(Command.FORWARD)
                return

    def takeElement(self, element: Element, pos: int):
        """
        This function move the ia to the pos of the element and pick it up

        Parameters:
        element (Element): element to take
        pos (int): pos (in front of the ia) of the element
        """
        if pos < 0:
            return
        self.pathFinding(pos)
        self.requestClient(Command.TAKE_OBJECT, element)
    
    def connectNewIA(self):
        self.pid = os.fork()
        if self.pid == 0:
            self._client.stopClient()
            self.build(0)
        time.sleep(0.5)

    def createEgg(self):
        self.requestClient(Command.FORK.value)
        self.connectNewIA()

    def takeElementInLastLook(self, element: Element, pos: int):
        """
        This function move the ia to the pos of the element and pick it up

        Parameters:
        element (Element): element to take
        pos (int): pos (in front of the ia) of the element
        """
        if pos < 0:
            return
        self.pathFinding(pos)
        self.requestClient(Command.TAKE_OBJECT, element)

    def takeFood(self):
        self.takeElement(Element.FOOD, self.findClosestElemInLastLook(Element.FOOD))

    def takeLinemate(self):
        self.takeElement(
            Element.LINEMATE, self.findClosestElemInLastLook(Element.LINEMATE)
        )

    def takeDeraumere(self):
        self.takeElement(
            Element.DERAUMERE, self.findClosestElemInLastLook(Element.DERAUMERE)
        )

    def takeSibur(self):
        self.takeElement(Element.SIBUR, self.findClosestElemInLastLook(Element.SIBUR))

    def takeMendiane(self):
        self.takeElement(
            Element.MENDIANE, self.findClosestElemInLastLook(Element.MENDIANE)
        )

    def takePhiras(self):
        self.takeElement(Element.PHIRAS, self.findClosestElemInLastLook(Element.PHIRAS))

    def takeThystame(self):
        self.takeElement(
            Element.THYSTAME, self.findClosestElemInLastLook(Element.THYSTAME)
        )

    def fork(self):
        print("Forking")

    def findClosestElemInLastLook(
        self, element: Element, checkCurrentTile: bool = True
    ) -> int:
        """
        This function find closest elem in last look and return it pos

        Parameters:
        element (Element): elem to find pos
        """
        lastLook = self._lastLook
        i = 0
        if checkCurrentTile is False:
            lastLook = lastLook[1:]
            i = 1
        for tile in lastLook:
            for elem in tile:
                if elem == element:
                    return i
            i += 1
        return -1

    def findFood(self, distanceLimit: int = 0):
        """
        This function find and take the closest food in other directions
            than the current, because it will be call when ia need food
            and don't see any in last look this function is call when
            ia need to survive and don't care of other items

        Parameters:
        distanceLimit (int): is the id of the last line where we can go take food,
            after it's too far away. 0 if no limit
        """
        i = 1
        pos = -1
        while pos == -1:
            self.requestClient(Command.RIGHT)
            self.look()
            pos = self.findClosestElemInLastLook(Element.FOOD)
            if distanceLimit != 0 and i > distanceLimit:
                self.findFood(distanceLimit)
            elif pos != -1:
                self.takeElement(Element.FOOD, pos)
            i += 1

    def chooseElevation(self):
        if self._level == 1:
            self.elevation()
        else:
            self.elevationEmitter()

    def elevation(self):
        for costTuple in levelCosts[self._level - 1]:
            if costTuple[1] > self._inputTree["m" + costTuple[0].value][0]:
                return
            for _ in range(costTuple[1]):
                self.requestClient(Command.SET_OBJECT, costTuple[0].value)
        self.requestClient(Command.INCANTATION)
        out = ""
        while out == "":
            out = self._client.output()
        if out != Message.KO.value + "\n":
            self._level += 1
            self.loadTree()

    def sendBroadcast(self, message: str, toSend: List[int] = []):
        toSendStr: str = "|"
        if len(toSend) == 0:
            toSendStr += "0"
        else:
            for id_ in toSend:
                toSendStr += " " + str(id_)
        codeStr: str = Message.CODE.value
        completeMessage: str = codeStr + "|" + str(self._id) + "|" + message + toSendStr + "\n"
        self.requestClient(Command.BROADCAST, completeMessage)

    def isMyIdInList(self, list_: List[int]) -> bool:
        for id_ in list_:
            if self._id == id_:
                return True
        return False

    def takeClosestFood(self):
        self.look()
        foodPos = self.findClosestElemInLastLook(Element.FOOD)
        if foodPos == -1:
            self.findFood()
        else:
            self.takeElement(Element.FOOD, foodPos)
        self.inventory()

    def sendAllCommand(self, messages: List[str]):
        for message in messages:
            self.requestClient(message)

    def joinEmitter(self):
        res = self.checkBroadcastResponse()
        while res[1] != "come":
            res = self.checkBroadcastResponse()
        while res[3] != 0 and res[1] == "come":
            self.sendAllCommand(cmdDirections[res[3]])
            res = self.checkBroadcastResponse()
            while res[1] != "come":
                res = self.checkBroadcastResponse()
        self.look()
        self.sendBroadcast(Message.OK.value, [self._emitter])
        out = self._client.output()
        while out == "":
            out = self._client.output()
        if out == "ko\n":
            self._emitter = 0
            return
        out = ""
        while out == "":
            out = self._client.output()
        if out == "ko\n":
            self._emitter = 0
        else:
            self._emitter = 0
            self._level += 1
            self.loadTree()
        return

    def elevationParticipant(self):
        res = self.checkBroadcastResponse()
        while res[1] == "":
            res = self.checkBroadcastResponse()
        if res[1] == Message.KO.value:
            self._emitter = 0
            return
        haveToCome = False
        ready = False
        while haveToCome is False or ready is False:
            self.takeClosestFood()
            if self._inputTree["mfood"][0] >= 13 and ready is False:
                ready = True
                self.sendBroadcast(Message.OK.value, [self._emitter])
            res = self.checkBroadcastResponse()
            if res[1] == Message.COME.value:
                haveToCome = True
        self.joinEmitter()

    def checkReceivedMessage(
        self, participantsId: List[int], res: Tuple[int, str, List[int], int]
    ) -> List[int]:
        if res[1] == Message.OK.value:
            if len(participantsId) < levelParticpantsNb[self._level]:
                participantsId.append(res[0])
                self.sendBroadcast(Message.OK.value, [res[0]])
            else:
                self.sendBroadcast(Message.KO.value, [res[0]])
        return participantsId

    def waitParticipants(self, participantsId: List[int]):
        readyParticipants = 0
        self.inventory()
        res: List[Tuple[int, str, List[int], int]] = []
        while (
            readyParticipants < levelParticpantsNb[self._level]
            or self._inputTree["mfood"][0] < 13
        ):
            self.takeClosestFood()
            res = self.checkBroadcastWithoutNewElevation()
            for mess in res:
                if (
                    mess[0] != 0
                    and self.isMyIdInList(mess[2])
                    and mess[1] == Message.OK.value
                ):
                    readyParticipants += 1
            self.inventory()
        arrivedParticipants = 0
        while arrivedParticipants < levelParticpantsNb[self._level]:
            self.sendBroadcast(Message.COME.value, participantsId)
            res = self.checkBroadcastWithoutNewElevation()
            for mess in res:
                if mess[1] == Message.OK.value:
                    arrivedParticipants += 1
        self.elevation()

    def elevationEmitter(self):
        """
        This function is call by decision tree when the ia have the stones for elevation,
            the ia call others to try elevation
        """
        self.sendBroadcast(list(Message)[self._level].value)
        participantsId: List[int] = []
        res: List[Tuple[int, str, List[int], int]] = []
        while len(participantsId) != levelParticpantsNb[self._level]:
            res = self.checkBroadcastWithoutNewElevation()
            for mess in res:
                participantsId = self.checkReceivedMessage(participantsId, mess)
        self.waitParticipants(participantsId)
