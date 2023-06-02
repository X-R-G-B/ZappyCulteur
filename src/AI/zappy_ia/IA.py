from typing import List
from zappy_ia.Client import Client
import os
import time

class IA:
    def __init__(self, port: int, machineName: str, teamName: str):
        self.port = port
        self.machineName = machineName
        self.teamName = teamName
        self.build()

    def build():
        self.mapSize = [0, 0]
        self.clientNb = 0
        self.cmdPathfinding = []
        self.client = Client(self.port, self.machineName)
        self.pid: int = 0

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

    def reproduction(self):
        self.requestClient("Fork\n")
        self.pid = os.fork()
        if (self.pid == 0):
            self.build()
