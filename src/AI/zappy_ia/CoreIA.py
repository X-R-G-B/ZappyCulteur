from enum import Enum

class State(Enum):
        ERROR = -1
        NONE = 0
        SETUP = 1
        MOVEMENT = 2
        CHEAT = 10

class Action(Enum):
        NONE = 0
        WSETUP = 1
        NSETUP = 2
        MSETUP = 3
        FORWARD = 4
        RIGHT = 5
        LEFT = 6
        TESTING = 11
        WORK = 12
        NOTWORK = 13

class IAPersonnality:
    def __init__(self):
        self.state = State.NONE
        self.action = Action.NONE
        self.teamName = "Cultureux"
        self.level = 1
        self.mapSize = [0, 0]
        self.clientNum = 0
        
    def inputMovement(self) -> str:
        if (self.action == Action.NONE or self.action == Action.FORWARD):
            self.action = Action.FORWARD
            return "Forward\n"
        else:
            return "\n"

    def inputSetup(self) -> str:
        if (self.action == Action.WSETUP):
            self.action = Action.NSETUP
            return (self.teamName + "\n")
        return "\n"
        
    def input(self) -> str:
        if (self.state == State.ERROR):
            return "quit"
        elif (self.state == State.SETUP):
            return self.inputSetup()
        elif (self.state == State.MOVEMENT):
            return self.inputMovement()
        else:
            return "\n"
    
    def outputSetup(self, message: str):
        if (self.action == Action.NSETUP):
            self.clientNum = int(message)
            self.action = Action.MSETUP
        elif (self.action == Action.MSETUP):
            maps = message.split(' ')
            self.mapSize[0] = int(maps[0])
            self.mapSize[1] = int(maps[1])
            self.state = State.NONE
            self.action = Action.NONE
        else:
            return

    def output(self, message: str):
        print(message)   
        cmds = message.split('\n')
        for cmd in cmds:
            if (cmd == "ko"):
                self.state = State.ERROR
            elif (self.state == State.NONE):
                if (cmd == "WELCOME"):
                    self.state = State.SETUP
                    self.action = Action.WSETUP
                else:
                    self.state = State.MOVEMENT
                    self.action = Action.NONE
            elif (self.state == State.SETUP):
                self.outputSetup(cmd)
            else:
                return
