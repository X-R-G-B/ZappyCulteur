from zappy_ia.Personnality import Personnality
from zappy_ia.Client import Client

class IA:
    def __init__(self, port: int, machineName: str, teamName: str):
        self.port = port
        self.machineName = machineName
        self.teamName = teamName
        self.personnality = Personnality.Personnality()
        self.client = Client(port, machineName)
    
    def pathfinding(self, pos: int) -> str:
        return "ok\n"

    def changePersonnality(self, personnality: Personnality):
        self.personnality = personnality
    
    def callClient(self, message: str) -> str:
        return "ok\n"