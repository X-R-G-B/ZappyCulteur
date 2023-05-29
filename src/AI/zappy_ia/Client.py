#!/usr/bin/env python3

import socket
import select
import sys
import threading
import time

class Client:
    def __init__(self, port: int, machineName: str = "localhost"):
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_ip = "127.0.0.1"
        self.messToSend = "\n"
        self.messReceived = "\n"
        self.machineName = machineName
        self.isConnected = False
        self.port = port

        self.stopLock = threading.Lock()
        self.stop = False
        self.receivedLock = threading.Lock()
        self.sendLock = threading.Lock()
        thread = threading.Thread(target=self.connect)
        thread.start()
        time.sleep(0.1)

    def connect(self):
        self.client_socket.connect((self.machineName, self.port))
        self.isConnected = True

        self.client_socket.setblocking(0)
        
        self.stopLock.acquire()
        while self.isConnected and self.stop == False:
            self.stopLock.release()
            read_sockets, write_sockets, _ = select.select([self.client_socket], [self.client_socket], [], 0)
            self.read(read_sockets)
            self.write(write_sockets)
            self.stopLock.acquire()

        self.client_socket.close()

    def read(self, read_sockets):
        for socket in read_sockets:
            if (socket == self.client_socket):
                message = socket.recv(2048).decode()
                if message:
                    self.receivedLock.acquire()
                    self.messReceived = message
                    self.receivedLock.release()
                else:
                    self.client_socket.close()
                    self.isConnected = False

    def write(self, write_sockets):
        for socket in write_sockets:
            if (socket == self.client_socket):
                self.sendLock.acquire()
                message = self.messToSend
                self.messToSend = "\n"
                self.sendLock.release()
                if (message != '\n'):
                    self.client_socket.sendall(message.encode())

    def input(self, message: str):
        self.sendLock.acquire()
        self.messToSend = message
        self.sendLock.release()

    def output(self) -> str:
        self.receivedLock.acquire()
        message = self.messReceived
        self.receivedLock.release()
        if (message != "" or message != "\n"):
            res = message
        else:
            res = ""
        time.sleep(0.1)
        return res

    def stopClient(self):
        self.stopLock.acquire()        
        self.stop = True
        self.stopLock.release()        
