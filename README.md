# Red-Black Tree Implementation in C++

This project contains a C++ implementation of a **Red-Black Tree (RBT)** data structure, which is a self-balancing binary search tree. It maintains balance through node colors and rotations, ensuring operations like insertion, deletion, and lookup can be done efficiently in O(log n) time.

---

## Features

- **Node Structure**: Each node stores an integer value, color (RED or BLACK), and pointers to its parent and children.
- **Insertion**: Adds nodes while maintaining Red-Black Tree properties using recoloring and rotations.
- **Deletion**: Removes nodes with necessary fixes to preserve tree balance.
- **Rotations**: Left and right rotations for balancing the tree during insertions and deletions.
- **Traversal**: Level-order traversal with node color output.
- **Sentinel NIL Node**: A sentinel node used to represent null leaves and simplify code logic.

---

## Code Structure

### `enum Color`
Defines two colors for nodes:
- `RED`
- `BLACK`

### `struct RBTreeNode`
- `int data`: Node value
- `Color color`: Node color
- `RBTreeNode *left`, `*right`, `*parent`: Pointers to children and parent
- Constructor initializes node with a given value and defaults to RED.

### `class RedBlackTree`
- Maintains root pointer and a sentinel NIL node.
- Methods include:
  - `Insert(int value)`: Insert new nodes maintaining RBT properties.
  - `deletion(int value)`: Delete a node with a given value.
  - `leftRotation(RBTreeNode* x)`, `rightRotation(RBTreeNode* x)`: Perform rotations.
  - `fixInsert(RBTreeNode* node)`, `fixDelete(RBTreeNode* node, int val)`: Fix violations after insert or delete.
  - `print()`: Prints tree nodes in level order with their colors.

---

## Usage

1. Create an instance of `RedBlackTree`.
2. Use `Insert` to add values.
3. Use `deletion` to remove values.
4. Call `print` to display the tree structure with node colors.

---

## Example

```cpp
RedBlackTree tree;
tree.Insert(tree.getRoot(), 10);
tree.Insert(tree.getRoot(), 20);
tree.Insert(tree.getRoot(), 15);
tree.print();
tree.deletion(tree.getRoot(), 15);
tree.print();
