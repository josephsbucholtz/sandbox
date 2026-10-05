
'''
PART 1
Building a storage engine behind a small config service. It keeps
everything in mem and is driven by script of commands

run_commands(["SET name james", "GET name"]) -> ["james"]
    - returns a list of strings: one per entry

GET -> gets value for key or NULL if key not found
SET -> sets key value pair 
DELETE -> deletes key (void)

Additional:
values are always single tokens
keys never contain spaces

PART 2
Add transaction feature (like db)

begin -> begins a transaction
commit -> commits all commands run in transaction. MUST SUCEEED
rollback -> if fail then rollback all changes


PART 3

'''

from collections import defaultdict

class StorageService:
    def __init__(self):
        self.map = defaultdict()
        self.copy = defaultdict()
        self.deleteStore = list()
        self.transactionFlag = False

    def get(self, key: str) -> str:
        if self.transactionFlag:
            return self.copy[key] if self.copy[key] else self.map[key]
        return self.map[key] 

    def set(self, key: str, value: str) -> None:
        if self.transactionFlag:
            self.copy[key] = value
        else:
            self.map[key] = value

    def delete(self, key: str) -> None:
        if self.transactionFlag:
            self.deleteStore.append(key)
        else:
            if key in self.map:
                del self.map[key]
            

    def run_commands(self, commands: List[str]) -> List[str]:

        output = []
        copyOut = []

        for command in commands:
            match command.split(" ")[0]:
                case "GET":
                    if self.transactionFlag:
                        copyOut.append(self.get(command.split(" ")[1]))
                    else:
                        output.append(self.get(command.split(" ")[1]))
                    

                case "SET":
                    self.set(command.split(" ")[1], command.split(" ")[2])


                case "DELETE":
                    self.delete(command.split(" ")[1])

                
                case "BEGIN":
                    self.transactionFlag = True
                

                case "COMMIT":
                    self.transactionFlag = False

                    for key, value in self.copy.items():
                        self.map[key] = value

                    for key in self.deleteStore:
                        self.delete(key)

                    output += copyOut


                case "ROLLBACK":
                    self.copy.clear()
                    self.deleteStore.clear()
                    self.transactionFlag = False
                
                case _:
                    return ["ERROR"]

        return output


engine = StorageService()

print(engine.run_commands(["SET name james", "GET name", "BEGIN", "SET name john", "DELETE name", 
                           "DELETE mark", "SET person james", "GET person", "COMMIT"]))

