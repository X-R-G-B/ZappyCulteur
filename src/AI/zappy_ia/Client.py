#!/usr/bin/env python3

import socket
import select
import threading
from typing import List
from zappy_ia.Enums import Message, ServerRes


class Client:
    def __init__(self, port: int, server_ip: str = "localhost"):
        self._client_socket: socket.socket = socket.socket(
            socket.AF_INET, socket.SOCK_STREAM
        )
        self._dead: bool = False

        self._server_ip: str = server_ip
        self._isConnected: bool = False
        self._port: int = port

        self._inTreatment: int = 0

        self._stopLock: threading.Lock = threading.Lock()
        self._stop: bool = False

        self._receivedLock: threading.Lock = threading.Lock()
        self._messReceived: List[str] = []

        self._broadcastLock: threading.Lock = threading.Lock()
        self._broadcastReceived: List[str] = []

        self._sendLock: threading.Lock = threading.Lock()
        self._messToSend: List[str] = []

        self._thread: threading.Thread = threading.Thread(target=self.connect)
        self._thread.start()

    def isDead(self) -> bool:
        return self._dead

    def connect(self):
        self._client_socket.connect((self._server_ip, self._port))
        self._isConnected = True

        self._client_socket.setblocking(False)

        self._stopLock.acquire()
        while self._isConnected and self._stop is False:
            self._stopLock.release()
            read_sockets, write_sockets, error_sockets = select.select(
                [self._client_socket], [self._client_socket], [self._client_socket], 0
            )
            self._read(read_sockets)
            self._write(write_sockets)
            self._handleError(error_sockets)
            self._stopLock.acquire()

        self._client_socket.close()

    def _checkMessage(self, message: str):
        if Message.CODE.value in message:
            self._broadcastLock.acquire()
            if message.count("\n") == 1:
                self._broadcastReceived.insert(0, message[:-1])
            else:
                for mess in message.split("\n"):
                    if mess != "":
                        self._broadcastReceived.insert(0, mess)
            self._broadcastLock.release()
        elif ServerRes.DEAD.value in message:
            self._dead = True
        elif ServerRes.BROADCAST.value in message and not Message.CODE.value in message:
            return
        elif message:
            self._receivedLock.acquire()
            if len(self._messReceived) == 0 or self._messReceived[0].count("\n") > 0:
                self._messReceived.insert(0, message)
            else:
                self._messReceived[0] += message
            self._receivedLock.release()
            if self._inTreatment > 0:
                self._inTreatment -= 1
        else:
            self._client_socket.close()
            self._isConnected = False

    def _read(self, read_sockets):
        for socket_ in read_sockets:
            if socket_ == self._client_socket:
                message = socket_.recv(2048).decode()
                if message.count("\n") > 1:
                    if message.endswith("\n"):
                        endClosed = True
                    else:
                        endClosed = False
                    message = message.split("\n")
                    i = 0
                    for i in range(len(message)):
                        if message[i] == "":
                            continue
                        if i < len(message) - 1 or endClosed:
                            self._checkMessage(message[i] + "\n")
                        else:
                            self._checkMessage(message[i])
                else:
                    self._checkMessage(message)

    def _addMessageToSend(self):
        self._sendLock.acquire()
        if len(self._messToSend) != 0:
            message = self._messToSend[-1]
            self._messToSend = self._messToSend[:-1]
            self._sendLock.release()
            if message != "\n":
                self._inTreatment += 1
                self._client_socket.sendall(message.encode())
        else:
            self._sendLock.release()

    def _write(self, write_sockets):
        for socket_ in write_sockets:
            if socket_ == self._client_socket and self._inTreatment < 10:
                self._addMessageToSend()

    def _handleError(self, error_sockets):
        for socket_ in error_sockets:
            if socket_ == self._client_socket:
                raise Exception("Socket error")

    def input(self, message: str, arg: str = ""):
        if arg != "":
            message += " " + arg
        message = message.rstrip(" \n")
        if not message.endswith("\n"):
            message += "\n"
        self._sendLock.acquire()
        self._messToSend.insert(0, message)
        self._sendLock.release()

    def outputBroadcast(self) -> List[str]:
        res = []
        self._broadcastLock.acquire()
        if len(self._broadcastReceived) != 0:
            res = self._broadcastReceived
            self._broadcastReceived = []
            self._broadcastLock.release()
        else:
            self._broadcastLock.release()
        return res

    def output(self) -> str:
        res = ""
        self._receivedLock.acquire()
        if len(self._messReceived) != 0:
            message = self._messReceived[-1]
            self._receivedLock.release()
            if message != "" and message != "\n" and message.endswith("\n"):
                res = message
                self._messReceived = self._messReceived[:-1]
        else:
            self._receivedLock.release()
        return res

    def stopClient(self):
        self._stopLock.acquire()
        self._stop = True
        self._stopLock.release()
