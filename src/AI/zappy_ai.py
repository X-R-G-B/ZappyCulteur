#!/usr/bin/env python3

from zappy_ia import IA
import argparse
        
class Argparse(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write('error: %s\n' % message)
        self.print_help()
        sys.exit(84)
        
if __name__ == "__main__":
    argparse = Argparse()
    port = 0
    teamName = ""
    machineName = ""

    argParse.add_argument("-p", type=int, help="port number", required=True)
    argParse.add_argument("-n", type=str, help="name of the team", required=True)
    argParse.add_argument("-h", type=str, help="name of the machine", default="localhost")
    argParse.add_argument("-help", action="help", help="show this help message and exit")
    
    args = self.argParse.parse_args()
    
    port = args.p
    teamName = args.n
    machineName = args.h
    ia = IA(port, machineName, teamName)
    ia.run()
