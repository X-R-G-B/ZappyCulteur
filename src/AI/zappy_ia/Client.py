#!/usr/bin/env python3

import socket
import select
import threading
import time
from typing import List
from MessageEnum import Message


class Client:
    def __init__(self, port: int, server_ip: str = "localhost"):
        self.client_socket: socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_ip: int = server_ip
        self.isConnected: bool = False
        self.port: int = port

        self.inTreatment: int = 0

        self.stopLock: threading.Lock = threading.Lock()
        self.stop: bool = False

        self.receivedLock: threading.Lock = threading.Lock()
        self.messReceived: List[str] = []

        self.broadcastLock: threading.Lock = threading.Lock()
        self.broadcastReceived: List[str] = []

        self.sendLock: threading.Lock = threading.Lock()
        self.messToSend: List[str] = []

        self.thread: threading.Thread = threading.Thread(target=self.connect)
        self.thread.start()
        time.sleep(0.1)

    def connect(self):
        self.client_socket.connect((self.server_ip, self.port))
        self.isConnected = True

        self.client_socket.setblocking(False)

        self.stopLock.acquire()
        while self.isConnected and self.stop is False:
            self.stopLock.release()
            read_sockets, write_sockets, error_sockets = select.select(
                [self.client_socket], [self.client_socket], [self.client_socket], 0
            )
            self.read(read_sockets)
            self.write(write_sockets)
            self.handleError(error_sockets)
            self.stopLock.acquire()

        self.client_socket.close()

    def checkMessage(self, message: str):
        if message.find(Message.CODE.value) != -1:
            self.broadcastLock.acquire()
            print("Recv broadcast: " + message)
            self.broadcastReceived.insert(0, message)
            self.broadcastLock.release()
        elif message:
            self.receivedLock.acquire()
            print("Recv: ", end="")
            print(message.split("\n")[:-1])
            self.messReceived.insert(0, message)
            self.receivedLock.release()
            if self.inTreatment > 0:
                self.inTreatment -= 1
        else:
            self.client_socket.close()
            self.isConnected = False

    def read(self, read_sockets):
        for socket_ in read_sockets:
            if socket_ == self.client_socket:
                message = socket_.recv(2048).decode()
                self.checkMessage(message)

    def addMessageToSend(self):
        self.sendLock.acquire()
        if len(self.messToSend) != 0:
            message = self.messToSend[-1]
            print("Send: ", end="")
            print(message.split("\n")[:-1])
            self.messToSend = self.messToSend[:-1]
            self.sendLock.release()
            if message != "\n":
                self.inTreatment += 1
                self.client_socket.sendall(message.encode())
        else:
            self.sendLock.release()

    def write(self, write_sockets):
        for socket_ in write_sockets:
            if socket_ == self.client_socket and self.inTreatment < 10:
                self.addMessageToSend()

    def handleError(self, error_sockets):
        for socket_ in error_sockets:
            if socket_ == self.client_socket:
                raise Exception("Socket error")

    def input(self, message: str, arg: str = ""):
        if arg != "":
            message += " " + arg + "\n"
        self.sendLock.acquire()
        self.messToSend.insert(0, message)
        self.sendLock.release()

    def outputBroadcast(self) -> str:
        res = ""
        self.broadcastLock.acquire()
        if len(self.broadcastReceived) != 0:
            message = self.broadcastReceived[-1]
            self.broadcastReceived = self.broadcastReceived[:-1]
            self.broadcastLock.release()
            if message != "" or message != "\n":
                res = message
        else:
            self.broadcastLock.release()
        time.sleep(0.1)
        return res

    def output(self) -> str:
        res = ""
        self.receivedLock.acquire()
        if len(self.messReceived) != 0:
            message = self.messReceived[-1]
            self.messReceived = self.messReceived[:-1]
            self.receivedLock.release()
            if message != "" or message != "\n":
                res = message
        else:
            self.receivedLock.release()
        time.sleep(0.1)
        return res

    def stopClient(self):
        self.stopLock.acquire()
        self.stop = True
        self.stopLock.release()
