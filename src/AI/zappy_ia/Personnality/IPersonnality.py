from enum import Enum
import random

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