from zappy_ia.Client import Client


class ClientManager:
    def __init__(self, port: int, machineName: str, teamName: str):
        self._client: Client = Client(port, machineName)
        self.teamName: str = teamName
