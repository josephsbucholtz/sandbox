
'''
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


class EventManager:
    def __init__(self, initEvents):
        pass
    
    def updatePriority(self, eventId: int, newPriority: int):
        pass

    def int pollHighest(self):
        pass


