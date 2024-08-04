from Tree import BinaryTree, Node

def isLeaf(node):
    return node.getRightTree() == None and node.getLeftTree() == None


def pertenece(node, value):
    #TODO
    return True
    
root = Node(10)
node_2 = Node(5)
node_3 = Node(8)
root.setLeftTree(node_2)
root.setRightTree(node_3)
node_4 = Node(3)
node_5 = Node(6)
node_2.setLeftTree(node_4)
node_2.setRightTree(node_5)
node_6 = Node(7)
node_7 = Node(9)
node_3.setLeftTree(node_6)
node_3.setRightTree(node_7)

tree= BinaryTree(root)


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

print(pertenece(tree.getRoot()), 9)
print(pertenece(tree_2.getRoot()), 29)
