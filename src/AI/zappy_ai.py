#!/usr/bin/env python3

import socket
import sys

def usage():
    print("USAGE: ./zappy_ai -p port -n name -h machine")
    print("       port     is the port number")
    print("       name     is the name of the team")
    print("       machine  is the name of the machine; localhost by default")
    
def connectToServer(port, name, machine):
    client_ip = "127.0.0.1"
    isConnected = True

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        client_socket.connect((machine, port))
    except:
        print("Connection error")
        return 1
    print("Connection established")
    while (isConnected):
        mess = input("Enter a message: ")
        if (mess == "quit"):
            client_socket.close()
            isConnected = False
        try:
            client_socket.send(mess.encode())
        except:
            print("Error while sending message")
            return 1
        try:
            data = client_socket.recv(4096)
            print(data.decode())
        except:
            print("Error while receiving message")
            return 1
        if (data.decode() == "dead"):
            print("You died")
            client_socket.close()
            isConnected = False
    return 0
        

def main():
    if (len(sys.argv) == 2 and sys.argv[1] == "-help"):
        usage()
        return 0
    if (len(sys.argv) != 7 and len(sys.argv) != 5):
        print("Bad usage: not enough arguments")
        usage()
        return 84
    port = 0
    name = ""
    machine = "localhost"
    i = 1
    while (i < len(sys.argv)):
        if (sys.argv[i] == "-p"):
            if (sys.argv[i + 1].isdigit() == False):
                print("Bad usage: port must be a number")
                return 84
            port = int(sys.argv[i + 1])
            i += 2
            continue
        if (sys.argv[i] == "-n"):
            name = sys.argv[i + 1]
            i += 2
            continue
        if (sys.argv[i] == "-h"):
            machine = sys.argv[i + 1]
            i += 2
            continue
        print("Bad usage: unknown argument")
        usage()
        return 84
    if (port == 0 or name == ""):
        print("Bad usage: mandatory arguments missing")
        usage()
        return 84
    if (connectToServer(port, name, machine) == 1):
        return 84
    return 0

if __name__ == '__main__':
    sys.exit(main())
