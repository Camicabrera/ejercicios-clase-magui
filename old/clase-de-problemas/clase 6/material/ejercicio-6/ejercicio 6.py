from Tree import BinaryTree, Node

def is_leaf(node: Node):
    return node.get_right_tree() == None and node.get_left_tree() == None


def pertenece(node: Node, value: any) -> bool:
    #TODO
    print(node, value)
    return True
    
root = Node(10)
node_2 = Node(5)
node_3 = Node(8)
root.set_left_tree(node_2)
root.set_right_tree(node_3)
node_4 = Node(3)
node_5 = Node(6)
node_2.set_left_tree(node_4)
node_2.set_right_tree(node_5)
node_6 = Node(7)
node_7 = Node(9)
node_3.set_left_tree(node_6)
node_3.set_right_tree(node_7)

tree= BinaryTree(root)

root_2 = Node(10)
node_2_2 = Node(3)
node_3_2 = Node(4)
root.set_left_tree(node_2_2)
root.set_right_tree(node_3_2)
node_4_2 = Node(2)
node_5_2 = Node(1)
node_2_2.set_left_tree(node_4_2)
node_2_2.set_left_tree(node_5_2)


tree_2 = BinaryTree(root_2)

print(pertenece(tree.get_root(), 9))
print(pertenece(tree_2.get_root(), 29))
