#!/usr/bin/env python3

from zappy_ia.Personnality import CoreIA, cheater
import socket
import select
import sys
import argparse

class Client:
    def __init__(self, port: int, machineName: str = "localhost"):
        self.argParse = Argparse(description="Zappy AI", add_help=False)
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_ip = "127.0.0.1"
        self.messToSend = "\n"
        self.messReceived = "\n"
        self.nameMachine = machineName
        self.isConnected = False
        self.port = port
        
        try:
            self.client_socket.connect((self.machineName, self.port))
            print("Connected to server")
            self.isConnected = True

            self.client_socket.setblocking(0)
            
            while self.isConnected:
                read_sockets, write_sockets, _ = select.select([self.client_socket], [self.client_socket], [], 0)
                
                for socket in read_sockets:
                    if (socket == self.client_socket):
                        message = socket.recv(2048).decode()
                        if message:
                            self.messReceived = message
                        else:
                            self.client_socket.close()
                            self.isConnected = False
                for socket in write_sockets:
                    if (socket == self.client_socket):
                        message = self.messToSend
                        if (message != '\n'):
                            print("Send: " + message, end='')
                            self.client_socket.sendall(message.encode())
        except ConnectionRefusedError:
            print("Connection refused")
        except KeyboardInterrupt:
            print("Disconnected from server")
        finally:
            self.client_socket.close()
            
    def input(self, message: str):
        self.messToSend = message

    def output(self) -> str:
        if (self.messReceived != ""):
            print(self.messReceived)
            return self.messReceived
        return ""
    
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
        
class Argparse(argparse.ArgumentParser):
    def error(self, message):
        sys.stderr.write('error: %s\n' % message)
        self.print_help()
        sys.exit(84)
