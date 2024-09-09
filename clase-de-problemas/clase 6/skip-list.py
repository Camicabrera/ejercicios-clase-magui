import random

class Node:
    def __init__(self, value):
        self.value = value
        self.next = None  # Pointer to the next node at the same level
        self.down = None  # Pointer to the node at the lower level

class SkipList:
    def __init__(self):
        # Create the head of the Skip List
        self.head = Node(None)  # Head node without value
        # Initial maximum level of the Skip List (single level)
        self.max_level = 0
    
    def insert(self, value):
        # TODO
        return True

    def contains(self, value):
        current = self.head
        # Traverse from top level to bottom
        while current:
            # Move forward while the next node is less than the value
            while current.next and current.next.value < value:
                current = current.next
            # If we find the value, return True
            if current.next and current.next.value == value:
                return True
            # Move down to the lower level
            current = current.down
        return False

    def delete(self, value):
        # TODO
        return True
