from Tree import BinaryTree, Node

def isLeaf(node):
    return node.getRightTree() == None and node.getLeftTree() == None

def ejercicioIII(node):
    
    if(node is None):
        return 0
    
    if(isLeaf(node)):
        return 1
    
    heightLeft = ejercicioIII(node.getLeftTree())
    heightRight = ejercicioIII(node.getRightTree())

    return max(heightLeft, heightRight) + 1

root = Node(1)
node_2 = Node(2)
node_3 = Node(3)
root.setLeftTree(node_2)
root.setRightTree(node_3)
node_4 = Node(4)
node_2.setLeftTree(node_4)


tree = BinaryTree(root)

print(ejercicioIII(tree.getRoot()))
