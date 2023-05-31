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
    TAKE_OBJECT = "Take object\n"
    SET_OBJECT = "Set object\n"
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

        while (self.client.output() != "WELCOME\n"):
            pass
        resSetup = self.requestClient(self.teamName + "\n").split("\n")
        self.clientNb = int(resSetup[0])
        self.mapSize = [int(resSetup[1].split(" ")[0]), int(resSetup[1].split(" ")[1])]

    def requestClient(self, command: Union[Command, str]) -> str:
        """
        This function send command to the server, wait the response and return it

        Parameters:
        command (Union[Command, str]): command to send to the server, can be an enum Command (which is a string value) or a string."
        """
        self.client.input(str(command))
        res = ""
        while (res == ""):
            res = self.client.output()
        if (res == "ko"):
            raise Exception("Server responsed ko to : " + str(command))
        return res

    def look(self):
        res = self.requestClient(Command.LOOK)
        for i in range(len(res)):
            for elem in tile.split(" "):
                self.lastLook[i].append(Element[elem])

    def pathFinding(self, pos: int):
        """
        This function move the ia to the pos in parameters

        Parameters:
        pos (int): pos which represent an index in the array of tile return by server to command look
        """
        for i in range(1, 9):
            self.requestClient(Command.FORWARD)
            mid = i * (i + 1)
            if (mid == pos):
                return
            if (mid - i <= pos and pos < mid):
                self.requestClient(Command.LEFT)
                for x in range(mid - pos):
                    self.requestClient(Command.FORWARD)
                return
            if (mid + i >= pos and pos > mid):
                self.requestClient(Command.RIGHT)
                for x in range(pos - mid):
                    self.requestClient(Command.FORWARD)
                return

    def takeElementInLastLook(self, element: Element):
        """
        This function move the ia to the closest element and pick it up

        Parameters:
        element (str): key of searched element (ex: food, player, etc)
        """
        pos = 0
        for tile in self.lastLook:
            for elem in tile:
                if (elem == element):
                    pathFinding(pos)
                    self.requestClient(Command.TAKE_OBJECT)
                    return
            pos += 1

    def takeFood(self):
        takeElementInLastLook(Element.FOOD)
