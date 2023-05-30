from typing import List
from zappy_ia.Personnality.Personnality import Personnality
from zappy_ia.Client import Client
import time

class IA:
    def __init__(self, port: int, machineName: str, teamName: str):
        self.port = port
        self.machineName = machineName
        self.teamName = teamName
        self.mapSize = [0, 0]
        self.clientNb = 0
        self.cmdPathfinding = []
        self.personnality = Personnality()
        self.client = Client(port, machineName)

        while (self.client.output() != "WELCOME\n"):
            pass
        self.client.input(self.teamName + "\n")
        resSetup = self.client.output()
        while (resSetup == ""):
            resSetup = self.client.output().split("\n")
        self.clientNb = int(resSetup[0])
        self.mapSize = [int(resSetup[1].split(" ")[0]), int(resSetup[1].split(" ")[1])]
    
    def pathfinding(self, pos: int) -> List[str]:
        for i in range(1, 9):
            res = i * (i + 1)
            if (res == pos):
                self.cmdPathfinding += ["Forward\n"] * i
                return self.cmdPathfinding
            elif (res - i <= pos and pos < res):
                self.cmdPathfinding += ["Forward\n"] * i
                self.cmdPathfinding += ["Left\n"]
                self.cmdPathfinding += ["Forward\n"] * (res - (res - i))
                return self.cmdPathfinding
            elif (res + i >= pos and pos > res):
                self.cmdPathfinding += ["Forward\n"] * i
                self.cmdPathfinding += ["Right\n"]
                self.cmdPathfinding += ["Forward\n"] * ((res + i) - res)
                return self.cmdPathfinding
        return self.cmdPathfinding

    def changePersonnality(self, personnality: Personnality):
        self.personnality = personnality
    
    def callClient(self, message: str) -> str:
        return "ok\n"
