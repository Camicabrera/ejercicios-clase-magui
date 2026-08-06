from Tree import BinaryTree, Node

def sum(node):
    if node is None:
        return 0
    return node.getValue() + sum(node.getLeftTree()) + sum(node.getRightTree())

def isSumTree(node):
    if node is None or (node.getLeftTree() is None and node.getRightTree()):
        return True
    left_sum = sum(node.getLeftTree())
    right_sum = sum(node.getRightTree())

    return node.getValue() == left_sum + right_sum and isSumTree(node.getRightTree()) and isSumTree(node.getLeftTree())
    
root = Node(1)
node_2 = Node(2)
node_3 = Node(3)
root.setLeftTree(node_2)
root.setRightTree(node_3)
node_4 = Node(4)
node_2.setLeftTree(node_4)

tree = BinaryTree(root)



root_2 = Node(10)
node_2_2 = Node(3)
node_3_2 = Node(4)
root.setLeftTree(node_2_2)
root.setRightTree(node_3_2)
node_4_2 = Node(2)
node_5_2 = Node(1)
node_2_2.setLeftTree(node_4_2)
node_2_2.setLeftTree(node_5_2)


tree_2 = BinaryTree(root_2)

print(isSumTree(tree.getRoot()))
print(isSumTree(tree_2.getRoot()))
