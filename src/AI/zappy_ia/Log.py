def configure_file(filename: str):
    open(file=filename, mode='x').close()
    
def write_to_file(filename: str, content: str):
    with open(filename, 'a') as f:
        f.write(content)