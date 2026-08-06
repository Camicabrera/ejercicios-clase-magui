from Tree import BinaryTree, Node

def isLeaf(node):
    return node.getRightTree() == None and node.getLeftTree() == None


def isBTS(node):

    if(node == None or isLeaf(node)):
        return True
    
    rightTree = node.getRightTree()
    leftTree = node.getLeftTree()

    isRightTreeBTS = isBTS(rightTree)
    isLeftTreeBTS = isBTS(leftTree)

    if(not rightTree): 
        return isLeftTreeBTS and node.getValue() > leftTree.getValue()


    if(not leftTree): 
        return isRightTreeBTS and node.getValue() <= rightTree.getValue()
   
   
    return rightTree.getValue() >=  node.getValue() and leftTree.getValue() < node.getValue()
    
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

print(isBTS(tree.getRoot()))
print(isBTS(tree_2.getRoot()))
