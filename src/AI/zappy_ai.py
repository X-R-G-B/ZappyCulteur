#!/usr/bin/env python3

from zappy_ia import CoreIA, cheater
import socket
import sys
import argparse

class IAClient:
    def __init__(self):
        self.personnality = CoreIA.IAPersonnality()
        self.argParse = Argparse(description="Zappy AI", add_help=False)
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_ip = "127.0.0.1"
        self.messToSend = ""
        self.messReceived = ""
        self.nameMachine = ""
        self.isConnected = False
        self.port = 0
        
    def setPersonnality(self, perso: CoreIA.IAPersonnality):
        self.personnality = perso
    
    def parseArgs(self):
        self.argParse.add_argument("-p", type=int, help="port number", required=True)
        self.argParse.add_argument("-n", type=str, help="name of the team", required=True)
        self.argParse.add_argument("-h", type=str, help="name of the machine", default="localhost")
        self.argParse.add_argument("-help", action="help", help="show this help message and exit")
        args = self.argParse.parse_args()
        self.port = args.p
        self.personnality.teamName = args.n
        self.machineName = args.h
        return self.connectToServer()
    
    def connectToServer(self):
        try:
            self.client_socket.connect((self.nameMachine, self.port))
        except:
            print("Connection error")
            return 1
        print("Connection established")
        self.isConnected = True
        return self.commWithServer()

    def commWithServer(self):
        while (self.isConnected):
            try:
                self.messReceived = self.client_socket.recv(4096)
                self.personnality.output(self.messReceived.decode())
            except:
                print("Error while receiving message")
                self.messReceived = ""
            if (self.messReceived != ""):
                if (self.messReceived.decode() == "dead"):
                    print("You died")
                    self.client_socket.close()
                    self.isConnected = False
                    continue
            self.messToSend = self.personnality.input()
            if (self.messToSend == "quit"):
                self.client_socket.close()
                self.isConnected = False
                continue
            try:
                self.client_socket.send(self.messToSend.encode())
            except:
                print("Error while sending message")
        return 0
        
class Argparse(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write('error: %s\n' % message)
        self.print_help()
        sys.exit(84)

if __name__ == '__main__':
    iaCli = IAClient()
    sys.exit(iaCli.parseArgs())
