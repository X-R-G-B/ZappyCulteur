from zappy_ia.Log import LogGood
from zappy_ia.ClientManager import ClientManager
from zappy_ia.DecisionTree import DecisionTree
from zappy_ia.ElevationParticipant import ElevationParticipant
from zappy_ia.Enums import Command
import random
from datetime import datetime
import os


class IA:
    def __init__(self, port: int, machineName: str, teamName: str):
        self._port: int = port
        self._machineName: str = machineName
        self._teamName: str = teamName
        self.build(7)

    def build(self, neededChilds: int):
        self._neededChilds = neededChilds
        self.setId()
        self._log = LogGood(f"log/{self._id}ia.log")
        self._clientManager: ClientManager = ClientManager(
            self._port, self._machineName, self._teamName, self._id, self._log
        )
        self._decisionTree: DecisionTree = DecisionTree(
            self._clientManager, self._log, self._id
        )
        self._elevationParticipant: ElevationParticipant = ElevationParticipant(
            self._clientManager, self._decisionTree, self._log
        )
        self.run()

    def setId(self):
        self._id = random.randint(10000, 99999)

    def connectNewIA(self):
        self.pid = os.fork()
        if self.pid == 0:
            self._clientManager.stopClient()
            self.build(0)

    def createEgg(self):
        self._clientManager.requestClient(Command.FORK.value)
        self.connectNewIA()

    def checkNeededChilds(self):
        while self._neededChilds > 0:
            if (
                int(
                    self._clientManager.requestClient(Command.CONNECT_NBR.value).split(
                        "\n"
                    )[0]
                )
                > 0
            ):
                self.connectNewIA()
            elif self._decisionTree.getCurrentFood() > 2:
                self.createEgg()
            else:
                break
            self._neededChilds -= 1

    def run(self):
        continueRun = True
        try:
            while continueRun:
                curTime = datetime.now()
                if self._clientManager.isDead() == True:
                    self._log.info("IS DEAD")
                    return
                self.checkNeededChilds()
                if (
                    self._elevationParticipant.checkElevationParticipant(
                        self._decisionTree.getCurrentLevel()
                    )
                    is True
                ):
                    self._decisionTree.incrementLevel()
                self._decisionTree.predict()
                self._log.debug("main loop time: " + str(datetime.now() - curTime))
        except KeyboardInterrupt:
            self._clientManager.stopClient()
            return
        self._clientManager.stopClient()
