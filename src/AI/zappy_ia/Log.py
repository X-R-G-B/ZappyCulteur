import os


class LogGood:
    def __init__(self, path: str, mode: str = "x") -> None:
        self._path = path
        self._mode = mode
        
        directory = os.path.dirname(self._path)
        os.makedirs(directory, exist_ok=True)
        
        open(self._path, self._mode).close()
    

    def info(self, content: str, end: str = "\n") -> None:
        with open(self._path, "a") as f:
            f.write(f"[INFO] {content}{end}")
    
    def debug(self, content: str, end: str = "\n") -> None:
        with open(self._path, "a") as f:
            f.write(f"[DEBUG] {content}{end}")
            
    def error(self, content: str, end: str = "\n") -> None:
        with open(self._path, "a") as f:
            f.write(f"[ERROR] {content}{end}")
            