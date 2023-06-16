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
    FORWARD = "Forward\n"
    RIGHT = "Right\n"
    LEFT = "Left\n"
    LOOK = "Look\n"
    INVENTORY = "Inventory\n"
    BROADCAST = "Broadcast"
    CONNECT_NBR = "Connect_nbr\n"
    FORK = "Fork\n"
    EJECT = "Eject\n"
    TAKE_OBJECT = "Take"
    SET_OBJECT = "Set"
    INCANTATION = "Incantation\n"
