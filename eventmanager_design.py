
'''
PART 1
You are given an initial list of events, where each event has  a unique
eventId and priority.

Implement the EventManager class 

EventManager(int[][] events) -> init given events where event[i] = [eventId, eventPriority]

void updatePriority(eventId, priority) -> updates priority of an active event.

int pollHighest() -> removes and returns the  active event with the highest priority.
- If many events with same priority, return smallest eventId.
- If no active events, return -1

Additional:
    - If event not removed by pollHighest then active.
    - All values of eventId unique
    - For every call to updatePriority, eventId refers to an active event
'''

import heapq

class EventManager:
    def __init__(self, initEvents):
        self.heap = []

        for i in range(len(initEvents)):
            id, prior = initEvents[i]
            heapq.heappush_max(self.heap ,(prior, id))
    
    def updatePriority(self, eventId: int, newPriority: int) -> None:
        for i in range(len(self.heap)):
            if self.heap[i][1] == eventId:
                self.heap[i][0] = newPriority
                heapq.heapify_max(self.heap)
                break
                    

    def pollHighest(self) -> int:
        if not self.heap:
            return -1

        minimumID = float('inf')
        priority = self.heap[0][0]
        for i in range(len(self.heap)):
            if self.heap[i][0] != priority:
                break

            minimumID = min(minimumID, self.heap[i][1])
        
        self.heap.remove((priority, minimumID))
        return minimumID


manager = EventManager([[1, 1], [2, 2], [3, 3], [4, 4], [5, 4], [6, 4]])
manager.pollHighest()

print(manager.heap)
