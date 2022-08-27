class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.value = key
        self.times = 1


class BinarySearchTree:
    def __init__(self):
        self.root = None

    def insert_in_bst(self, root_node, key):
        if root_node is None:
            root_node = Node(key)
        if root_node.value == key:
            root_node.times += 1
        elif root_node.value < key:
            if root_node.right is None:
                root_node.right = Node(key)
            else:
                self.insert_in_bst(root_node.right, key)
        else:
            if root_node.left is None:
                root_node.left = Node(key)
            else:
                self.insert_in_bst(root_node.left, key)

    def create_bst(self, array):
        num_nodes = len(array) - 1
        self.root = Node(array[0])
        for node_index in range(1, num_nodes):
            self.insert_in_bst(self.root, array[node_index])

    def inorder_traversal(self, root_node, vertex_time):
        if root_node:
            self.inorder_traversal(root_node.left, vertex_time)
            vertex_time.append((root_node.value, root_node.times))
            self.inorder_traversal(root_node.right, vertex_time)


def print_tree(array):
    tree = BinarySearchTree()
    tree.create_bst(array)
    vertex_time = []
    tree.inorder_traversal(tree.root, vertex_time)
    for pair in vertex_time:
        print(pair[0], pair[1])


def main():
    array = list(map(int, input().split()))
    print_tree(array)


if __name__ == '__main__':
    main()
