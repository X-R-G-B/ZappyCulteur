from zappy_ia.CoreIA import IAPersonnality, State

class cheaterIA(IAPersonnality):
    def __init__(self):
        self.bctWork = State.NONE
        self.mctWork = State.NONE

    def input(self):
        if (self.bctWork == State.NONE):
            self.bctWork = State.TESTING
            return "bct 0 0\n"
        elif (self.mctWork == State.NONE):
            self.mctWork = State.TESTING
            return "mct\n"
        else:
            return "quit"
    
    def output(self, message):
        if (self.bctWork == State().TESTING):
            if (message != "ko\n"):
                self.bctWork = State().WORK
                return
        elif (self.mctWork == State().TESTING):
            if (message != "ko\n"):
                self.mctWork = State().WORK
                return
        return