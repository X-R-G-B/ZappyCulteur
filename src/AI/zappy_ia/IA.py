from enum import Enum
from typing import List, Tuple
from zappy_ia.Client import Client
from typing import Union
import time


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
        self.mapSize: Tuple[int, int] = [0, 0]
        self.clientNb: int = 0
        self.lastLook: List[List[Element]] = []
        self.client: Client = Client(port, machineName)

        while self.client.output() != "WELCOME\n":
            pass
        resSetup = self.requestClient(self.teamName + "\n").split("\n")
        self.clientNb = int(resSetup[0])
        self.mapSize = [int(resSetup[1].split(" ")[0]), int(resSetup[1].split(" ")[1])]

    def requestClient(self, command: Union[Command, str], arg: str = "") -> str:
        """
        This function send command to the server, wait the response and return it

        Parameters:
        command (Union[Command, str]): command to send to the server, can be Command or str."

        Returns:
        Server response
        """
        toSend: str = ""
        if isinstance(command, Command):
            toSend = command.value
        else:
            toSend = command
        self.client.input(toSend, arg)
        res = ""
        while res == "":
            res = self.client.output()
        if res == "ko":
            raise Exception("Server responsed ko to : " + command.value)
        return res

    def look(self):
        res = self.requestClient(Command.LOOK)
        self.lastLook.clear()
        for i in range(len(res)):
            self.lastLook.append([])
            for elem in res[i].split(" "):
                if elem == "":
                    self.lastLook[i].append(Element.EMPTY)
                else:
                    self.lastLook[i].append(Element(elem))

    def pathFinding(self, pos: int):
        """
        This function move the ia to the pos in parameters

        Parameters:
        pos (int): pos which represent an index in the array of tile return by server to command look
        """
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
        self.requestClient(Command.TAKE_OBJECT, element.value)

    def takeFood(self, pos: int):
        self.takeElementInLastLook(Element.FOOD, pos)

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
        if checkCurrentTile == False:
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
        This function find and take the closest food in other directions than the current,
            because it will be call when ia need food and don't see any in last look
            this function is call when ia need to survive and don't care of other items

        Parameters:
        distanceLimit (int): is the id of the last line where we can go take food, after it's too far away
            0 if no limit
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
