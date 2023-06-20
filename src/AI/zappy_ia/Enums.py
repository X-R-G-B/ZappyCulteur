from enum import Enum

class Message(Enum):
    OK = "ok"
    KO = "ko"
    L2 = "levelup2"
    L3 = "levelup3"
    L4 = "levelup4"
    L5 = "levelup5"
    L6 = "levelup6"
    L7 = "levelup7"
    L8 = "levelup8"
    COME = "come"
    CODE = "*$+"


class ServerRes(Enum):
    OK = "ok\n"
    KO = "ko\n"
    ELEVATION_UNDERWAY = "Elevation underway\n"
    DEAD = "dead\n"

class Element(Enum):
    EMPTY = "empty"
    FOOD = "food"
    PLAYER = "player"
    LINEMATE = "linemate"
    DERAUMERE = "deraumere"
    SIBUR = "sibur"
    MENDIANE = "mendiane"
    PHIRAS = "phiras"
    THYSTAME = "thystame"


class Command(Enum):
    FORWARD = "Forward"
    RIGHT = "Right"
    LEFT = "Left"
    LOOK = "Look"
    INVENTORY = "Inventory"
    BROADCAST = "Broadcast"
    CONNECT_NBR = "Connect_nbr"
    FORK = "Fork"
    EJECT = "Eject"
    TAKE_OBJECT = "Take"
    SET_OBJECT = "Set"
    INCANTATION = "Incantation"
