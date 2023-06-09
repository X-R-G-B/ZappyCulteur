from enum import Enum
from typing import List, Tuple
from zappy_ia.Client import Client
from typing import Union
import pandas as pd
import time
import joblib
import random


class Message(Enum):
    OK = "ok"
    KO = "ko"
    L2 = "levelup2"
    L3 = "levelup3"
    L4 = "levelup4"
    L5 = "levelup5"
    L6 = "levelup6"
    L7 = "levelup7"
    L8 = "levelup8"
    COME = "come"
    CODE = "*$+"


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
            self.levelTree = joblib.load("joblib/level1.joblib")
        except FileNotFoundError:
            raise Exception("Level not found")
        self.connect()
        self.run()

    def setId(self):
        self.id = random.randint(10000, 99999)

    def connect(self):
        while self.client.output() != "WELCOME\n":
            pass
        resSetup = self.requestClient(self.teamName + "\n").split("\n")
        self.clientNb = int(resSetup[0])
        self.mapSize = [int(resSetup[1].split(" ")[0]), int(resSetup[1].split(" ")[1])]

    def loadTree(self):
        try:
            self.levelTree = joblib.load("joblib/level" + str(self.level) + ".joblib")
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
        res = self.checkBroadcast()
        if res[0] != 0:
            if res[1] in Message and self.emitter != 0:
                self.emitter = res[0]
                self.sendBroadcast(Message.OK, List[self.emitter])
                self.elevationParticipant()
            else:
                self.emitter = 0
                self.sendBroadcast(Message.KO, List[res[0]])
        return

    def checkBroadcast(self) -> Tuple[int, str, List[int], int]:
        """
        This function is call by ElevationEmitter and ElevationParticipant,
            check if client received broadcast from other ia, parse and return it

        Returns:
        parsed broadcast [senderId, message, targets, dir]
        """
        res = self.client.output()
        if res.find(Message.CODE.value) == -1:
            return [0, "", [0], 0]
        res = res.split(",")
        dir_ = int(res[0].split(" ")[1])
        splittedRes = res[1].split("|")
        if len(splittedRes) != 4 or splittedRes[0] != Message.CODE.value:
            return [0, "", [0], 0]
        toSend = list(map(int, splittedRes[2].split(" ")))
        res = [int(splittedRes[0]), splittedRes[1], toSend, dir_]
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
                case = self.findClosestElemInLastLook(
                    elem
                )
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
        if out != "ko":
            self.level += 1
            self.loadTree()

    def sendBroadcast(self, message: str, toSend: List[int] = []):
        toSendStr = "|"
        if len(toSend) == 0:
            toSendStr += "0"
        else:
            for id_ in toSend:
                toSendStr += " " + str(id_)
        completeMessage = (
            Message.CODE + "|" + str(self.id) + "|" + message + "|" + toSendStr
        )
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
        res = self.checkBroadcast()
        while res[3] != 0:
            self.sendAllCmd(self.cmdDirections[res[3]])
            res = self.checkBroadcast()
        self.sendBroadcast(Message.OK, List[self.emitter])
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
        res = self.checkBroadcast()
        if res[1] == Message.KO:
            self.emitter = 0
            return
        haveToCome = False
        ready = False
        while haveToCome is False or ready is False:
            self.takeClosestFood()
            if self.inputTree["mfood"] < 13:
                ready = True
                self.sendBroadcast(Message.OK, List[self.emitter])
            res = self.checkBroadcast()
            if res[1] == Message.COME and res[0] == self.emitter:
                haveToCome = True
                self.sendBroadcast(Message.OK, List[self.emitter])
        self.joinEmitter()

    def checkReceivedMessage(
        self, participantsId: List[int], res: Tuple[int, str, List[int], int]
    ) -> List[int]:
        if res[1] == Message.OK:
            if len(participantsId) < self.level - 1:
                participantsId.append(res[0])
                self.sendBroadcast(Message.OK, res[0])
            else:
                self.sendBroadcast(Message.KO, res[0])
        return participantsId

    def waitParticipants(self):
        readyParticipants = 0
        self.inventory()
        while readyParticipants < self.level - 1 and self.inputTree["mfood"] < 13:
            self.takeClosestFood()
            res = self.checkBroadcast()
            if res[0] != 0 and self.isMyIdInList(res[2]) and res[1] == Message.OK:
                readyParticipants += 1
            self.inventory()
        arrivedParticipants = 0
        while arrivedParticipants < self.level - 1:
            self.sendBroadcast(Message.COME)
            res = self.checkBroadcast()
            if res[0] != 0 and self.isMyIdInList(res[2]) and res[1] == Message.OK:
                arrivedParticipants += 1
        self.elevation()

    def elevationEmitter(self):
        """
        This function is call by decision tree when the ia have the stones for elevation,
            the ia call others to try elevation
        """
        self.sendBroadcast(list(Message)[self.level])
        time_ = time.time()
        participantsId: List[int] = []
        res: Tuple[int, str, List[int]] = []
        while time.time() - time_ < 1:
            res = self.checkBroadcast()
            if res[0] != 0 and self.isMyIdInList(res[2]):
                participantsId = self.checkReceivedMessage(participantsId, res)
                time_ = time.time()
            time.sleep(0.1)
        if len(participantsId) == self.level - 1:
            self.waitParticipants()
