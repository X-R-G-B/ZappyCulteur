from zappy_ia.CoreIA import IAPersonnality, State

class cheaterIA(IAPersonnality):
    def __init__(self):
        self.bctTest = State.NONE
        self.mctTest = State.NONE

    def input(self):
        if (self.state == False):
            return self.inputBase()
        else:
            if (self.bctTest == State.NONE):
                self.bctTest = State.TESTING
                return "bct 0 0\n"
            elif (self.mctTest == State.NONE):
                self.mctTest = State.TESTING
                return "mct\n"
            else:
                return ""

    def output(self, message):
        if (self.state == False):
            return self.outputBase(message)
        else :
            if (self.bctTest == State().TESTING):
                if (message != "ko\n"):
                    self.bctTest = State().WORK
                    return
            elif (self.mctTest == State().TESTING):
                if (message != "ko\n"):
                    self.mctTest = State().WORK
                    return
            return
