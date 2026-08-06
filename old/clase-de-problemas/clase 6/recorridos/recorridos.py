from Tree import BinaryTree, Node

def visit_tree_in_order(node: Node, fn):
    # TODO
    return

def visit_tree_in_post_order(node: Node, fn):
    # TODO
    return

def visit_tree_in_pre_order(node: Node, fn):
    # TODO
    return


root = Node(1)
node_2 = Node(2)
node_3 = Node(3)
root.set_left_tree(node_2)
root.set_right_tree(node_3)
node_4 = Node(4)
node_5 = Node(5)
node_2.set_left_tree(node_4)
node_2.set_right_tree(node_5)
node_6 = Node(6)
node_7 = Node(7)
node_3.set_left_tree(node_6)
node_3.set_right_tree(node_7)

tree = BinaryTree(root)

print("PRE ORDER")
visit_tree_in_pre_order(tree.get_root(), print)
print("IN ORDER")
visit_tree_in_order(tree.get_root(), print)
print("POST ORDER")
visit_tree_in_post_order(tree.get_root(), print)