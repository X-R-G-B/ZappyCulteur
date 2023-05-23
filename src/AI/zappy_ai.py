#!/usr/bin/env python3

import socket
import sys

class IAClient:
    def __init__(self):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_ip = "127.0.0.1"
        self.messToSend = ""
        self.messReceived = ""
        self.teamName = ""
        self.nameMachine = "localhost"
        self.isConnected = False
        self.port = 0
        self.level = 1
    
    def parseArgs(self):
        if (len(sys.argv) != 7 and len(sys.argv) != 5):
            print("Bad usage: not enough arguments")
            usage()
            return 84
        i = 1
        while (i < len(sys.argv)):
            if (sys.argv[i] == "-p"):
                if (sys.argv[i + 1].isdigit() == False):
                    print("Bad usage: port must be a number")
                    return 84
                self.port = int(sys.argv[i + 1])
                i += 2
                continue
            if (sys.argv[i] == "-n"):
                self.teamName = sys.argv[i + 1]
                i += 2
                continue
            if (sys.argv[i] == "-h"):
                self.nameMachine = sys.argv[i + 1]
                i += 2
                continue
            print("Bad usage: unknown argument")
            usage()
            return 84
        if (self.port == 0 or self.teamName == ""):
            print("Bad usage: mandatory arguments missing")
            usage()
            return 84
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
            self.messToSend = input()
            if (self.messToSend == "quit"):
                self.client_socket.close()
                self.isConnected = False
                continue
            try:
                self.client_socket.send(self.messToSend.encode())
            except:
                print("Error while sending message")
            try:
                self.messReceived = self.client_socket.recv(4096)
                print(self.messReceived.decode())
            except:
                print("Error while receiving message")
                self.messReceived = ""
            if (self.messReceived != ""):
                if (self.messReceived.decode() == "dead"):
                    print("You died")
                    self.client_socket.close()
                    self.isConnected = False
                    continue
        return 0
        
def usage():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("       port     is the port number")
    print("       name     is the name of the team")
    print("       machine  is the name of the machine; localhost by default")

if __name__ == '__main__':
    iaCli = IAClient()
    sys.exit(iaCli.parseArgs())
