class Node:
    def __init__(self, value):
        self.value = value
        self.left_tree = None
        self.right_tree = None
    
    def set_left_tree(self, left):
        self.left_tree = left
    
    def set_right_tree(self, right):
        self.right_tree = right
    
    def set_value(self, value):
        self.value = value
    
    def get_left_tree(self):
        return self.left_tree
    
    def get_right_tree(self):
        return self.right_tree
    
    def get_value(self):
        return self.value

class BinaryTree:
    def __init__(self, root):
        self.root = root
    def get_root(self):
        return self.root
