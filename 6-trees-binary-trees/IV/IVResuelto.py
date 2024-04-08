from Tree import BinaryTree, Node

def sum(root):
    if root is None:
        return 0
    return sum(root.getLeftTree()) + root.getValue() + sum(root.getRightTree())

def isSumTree(root):
    if root is None or (root.getLeftTree() is None and root.getRightTree() is None):
        return True

    left_sum = sum(root.getLeftTree())
    right_sum = sum(root.getRightTree())

    if root.getValue() == left_sum + right_sum and isSumTree(root.getLeftTree()) and isSumTree(root.getRightTree()):
        return True

    return False

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
