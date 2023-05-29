#!/usr/bin/env python3

from zappy_ia.Client import Client
import sys

if __name__ == "__main__":
    client = Client(int(sys.argv[2]))
    client.input(sys.argv[4] + "\n")
    print(client.output())
    print(client.output())
    client.stopClient()
