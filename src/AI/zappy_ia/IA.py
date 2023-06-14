from enum import Enum
import time
from typing import List, Tuple
from zappy_ia.Client import Client
from typing import Union
import pandas as pd
import os
import joblib
import sys


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
    BROADCAST = "Broadcast text\n"
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
        self.build(7)

    def build(self, neededChild: int = 0):
        self.neededChild = neededChild 
        self.mapSize: Tuple[int, int] = [0, 0]
        self.clientNb: int = 0
        self.level: int = 1
        self.lastLook: List[List[Element]] = []
        self.client: Client = Client(self.port, self.machineName)
        self.inputTree: dict() = {
            "level": [self.level],
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
            "broadcast": [0],
        }
        self.outputTree: dict() = {
            "Take food": self.takeFood,
            "Find food": self.findFood,
        }

        try:
            self.clf = joblib.load("src/AI/joblib/food.joblib")
        except FileNotFoundError:
            print("File joblib not found", file=sys.stderr)
            self.client.stopClient()
            sys.exit(84)

        while self.client.output() != "WELCOME\n":
            pass
        resSetup = self.requestClient(self.teamName + "\n").split("\n")
        if resSetup[0] == "ko":
            print("Not remaining slot")
            self.client.stopClient()
            sys.exit(84)
        if (len(resSetup[1].split(" ")) == 2):
            self.clientNb = int(resSetup[0])
            mapSize = resSetup[1].split(" ")
            self.mapSize = [int(mapSize[0]), int(mapSize[1])]
        else:
            self.clientNb = int(resSetup[0])
            mapSize = mapSize.split("\n")[0].split(" ")
            self.mapSize = [int(mapSize[0]), int(mapSize[1])]
        self.run()

    def checkNeededChilds(self):
        while self.neededChild > 0:
            if int(self.requestClient(Command.CONNECT_NBR.value).split("\n")[0]) > 0:
                print("newIA")
                self.connectNewIA()
            elif self.inputTree["mfood"][0] > 2:
                print("newEgg")
                self.createEgg()
            else:
                break
            self.neededChild -= 1
            print("neededchilds: " + str(self.neededChild))

    def run(self):
        continueRun = True
        try:
            while continueRun:
                self.inventory()
                self.checkNeededChilds()
                self.lookForTree()
                predictions = self.clf.predict(pd.DataFrame(self.inputTree))
                for prediction in predictions:
                    self.outputTree[prediction]()
        except KeyboardInterrupt:
            return

    def waitOutput(self) -> str:
        res = ""
        while res == "":
            res = self.client.output()
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
        res = self.waitOutput()
        if res == "ko":
            raise Exception("Server responsed ko to : " + toSend)
        return res

    def inventory(self):
        """
        This function send the inventory command to the server and
            parse response in self.inputTree which is List
        """
        res = self.requestClient(Command.INVENTORY)
        print(res)
        res = res.split("[")[1].split("]")[0]

        for elem in res.split(","):
            parsedElem = elem.strip().split(" ")
            self.inputTree["m" + parsedElem[0]][0] = int(
                parsedElem[1]
            )

    def lookForTree(self):
        """
        This function get the list of the closest items on the look to
            put in self.inputTree
        """
        self.look()
        for elem in Element:
            if "l" + elem.value in self.inputTree.keys():
                self.inputTree["l" + elem.value][0] = self.findClosestElemInLastLook(
                    elem
                )
        self.inputTree["enemy"][0] = self.findClosestElemInLastLook(Element.PLAYER)

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

    def connectNewIA(self):
        self.pid = os.fork()
        if self.pid == 0:
            self.client.stopClient()
            self.build(0)
        time.sleep(0.5)

    def createEgg(self):
        self.requestClient(Command.FORK.value)
        self.connectNewIA()

    def takeElementInLastLook(self, element: Element, pos: int):
        """
        This function move the ia to the closest element and pick it up

        Parameters:
        element (Element): element to take
        pos (int): pos (in front of the ia) of the element
        """
        if pos < 0:
            return
        self.pathFinding(pos)
        self.requestClient(Command.TAKE_OBJECT, element)

    def takeFood(self):
        self.takeElementInLastLook(
            Element.FOOD, self.findClosestElemInLastLook(Element.FOOD)
        )

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
            self.requestClient("Right\n")
            self.look()
            pos = self.findClosestElemInLastLook(Element.FOOD)
            if distanceLimit != 0 and i > distanceLimit:
                self.findFood(distanceLimit)
            elif pos != -1:
                self.takeElementInLastLook(Element.FOOD, pos)
            i += 1
