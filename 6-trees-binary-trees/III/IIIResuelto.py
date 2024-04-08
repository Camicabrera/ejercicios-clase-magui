from Tree import BinaryTree, Node

def isLeaf(node):
    return node.getRightTree() == None and node.getLeftTree() == None

def ejericioIII(node):
    
    if(node == None): 
        return 0

    if(isLeaf(node)):
        return 1
    
    alturaHijoIzquierdo = ejericioIII(node.getLeftTree())
    alturaHijoDerecho = ejericioIII(node.getRightTree())
    
    if(alturaHijoIzquierdo > alturaHijoDerecho): 
        return alturaHijoIzquierdo + 1
    elif(alturaHijoIzquierdo < alturaHijoDerecho):
        return alturaHijoDerecho + 1
    else:
        return alturaHijoDerecho + 1



root = Node(1)
node_2 = Node(2)
node_3 = Node(3)
root.setLeftTree(node_2)
root.setRightTree(node_3)
node_4 = Node(4)
node_2.setLeftTree(node_4)


tree = BinaryTree(root)

print(ejericioIII(tree.getRoot()))
