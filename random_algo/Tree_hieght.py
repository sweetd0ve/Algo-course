class Node:
    def __init__(self, key):
        self.left = None
        self.right = None
        self.value = key


class BinarySearchTree:
    def __init__(self):
        self.root = None

    def insert_in_bst(self, current_root, key):
        if current_root is None:
            current_root = Node(key)
        if current_root.value < key:
            if current_root.right is None:
                current_root.right = Node(key)
            else:
                self.insert_in_bst(current_root.right, key)
        elif current_root.value > key:
            if current_root.left is None:
                current_root.left = Node(key)
            else:
                self.insert_in_bst(current_root.left, key)

    def create_bst(self, array):
        num_nodes = len(array) - 1
        self.root = Node(array[0])
        for node_index in range(1, num_nodes):
            self.insert_in_bst(self.root, array[node_index])

    def height_of_bst(self, node):
        height_left = 0
        height_right = 0
        if node is None:
            return 0
        if node.left is not None:
            height_left = self.height_of_bst(node.left)
        if node.right is not None:
            height_right = self.height_of_bst(node.right)
        return max(height_left, height_right) + 1


def main():
    array = list(map(int, input().split()))
    if len(array) > 1:
        tree = BinarySearchTree()
        tree.create_bst(array)
        tree_height = tree.height_of_bst(tree.root)
        print(tree_height)
    else:
        print(0)


if __name__ == '__main__':
    main()
