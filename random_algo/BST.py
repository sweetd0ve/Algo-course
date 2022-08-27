class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.value = key


class BinarySearchTree:
    def __init__(self):
        self.root = None

    def insert_in_bst(self, root_node, key):
        if root_node is None:
            root_node = Node(key)
        if root_node.value < key:
            if root_node.right is None:
                root_node.right = Node(key)
            else:
                self.insert_in_bst(root_node.right, key)
        elif root_node.value > key:
            if root_node.left is None:
                root_node.left = Node(key)
            else:
                self.insert_in_bst(root_node.left, key)

    def create_bst(self, array):
        num_nodes = len(array) - 1
        self.root = Node(array[0])
        for node_index in range(1, num_nodes):
            self.insert_in_bst(self.root, array[node_index])

    def inorder(self, root_node, sorted_keyes):
        if root_node:
            self.inorder(root_node.left, sorted_keyes)
            sorted_keyes.append(root_node.value)
            self.inorder(root_node.right, sorted_keyes)


def print_search(array):
    tree = BinarySearchTree()
    tree.create_bst(array)
    sorted_keyes = []
    tree.inorder(tree.root, sorted_keyes)
    print('\n'.join(map(str, sorted_keyes)))


def main():
    array = list(map(int, input().split()))
    print_search(array)


if __name__ == '__main__':
    main()