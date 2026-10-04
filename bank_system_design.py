import heapq
from collections import defaultdict

class Bank:
    def __init__(self):
        self.accounts = {}  # acc_id -> amount
        self.scheduler = [] # time , (from_acc, to_acc, amount)
        self.history = defaultdict(list)
        self.clock = 0
    
    def open_account(self, account_id: str) -> bool:
        if account_id in self.accounts:
            return False

        self.accounts[account_id] = 0
        return True

    def deposit(self, account_id: str, amount: int) -> bool:
        if account_id not in self.accounts:
            return False
        if amount < 0:
            return False

        self.accounts[account_id] += amount
        self.history[account_id].append("DEPOSIT ${amount} bal=${self.get_balance(account_id)}")
        return True

    def withdraw(self, account_id: str, amount: int) -> bool:
        if account_id not in self.accounts:
            return False
        if amount < 0:
            return False
        if self.accounts[account_id] - amount < 0:
            return False

        self.accounts[account_id] -= amount
        self.history[account_id].append("WITHDRAW -{amount} bal={self.get_balance(account_id)}")
        return True

    def transaction(self, from_acc: str, to_acc: str, amount: int) -> bool:
        self.withdraw(from_acc, amount)
        self.deposit(to_acc, amount)
        self.history[from_acc].append("TRANSFER_OUT -{amount} to={to_acc} bal={self.get_balance(from_acc)}")
        self.history[to_acc].append("TRANSFER_IN -{amount} from={from_acc} bal={self.get_balance(to_acc)}")
        return True

    def get_balance(self, account_id: str) -> int:
        if account_id not in self.accounts:
            return None

        return self.accounts[account_id] 

    def tick(self, number: int) -> bool:
        if number < 0:
            return False

        self.clock += number

        while self.scheduler and self.scheduler[0][0] <= self.clock:
            delay, args = heapq.heappop(self.scheduler)
            self.transaction(args[0], args[1], args[2])

        return True
        
 
    def schedule(self, from_acc: str, to_acc: str, amount: int, delay: int) -> bool:
        if from_acc not in self.accounts or to_acc not in self.accounts:
            return False
        if self.accounts[from_acc] < amount:
            return False
        if amount < 0:
            return False
        if delay < 0:
            return False

        delayed = delay + self.clock
        heapq.heappush(self.scheduler, (delayed, (from_acc, to_acc, amount)))

        return True

    def getHistory(self, account_id: str, number: int) -> bool:
        if account_id not in self.history:
            return False

        count = min(len(self.history[account_id]), number)
        
        historyList = self.history[account_id]

        for i in range(len(historyList) - 1, -1, -1):
            if count <= 0:
                break

            print(historyList[i])
            count -= 1

        return True



bank = Bank()

assert(bank.open_account("1")) == True
assert(bank.open_account("2")) == True
assert(bank.deposit("1", 15)) == True
assert(bank.deposit("2", 5)) == True
assert(bank.schedule("1", "2", 15, 3)) == True
assert(bank.tick(4)) == True
assert(bank.get_balance("2")) == 20
assert(bank.getHistory("1", 7)) == True
