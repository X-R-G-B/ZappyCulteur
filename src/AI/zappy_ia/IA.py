from typing import List
from zappy_ia.Client import Client
import time

class IA:
    def __init__(self, port: int, machineName: str, teamName: str):
        self.port = port
        self.machineName = machineName
        self.teamName = teamName
        self.mapSize = [0, 0]
        self.clientNb = 0
        self.lastLook = []
        self.client = Client(port, machineName)

        while (self.client.output() != "WELCOME\n"):
            pass
        resSetup = self.requestClient(self.teamName + "\n").split("\n")
        self.clientNb = int(resSetup[0])
        self.mapSize = [int(resSetup[1].split(" ")[0]), int(resSetup[1].split(" ")[1])]

    def requestClient(self, message: str) -> str:
        self.client.input(message)
        res = ""
        while (res == ""):
            res = self.client.output()
        if (res == "ko"):
            raise Exception("Server responsed ko to : " + message)
        return res

    def pathFinding(self, pos: int):
        """
        This function move the ia to the pos in parameters

        Parameters:
        pos (int): pos which represent an index in the array of tile return by server to command look
        """
        for i in range(1, 9):
            self.requestClient("Forward\n")
            mid = i * (i + 1)
            if (mid == pos):
                return
            if (mid - i <= pos and pos < mid):
                self.requestClient("Left\n")
                for x in range(mid - pos):
                    self.requestClient("Forward\n")
                return
            if (mid + i >= pos and pos > mid):
                self.requestClient("Right\n")
                for x in range(pos - mid):
                    self.requestClient("Forward\n")
                return

    def takeElementInLastLook(self, element: str):
        """
        This function move the ia to the closest element and pick it up

        Parameters:
        element (str): key of searched element (ex: food, player, etc)
        """
        pos = 0
        for tile in self.lastLook:
            for elem in tile.split(" "):
                if (elem == element):
                    pathFinding(pos)
                    self.requestClient("Take object\n")
                    return
            pos += 1

    def takeFood(self):
        takeElementInLastLook("food")
