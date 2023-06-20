import random
import csv
import argparse
import sys
from typing import List, Tuple, Dict


levelCosts: List[List[Tuple[str, int]]] = [
    [("Linemate", 1)],
    [("Linemate", 1), ("Deraumere", 1), ("Sibur", 1)],
    [("Linemate", 2), ("Sibur", 1), ("Phiras", 2)],
    [
        ("Linemate", 1),
        ("Deraumere", 1),
        ("Sibur", 2),
        ("Phiras", 1),
    ],
    [
        ("Linemate", 1),
        ("Deraumere", 2),
        ("Sibur", 1),
        ("Mendiane", 3),
    ],
    [
        ("Linemate", 1),
        ("Deraumere", 2),
        ("Sibur", 3),
        ("Phiras", 1),
    ],
    [
        ("Linemate", 2),
        ("Deraumere", 2),
        ("Sibur", 2),
        ("Mendiane", 2),
        ("Phiras", 2),
        ("Thystame", 1),
    ],
]


class Argparse(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write("error: %s\n" % message)
        self.print_help()
        sys.exit(84)


class CSVGenerator:
    def __init__(self, levels: List[int], nbGen: int, nameFile: str, isSituation: bool):
        self.levels = levels
        self.nbGen = nbGen
        self.nameFile = nameFile
        self.isSituation = isSituation
        self.maxCase = 0
        self.titleColumns = [
            "mfood",
            "mlinemate",
            "mderaumere",
            "msibur",
            "mmendiane",
            "mphiras",
            "mthystame",
            "lfood",
            "llinemate",
            "lderaumere",
            "lsibur",
            "lmendiane",
            "lphiras",
            "lthystame",
            "enemy",
            "response",
        ]
        self.lines = []
        self.lines.append(self.titleColumns)

        self.needed = {
            "Linemate": -1,
            "Deraumere": -1,
            "Sibur": -1,
            "Mendiane": -1,
            "Phiras": -1,
            "Thystame": -1,
        }

        self.mfood: int = 0
        self.mlinemate: int = 0
        self.mderaumere: int = 0
        self.msibur: int = 0
        self.mmendiane: int = 0
        self.mphiras: int = 0
        self.mthystame: int = 0
        self.lfood: int = 0
        self.llinemate: int = 0
        self.lderaumere: int = 0
        self.lsibur: int = 0
        self.lmendiane: int = 0
        self.lphiras: int = 0
        self.lthystame: int = 0
        self.enemy: int = 0
        self.response: str = ""

        self.auto = False

        if not isSituation:
            self.nameFile += "_test"

    def lauch(self):
        i = 2
        for _ in range(self.nbGen):
            tmp = []
            level = random.choice(self.levels)
            tmpLevel = 0
            if level == -1:
                tmpLevel = random.randint(1, 8)
                self.maxCase = (tmpLevel * (tmpLevel + 1)) + tmpLevel
                self.loadNeeded(tmpLevel)
            else:
                self.maxCase = (level * (level + 1)) + level
                self.loadNeeded(level)

            self.mfood = random.randint(1, 15)
            self.mlinemate = (
                self.inventory(level) if level != -1 else self.inventory(tmpLevel)
            )
            self.mderaumere = (
                self.inventory(level) if level != -1 else self.inventory(tmpLevel)
            )
            self.msibur = (
                self.inventory(level) if level != -1 else self.inventory(tmpLevel)
            )
            self.mmendiane = (
                self.inventory(level) if level != -1 else self.inventory(tmpLevel)
            )
            self.mphiras = (
                self.inventory(level) if level != -1 else self.inventory(tmpLevel)
            )
            self.mthystame = (
                self.inventory(level) if level != -1 else self.inventory(tmpLevel)
            )
            self.lfood = self.proba(0.5)
            self.llinemate = self.proba(0.3)
            self.lderaumere = self.proba(0.15)
            self.lsibur = self.proba(0.1)
            self.lmendiane = self.proba(0.1)
            self.lphiras = self.proba(0.08)
            self.lthystame = self.proba(0.05)
            self.enemy = random.randint(0, self.maxCase)
            if self.enemy != 0:
                self.enemy = 1
            if self.isSituation and self.mfood <= 5:
                if self.lfood == 0:
                    self.response = "Find food"
                else:
                    self.response = "Take food"
            elif self.isSituation and self.auto is False:
                if not self.writeResponse(level, i):
                    continue
            else:
                self.response = ""
            tmp.extend(
                [
                    self.mfood,
                    self.mlinemate,
                    self.mderaumere,
                    self.msibur,
                    self.mmendiane,
                    self.mphiras,
                    self.mthystame,
                    self.lfood,
                    self.llinemate,
                    self.lderaumere,
                    self.lsibur,
                    self.lmendiane,
                    self.lphiras,
                    self.lthystame,
                    self.enemy,
                    self.response,
                ]
            )
            self.lines.append(tmp)
            i += 1
        self.writeCSV()

    def loadNeeded(self, level: int):
        self.needed = {
            "Linemate": -1,
            "Deraumere": -1,
            "Sibur": -1,
            "Mendiane": -1,
            "Phiras": -1,
            "Thystame": -1,
        }
        for element in levelCosts[level - 1]:
            self.needed[element[0]] = element[1]

    def writeResponse(self, level: int, nb: int) -> bool:
        self.response = ""
        print("--------------------------------------")
        print(f"Line {nb}: Resources needed for level {level}")
        for element in levelCosts[level - 1]:
            print("{:<10}{}".format(element[0], element[1]))
        print("\n{:<10}{:<10}{:<10}{}".format("Column", "Inventory", "Looked", "Good?"))
        print("--------------------------------------")
        print(
            "{:<10}{:<10}{:<10}{}".format(
                "Food", self.mfood, "Yes" if self.lfood == 1 else "No", "X"
            )
        )
        print(
            "{:<10}{:<10}{:<10}{}".format(
                "Linemate",
                self.mlinemate,
                "Yes" if self.llinemate == 1 else "No",
                "X"
                if self.needed["Linemate"] == -1
                else "Good"
                if self.mlinemate >= self.needed["Linemate"]
                else "Bad",
            )
        )
        print(
            "{:<10}{:<10}{:<10}{}".format(
                "Deraumere",
                self.mderaumere,
                "Yes" if self.lderaumere == 1 else "No",
                "X"
                if self.needed["Deraumere"] == -1
                else "Good"
                if self.mderaumere >= self.needed["Deraumere"]
                else "Bad",
            )
        )
        print(
            "{:<10}{:<10}{:<10}{}".format(
                "Sibur",
                self.msibur,
                "Yes" if self.lsibur == 1 else "No",
                "X"
                if self.needed["Sibur"] == -1
                else "Good"
                if self.msibur >= self.needed["Sibur"]
                else "Bad",
            )
        )
        print(
            "{:<10}{:<10}{:<10}{}".format(
                "Mendiane",
                self.mmendiane,
                "Yes" if self.lmendiane == 1 else "No",
                "X"
                if self.needed["Mendiane"] == -1
                else "Good"
                if self.mmendiane >= self.needed["Mendiane"]
                else "Bad",
            )
        )
        print(
            "{:<10}{:<10}{:<10}{}".format(
                "Phiras",
                self.mphiras,
                "Yes" if self.lphiras == 1 else "No",
                "X"
                if self.needed["Phiras"] == -1
                else "Good"
                if self.mphiras >= self.needed["Phiras"]
                else "Bad",
            )
        )
        print(
            "{:<10}{:<10}{:<10}{}".format(
                "Thystame",
                self.mthystame,
                "Yes" if self.lthystame == 1 else "No",
                "X"
                if self.needed["Thystame"] == -1
                else "Good"
                if self.mthystame >= self.needed["Thystame"]
                else "Bad",
            )
        )
        print(
            "{:<10}{:<10}{:<10}{}".format(
                "Enemy", "No", "Yes" if self.enemy == 1 else "No", "X"
            )
        )
        res = input("\nResponse: ")
        if res == "q":
            self.auto = True
        elif res == "r":
            return False
        else:
            self.response = res
        return True

    def inventory(self, level: int) -> int:
        if level == 1:
            return random.choice([0, 1])
        elif level == 2:
            return random.randint(0, 2)
        else:
            return random.randint(0, 3)

    def proba(self, density: float) -> int:
        proba = 1 - ((1 - density) ** (self.maxCase + 1))
        rand = random.randint(0, 1)
        if rand <= proba:
            return 1
        else:
            return 0

    def writeCSV(self):
        with open(self.nameFile + ".csv", "w", newline="") as file:
            writer = csv.writer(file)
            writer.writerows(self.lines)
        print("File " + self.nameFile + ".csv generated")


if __name__ == "__main__":
    argParser = Argparse(description="Generate CSV file for Zappy IA")

    argParser.add_argument(
        "-l",
        "--levels",
        nargs="+",
        type=int,
        help="Levels of the IA to be generated",
        required=True,
    )
    argParser.add_argument("-n", type=int, help="Number of generation", required=True)
    argParser.add_argument(
        "-f", type=str, help="Name of the file to be generated", required=True
    )
    argParser.add_argument("-t", action="store_true", help="Generate test")
    args = argParser.parse_args()

    levels = args.levels
    nbGen = args.n
    nameFile = args.f
    isSituation = args.t

    if -1 in levels and len(levels) > 1:
        print("Error: -1 must be alone")
        sys.exit(84)

    if nameFile.endswith(".csv"):
        nameFile = nameFile[:-4]

    csvGen = CSVGenerator(levels, nbGen, nameFile, not isSituation)
    csvGen.lauch()
