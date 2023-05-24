from enum import Enum

class State(Enum):
        ERROR = -1
        NONE = 0
        TESTING = 1
        WORK = 2
        NOTWORK = 3
        WSETUP = 4
        NSETUP = 5
        MSETUP = 6

class IAPersonnality:
    def __init__(self):
        self.state = State.NONE
        self.teamName = "Cultureux"
        self.level = 1
        self.mapSize = [0, 0]
        self.clientNum = 0
        self.switch = False

    def input(self) -> str:
        if (self.state == State.WSETUP):
            self.state = State.NSETUP
            return ("-->" + self.teamName + "\n")
        if (self.state == State.MSETUP):
            return ""
        return "quit"

    def output(self, message: str):
        print(message)
        if (message == "<--WELCOME\n"):
            self.state = State.WSETUP
        elif (self.state == State.NSETUP):
            self.clientNum = int(message[3:-1])
            self.state = State.MSETUP
        elif (self.state == State.MSETUP):
            maps = message[:-1].split(' ')
            self.mapSize[0] = int(maps[1])
            self.mapSize[1] = int(maps[2])
            self.state = State.NONE
        return