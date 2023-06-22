import joblib
from datetime import datetime
import sys
import pandas as pd
from typing import Dict, List, Tuple
from zappy_ia.ClientManager import ClientManager
from zappy_ia.Enums import Message, Element, Command, ServerRes
from zappy_ia.Log import LogGood

levelParticipantsNb: List[int] = [0, 0, 1, 1, 3, 3, 5, 5]

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


class DecisionTree:
    def __init__(self, clientManager: ClientManager, log: LogGood, id: int):
        self._participantsId: List[int] = []
        self._clientManager: ClientManager = clientManager
        self._level: int = 1
        self._log: LogGood = log
        self._id: int = id
        self.loadTree()
        self._lastLook: List[List[Element]] = []
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

    def getCurrentLevel(self) -> int:
        return self._level

    def incrementLevel(self):
        self._level += 1
        self.loadTree()

    def getFood(self) -> int:
        return self._inputTree["mfood"][0]

    def getCurrentFood(self) -> int:
        self.inventory()
        return self.getFood()

    def predict(self):
        self.inventory()
        self.lookForTree()
        curTime = datetime.now()
        predictions = self._levelTree.predict(pd.DataFrame(self._inputTree))
        self._log.debug("predict time: : " + str(datetime.now() - curTime))
        for prediction in predictions:
            self._log.info("Pred:" + prediction)
            self._outputTree[prediction]()

    def inventory(self):
        """
        This function send the inventory command to the server and
            parse response in self._inputTree which is List
        """
        res = self._clientManager.requestClient(Command.INVENTORY)
        rescpy = ""
        if res == ServerRes.KO.value:
            return
        try:
            rescpy = res
            res = res.split("[")[1].split("]")[0]
            for elem in res.split(","):
                parsedElem = elem.strip().split(" ")
                self._inputTree["m" + parsedElem[0]][0] = int(parsedElem[1])
        except (IndexError, ValueError):
            print(
                f"ID : {self._clientManager._id} crashed in inventory when received : ",
                rescpy,
            )
            self._clientManager.stopClient()

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

        res = self._clientManager.requestClient(Command.LOOK)
        rescpy = ""
        if res == ServerRes.KO.value:
            return
        try:
            rescpy = res
            res = res.split("[")[1].split("]")[0]

            i = 0
            for tile in res.split(","):
                self._lastLook.append([])
                for elem in tile.split(" "):
                    if elem == "":
                        self._lastLook[i].append(Element.EMPTY)
                    else:
                        self._lastLook[i].append(Element(elem))
                i += 1
        except IndexError:
            print(
                f"ID : {self._clientManager._id} crashed in look when received : ",
                rescpy,
            )
            self._clientManager.stopClient()
            return

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
            self._clientManager.requestClient(Command.FORWARD)
            mid = i * (i + 1)
            if mid == pos:
                return
            if mid - i <= pos and pos < mid:
                self._clientManager.requestClient(Command.LEFT)
                for _ in range(mid - pos):
                    self._clientManager.requestClient(Command.FORWARD)
                return
            if mid + i >= pos and pos > mid:
                self._clientManager.requestClient(Command.RIGHT)
                for _ in range(pos - mid):
                    self._clientManager.requestClient(Command.FORWARD)
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
        self._clientManager.requestClient(Command.TAKE_OBJECT, element)

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
        self.takeClosestFood()

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
            self._clientManager.requestClient(Command.RIGHT)
            self.look()
            pos = self.findClosestElemInLastLook(Element.FOOD)
            if distanceLimit != 0 and i > distanceLimit:
                self.findFood(distanceLimit)
            elif pos != -1:
                self.takeElement(Element.FOOD, pos)
            i += 1

    def checkStonesForElevation(self) -> bool:
        for costTuple in levelCosts[self._level - 1]:
            if costTuple[1] > self._inputTree["m" + costTuple[0].value][0]:
                return False
        return True

    def chooseElevation(self):
        if self._level == 1:
            self.elevation()
        elif self.checkStonesForElevation() is True:
            self.elevationEmitter()

    def loadTree(self):
        try:
            self._levelTree = joblib.load(
                "src/AI/joblib/level" + str(self._level) + ".joblib"
            )
        except FileNotFoundError:
            print("File joblib not found", file=sys.stderr)
            self._clientManager.stopClient()
            sys.exit(84)

    def checkElevationFinalRes(self):
        out = self._clientManager.waitOutput()
        if out != ServerRes.KO.value:
            self.incrementLevel()
        elif self._level == 1:
            self._clientManager.requestClient(Command.FORWARD)
        self._participantsId = []

    def elevation(self):
        if self.checkStonesForElevation() is False:
            return
        for costTuple in levelCosts[self._level - 1]:
            for _ in range(costTuple[1]):
                self._clientManager.requestClient(
                    Command.SET_OBJECT, costTuple[0].value
                )
        res = self._clientManager.requestClient(Command.INCANTATION)
        if res == ServerRes.KO.value:
            if self._level == 1:
                self._clientManager.requestClient(Command.FORWARD)
            else:
                self._clientManager.sendBroadcast(
                    Message.KO.value, self._participantsId
                )
                self._participantsId = []
            return
        self.checkElevationFinalRes()

    def takeClosestFood(self):
        self.look()
        foodPos = self.findClosestElemInLastLook(Element.FOOD)
        if foodPos == -1:
            self.findFood()
        else:
            self.takeElement(Element.FOOD, foodPos)

    def checkReceivedMessage(self, res: Tuple[int, str, List[int], int]):
        self._log.debug("message: " + res[1])
        if res[1] == Message.OK.value:
            if len(self._participantsId) < levelParticipantsNb[self._level]:
                self._log.debug("res ok")
                self._participantsId.append(res[0])
                self._clientManager.sendBroadcast(Message.OK.value, [res[0]])
            else:
                self._log.debug("res ko")
                self._clientManager.sendBroadcast(Message.KO.value, [res[0]])

    def takeFoodIfAtFeet(self):
        self.look()
        for elem in self._lastLook[0]:
            if elem == Element.FOOD:
                self._clientManager.requestClient(Command.TAKE_OBJECT, Element.FOOD)

    def checkArrivedParticipants(self):
        arrivedParticipants = 0
        while arrivedParticipants < levelParticipantsNb[self._level]:
            self.takeFoodIfAtFeet()
            self._clientManager.sendBroadcast(Message.COME.value, self._participantsId)
            res = self._clientManager.checkBroadcastWithoutNewElevation()
            for mess in res:
                if mess[1] == Message.OK.value:
                    arrivedParticipants += 1
                    self._log.debug("arrived Participants: " + str(arrivedParticipants))

    def waitParticipants(self):
        readyParticipants = 0
        res: List[Tuple[int, str, List[int], int]] = []
        self.inventory()
        while (
            readyParticipants < levelParticipantsNb[self._level]
            or self._inputTree["mfood"][0] < 13
        ):
            self.takeClosestFood()
            res = self._clientManager.checkBroadcastWithoutNewElevation()
            for mess in res:
                if mess[1] == Message.OK.value:
                    if self._clientManager.isIdInList(self._participantsId, mess[0]):
                        readyParticipants += 1
                        self._log.debug(
                            "readyParticipants nb: " + str(readyParticipants)
                        )
                    else:
                        self._log.debug("resp ko in waitparticipant")
                        self._clientManager.sendBroadcast(Message.KO.value, [mess[0]])
            self.inventory()
        self.checkArrivedParticipants()
        self.elevation()

    def elevationEmitter(self):
        """
        This function is call by decision tree when the ia have the stones for elevation,
            the ia call others to try elevation
        """
        res = self._clientManager.checkBroadcast()
        for mess in res:
            if mess[1] == "levelup" + str(self._level):
                return
        self._participantsId = []
        res: List[Tuple[int, str, List[int], int]] = []
        while len(self._participantsId) < levelParticipantsNb[self._level]:
            self._clientManager.sendBroadcast(list(Message)[self._level].value)
            res = self._clientManager.checkBroadcastWithoutNewElevation()
            for mess in res:
                self.checkReceivedMessage(mess)
            self.takeClosestFood()
        self._clientManager.sendBroadcast(Message.OK.value, self._participantsId)
        self.waitParticipants()
