from zappy_ai.Personnality.Personnality import Personnality, State, Action
import random
        
move_choices = {
    Action.FORWARD: "Forward",
    Action.RIGHT: "Right",
    Action.LEFT: "Left"
}

class Basic(Personnality):
    def __init__(self):
        self.isWaiting = False
        self.teamName = "Cultureux"
        self.level = 1
        self.mapSize = [0, 0]
        self.clientNum = 0
        
    def run():
        pass

    # def inputMovement(self) -> str:
    #     self.action = random.choice(list(move_choices.keys()))
    #     return move_choices[self.action] + "\n"

    # def inputSetup(self) -> str:
    #     if (self.action == Action.WSETUP):
    #         self.action = Action.NSETUP
    #         return (self.teamName + "\n")
    #     return "\n"
        
    # def input(self) -> str:
    #     if (self.isWaiting == False):
    #         if (self.state == State.ERROR):
    #             self.isWaiting = True
    #             return "quit"
    #         elif (self.state == State.SETUP):
    #             self.isWaiting = True
    #             return self.inputSetup()
    #         elif (self.state == State.MOVEMENT):
    #             self.isWaiting = True
    #             return self.inputMovement()
    #         else:
    #             return "\n"
    #     else:
    #         return "\n"
    
    # def outputSetup(self, message: str):
    #     if (self.action == Action.NSETUP):
    #         self.clientNum = int(message)
    #         self.action = Action.MSETUP
    #     elif (self.action == Action.MSETUP):
    #         maps = message.split(' ')
    #         self.mapSize[0] = int(maps[0])
    #         self.mapSize[1] = int(maps[1])
    #         self.state = State.NONE
    #         self.action = Action.NONE
    #     else:
    #         return

    # def output(self, message: str):
    #     cmds = message.split('\n')
    #     print("Recv: ", end='')
    #     print(cmds[:-1], end="\n\n")   
    #     self.isWaiting = False
    #     for cmd in cmds:
    #         if (cmd == "ko"):
    #             self.state = State.ERROR
    #         elif (self.state == State.NONE):
    #             if (cmd == "WELCOME"):
    #                 self.state = State.SETUP
    #                 self.action = Action.WSETUP
    #             else:
    #                 self.state = State.MOVEMENT
    #                 self.action = Action.NONE
    #         elif (self.state == State.SETUP):
    #             self.outputSetup(cmd)
    #         else:
    #             return
