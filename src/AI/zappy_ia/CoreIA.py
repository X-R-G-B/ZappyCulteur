from enum import Enum

class State(Enum):
        NONE = 0
        TESTING = 1
        WORK = 2
        NOTWORK = 3

class IAPersonnality:
    def __init__(self):
        self.bctWork = State.NONE
        self.mctWork = State.NONE
        self.teamName = ""
        self.level = 1
        self.switch = False
    
    def input(self):
        if (self.switch == False):
            self.switch = True
            return "Euhhh... I'm just dumb\n"
        return "quit"
    
    def output(self, message):
        print(message)
        return