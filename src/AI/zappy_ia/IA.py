from typing import Dict, List, Tuple
from zappy_ia.ClientManager import ClientManager
from zappy_ia.DecisionTree import DecisionTree
from zappy_ia.ElevationParticipant import ElevationParticipant
import random

class IA:
    def __init__(self, port: int, machineName: str, teamName: str):
        self.setId()
        self._clientManager: ClientManager = ClientManager(port, machineName, teamName, self._id)
        self._decisionTree: DecisionTree = DecisionTree(self._clientManager)
        self._elevationParticipant: ElevationParticipant = ElevationParticipant(self._clientManager, self._decisionTree)
        self.run()

    def setId(self):
        self._id = random.randint(10000, 99999)

    def run(self):
        continueRun = True
        try:
            while continueRun:
                if (self._elevationParticipant.checkElevationParticipant(self._decisionTree.getCurrentLevel()) == True):
                    self._decisionTree.incrementLevel()
                self._decisionTree.predict()
        except KeyboardInterrupt:
            return
