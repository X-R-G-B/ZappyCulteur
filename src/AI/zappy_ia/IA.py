from enum import Enum
from typing import List, Tuple
from typing import Union
import pandas as pd
import joblib
import random
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


class IA:
    def __init__(self, port: int, machineName: str, teamName: str):
        self.port: int = port
        self.machineName: str = machineName
        self.teamName: str = teamName
        self.mapSize: Tuple[int, int] = [0, 0]
        self.clientNb: int = 0
        self.level: int = 1
        self.setId()
        self.lastLook: List[List[Element]] = []
        self.client: Client = Client(port, machineName)
        self.emitter: int = 0
        self.levelParticipantsNb: List[int] = [0, 0, 1, 1, 3, 3, 5, 5]
        self.levelCosts: List[List[Tuple[Element, int]]] = [
            [[Element.LINEMATE, 1]],
            [[Element.LINEMATE, 1], [Element.DERAUMERE, 1], [Element.SIBUR, 1]],
            [[Element.LINEMATE, 2], [Element.SIBUR, 1], [Element.PHIRAS, 2]],
            [
                [Element.LINEMATE, 1],
                [Element.DERAUMERE, 1],
                [Element.SIBUR, 2],
                [Element.PHIRAS, 1],
            ],
            [
                [Element.LINEMATE, 1],
                [Element.DERAUMERE, 2],
                [Element.SIBUR, 1],
                [Element.MENDIANE, 3],
            ],
            [
                [Element.LINEMATE, 1],
                [Element.DERAUMERE, 2],
                [Element.SIBUR, 3],
                [Element.PHIRAS, 1],
            ],
            [
                [Element.LINEMATE, 2],
                [Element.DERAUMERE, 2],
                [Element.SIBUR, 2],
                [Element.MENDIANE, 2],
                [Element.PHIRAS, 2],
                [Element.THYSTAME, 1],
            ],
        ]
        self.inputTree: dict() = {
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
        self.outputTree: dict() = {
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
        self.cmdDirections: dict() = {
            1: ["Forward\n"],
            2: ["Forward\n", "Right\n"],
            3: ["Left\n", "Forward\n"],
            4: ["Left\n", "Forward\n", "Left\n", "Forward\n"],
            5: ["Right\n", "Right\n", "Forward\n"],
            6: ["Right\n", "Forward\n", "Right\n", "Forward\n"],
            7: ["Right\n", "Forward\n"],
            8: ["Forward\n", "Right\n", "Forward\n"],
        }
        try:
            self.levelTree = joblib.load("src/AI/joblib/level1.joblib")
        except FileNotFoundError:
            raise Exception("Level not found")
        self.connect()
        self.run()

    def setId(self):
        self.id = random.randint(10000, 99999)

    def connect(self):
        while self.client.output() != "WELCOME\n":
            pass
        self.client.input(self.teamName + "\n")
        resSetup = ""
        while resSetup == "":
            resSetup = self.client.output()
        if resSetup == "ko\n":
            raise Exception("Team name already taken")
        elif len(resSetup.split("\n")) == 2:
            self.client.output()

    def loadTree(self):
        try:
            self.levelTree = joblib.load(
                "src/AI/joblib/level" + str(self.level) + ".joblib"
            )
        except FileNotFoundError:
            raise Exception("Level not found")

    def run(self):
        continueRun = True
        try:
            while continueRun:
                self.checkElevationParticipant()
                self.inventory()
                self.lookForTree()
                predictions = self.levelTree.predict(pd.DataFrame(self.inputTree))
                for prediction in predictions:
                    print(prediction)
                    self.outputTree[prediction]()
        except KeyboardInterrupt:
            return

    def checkElevationParticipant(self):
        broadcasts: List[Tuple[int, str, List[int], int]] = self.checkBroadcast()
        response: List[int] = []
        if len(broadcasts) == 0:
            return
        for broadcast_ in broadcasts:
            if (
                broadcast_[1][:-1] == "levelup"
                and self.emitter == 0
                and int(broadcast_[1][-1]) == self.level
            ):
                self.emitter = broadcast_[0]
                response.append(broadcast_[0])
                self.sendBroadcast(Message.OK.value, [self.emitter])
            elif broadcast_[0] in response:
                continue
            else:
                response.append(broadcast_[0])
                self.sendBroadcast(Message.KO.value, [broadcast_[0]])
        if self.emitter != 0:
            self.elevationParticipant()
        return

    def checkBroadcast(self) -> List[Tuple[int, str, List[int], int]]:
        """
        This function is call to get received broadcast since last get,
            check if client received broadcast from other ia, parse and return it

        Returns:
        List of parsed broadcast List[[senderId, message, targets, dir]]
        """
        outList: List[str] = self.client.outputBroadcast()
        if len(outList) == 0:
            return []
        resList: List[Tuple[int, str, List[int], int]] = []
        for res in outList:
            res = res.split(",")
            dir_ = int(res[0].split(" ")[1])
            splittedRes = res[1].split("|")
            if len(splittedRes) != 4 or splittedRes[0].strip() != Message.CODE.value:
                continue
            toSend = list(map(int, splittedRes[3].strip().split(" ")))
            if toSend[0] != 0 and self.isMyIdInList(toSend) is False:
                continue
            resList.append([int(splittedRes[1]), splittedRes[2], toSend, dir_])
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
            return [0, "", [0], 0]
        return liste[0]

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
        self.client.input(toSend, argToSend)
        res = ""
        while res == "":
            res = self.client.output()
        return res

    def inventory(self):
        """
        This function send the inventory command to the server and
            parse response in self.inputTree which is List
        """
        res = self.requestClient(Command.INVENTORY)
        print(res)
        res = res.split("[")[1].split("]")[0]

        i = 1
        for elem in res.split(","):
            self.inputTree["m" + elem.split(" ")[1].strip()][0] = int(
                elem.split(" ")[2].strip()
            )
            i += 1

    def lookForTree(self):
        """
        This function get the list of the closest items on the look to
            put in self.inputTree
        """
        self.look()
        for elem in Element:
            if "l" + elem.value in self.inputTree.keys():
                case = self.findClosestElemInLastLook(elem)
                self.inputTree["l" + elem.value][0] = 1 if case >= 0 else 0
        case = self.findClosestElemInLastLook(Element.PLAYER)
        self.inputTree["enemy"][0] = 1 if case >= 0 else 0

    def look(self):
        """
        This function send the look command to the server and parse response in
            self.lastLook which is List[List[Element]]
        """
        self.lastLook.clear()

        res = self.requestClient(Command.LOOK)
        res = res.split("[")[1].split("]")[0]

        i = 0
        for tile in res.split(","):
            self.lastLook.append([])
            for elem in tile.split(" "):
                if elem == "":
                    self.lastLook[i].append(Element.EMPTY)
                else:
                    self.lastLook[i].append(Element(elem))
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
                for x in range(mid - pos):
                    self.requestClient(Command.FORWARD)
                return
            if mid + i >= pos and pos > mid:
                self.requestClient(Command.RIGHT)
                for x in range(pos - mid):
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
        lastLook = self.lastLook
        i = 0
        if checkCurrentTile is False:
            lastLook = lastLook.pop(0)
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
        if self.level == 1:
            self.elevation()
        else:
            self.elevationEmitter()

    def elevation(self):
        for costTuple in self.levelCosts[self.level - 1]:
            if costTuple[1] > self.inputTree["m" + costTuple[0].value][0]:
                return
            for i in range(costTuple[1]):
                self.requestClient(Command.SET_OBJECT, costTuple[0].value)
        self.requestClient(Command.INCANTATION)
        out = ""
        while out == "":
            out = self.client.output()
        if out != Message.KO.value + "\n":
            self.level += 1
            self.loadTree()

    def sendBroadcast(self, message: str, toSend: List[int] = []):
        toSendStr: str = "|"
        if len(toSend) == 0:
            toSendStr += "0"
        else:
            for id_ in toSend:
                toSendStr += " " + str(id_)
        codeStr: str = Message.CODE.value
        completeMessage: str = codeStr + "|" + str(self.id) + "|" + message + toSendStr
        self.requestClient(Command.BROADCAST, completeMessage)

    def isMyIdInList(self, list_: List[int]) -> bool:
        for id_ in list_:
            if self.id == id_:
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
            print("res[3] = " + str(res[3]))
            self.sendAllCommand(self.cmdDirections[res[3]])
            res = self.checkBroadcastResponse()
            while res[1] != "come":
                res = self.checkBroadcastResponse()
        self.look()
        self.sendBroadcast(Message.OK.value, [self.emitter])
        out = self.client.output()
        while out == "":
            out = self.client.output()
        if out == "ko\n":
            self.emitter = 0
            return
        out = ""
        while out == "":
            out = self.client.output()
        if out == "ko\n":
            self.emitter = 0
        else:
            self.emitter = 0
            self.level += 1
            self.loadTree()
        return

    def elevationParticipant(self):
        res = self.checkBroadcastResponse()
        while res[1] == "":
            res = self.checkBroadcastResponse()
        if res[1] == Message.KO.value:
            self.emitter = 0
            return
        haveToCome = False
        ready = False
        while haveToCome is False or ready is False:
            print("haveToCome = " + str(haveToCome) + " ready = " + str(ready))
            self.takeClosestFood()
            if self.inputTree["mfood"][0] >= 13 and ready is False:
                ready = True
                self.sendBroadcast(Message.OK.value, [self.emitter])
            res = self.checkBroadcastResponse()
            print("res[1] = " + res[1])
            if res[1] == Message.COME.value:
                haveToCome = True
        self.joinEmitter()

    def checkReceivedMessage(
        self, participantsId: List[int], res: Tuple[int, str, List[int], int]
    ) -> List[int]:
        if res[1] == Message.OK.value:
            if len(participantsId) < self.levelParticipantsNb[self.level]:
                participantsId.append(res[0])
                self.sendBroadcast(Message.OK.value, [res[0]])
            else:
                self.sendBroadcast(Message.KO.value, [res[0]])
        return participantsId

    def waitParticipants(self, participantsId: List[int]):
        readyParticipants = 0
        self.inventory()
        while (
            readyParticipants < self.levelParticipantsNb[self.level]
            or self.inputTree["mfood"][0] < 13
        ):
            self.takeClosestFood()
            res: Tuple[int, str, List[int], int] = self.checkBroadcastResponse()
            if res[0] != 0 and self.isMyIdInList(res[2]) and res[1] == Message.OK.value:
                readyParticipants += 1
            self.inventory()
        arrivedParticipants = 0
        while arrivedParticipants < self.levelParticipantsNb[self.level]:
            self.sendBroadcast(Message.COME.value, participantsId)
            res: Tuple[int, str, List[int], int] = self.checkBroadcastResponse()
            if res[1] == Message.OK.value:
                arrivedParticipants += 1
        self.elevation()

    def elevationEmitter(self):
        """
        This function is call by decision tree when the ia have the stones for elevation,
            the ia call others to try elevation
        """
        self.sendBroadcast(list(Message)[self.level].value)
        participantsId: List[int] = []
        res: Tuple[int, str, List[int]] = self.checkBroadcastResponse()
        while len(participantsId) != self.levelParticipantsNb[self.level]:
            res = self.checkBroadcastResponse()
            participantsId = self.checkReceivedMessage(participantsId, res)
        self.waitParticipants(participantsId)
