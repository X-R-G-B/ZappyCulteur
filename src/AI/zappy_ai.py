#!/usr/bin/env python3

from zappy_ia.Client import Client
from zappy_ia.IA import IA
import argparse
import sys
 
class Argparse(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write('error: %s\n' % message)
        self.print_help()
        sys.exit(84)

def abc(a: int):
    print(a)

abc("ade")
        
if __name__ == "__main__":
    argParse = Argparse(add_help=False)
    port = 0
    teamName = ""
    machineName = ""

    argParse.add_argument("-p", type=int, help="port number", required=True)
    argParse.add_argument("-n", type=str, help="name of the team", required=True)
    argParse.add_argument("-h", type=str, help="name of the machine", default="localhost")
    argParse.add_argument("-help", action="help", help="show this help message and exit")

    args = argParse.parse_args()
    port = args.p
    teamName = args.n
    machineName = args.h

    bee = IA(port, machineName, teamName)
