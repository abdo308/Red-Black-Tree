#include <bits/stdc++.h>
using namespace std;
enum Color
{
    RED,
    BLACK
}; // Define two possible colors

struct RBTreeNode
{
    int data;           // Key or data stored in the node
    Color color;        // Color of the node (RED or BLACK)
    RBTreeNode *left;   // Pointer to the left child
    RBTreeNode *right;  // Pointer to the right child
    RBTreeNode *parent; // Pointer to the parent node

    // Constructor for creating a new node
    RBTreeNode(int value) : data(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree
{
private:
    RBTreeNode *root; // Pointer to the root of the tree
    RBTreeNode *NIL;  // Sentinel node representing "null" nodes
    void leftRotation(RBTreeNode *x)
    {
        RBTreeNode *y = x->right;
        x->right = y->left;
        if (y->left != NIL)
        {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->left)
        {
            x->parent->left = y;
        }
        else
        {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
    void rightRotation(RBTreeNode *x)
    {
        RBTreeNode *y = x->left;
        x->left = y->right;
        if (y->right != NIL)
        {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr)
        {
            this->root = y;
        }
        else if (x == x->parent->right)
        {
            x->parent->right = y;
        }
        else
        {
            x->parent->left = y;
        }
        y->right = x;
        x->parent = y;
    }
    void fixInsert(RBTreeNode *newNode)
    {
        while (newNode != this->root && newNode->parent->color == RED && newNode->color == RED)
        {
            RBTreeNode *grandParent = newNode->parent->parent;
            RBTreeNode *uncle;
            if (newNode->parent == grandParent->right)
            {
                uncle = grandParent->left;
            }
            else
            {
                uncle = grandParent->right;
            }
            // first case if uncle is red
            if (uncle->color == RED)
            {
                uncle->color = BLACK;
                newNode->parent->color = BLACK;
                grandParent->color = RED;
                newNode = grandParent;
                continue;
            }
            // second and third test cases
            else
            {
                // RL case
                if (newNode->parent == grandParent->right && newNode == newNode->parent->left)
                {
                    rightRotation(newNode->parent);
                    swap(newNode->parent->color, newNode->color);
                    leftRotation(newNode->parent);
                    continue;
                }
                // RR case
                if (newNode->parent == grandParent->right && newNode == newNode->parent->right)
                {
                    leftRotation(grandParent);
                    swap(newNode->parent->color, grandParent->color);
                    newNode = newNode->parent;
                    continue;
                }
                // LL case
                if (newNode->parent == grandParent->left && newNode == newNode->parent->left)
                {
                    rightRotation(grandParent);
                    swap(newNode->parent->color, grandParent->color);
                    newNode = newNode->parent;
                    continue;
                }
                // LR case
                if (newNode->parent == grandParent->left && newNode == newNode->parent->right)
                {
                    leftRotation(newNode->parent);
                    swap(newNode->parent->color, newNode->color);
                    rightRotation(newNode->parent);
                    continue;
                }
            }
        }
        this->root->color = BLACK;
    }
    RBTreeNode *successor(RBTreeNode *target)
    {
        if (target->right != NIL)
        { // Case 1: Right subtree exists
            RBTreeNode *current = target->right;
            while (current->left != NIL)
            {
                current = current->left; // Find the leftmost node in the right subtree
            }
            return current;
        }
        return target;
    }
    RBTreeNode *predecessor(RBTreeNode *target)
    {
        if (target->left != NIL)
        { // Case 1: Left subtree exists
            RBTreeNode *current = target->left;
            while (current->right != NIL)
            {
                current = current->right; // Find the rightmost node in the left subtree
            }
            return current;
        }
        return target;
    }
    void fixDelete(RBTreeNode *target, int val)
    {
        // Case: The node to delete has two children
        if ((target->left != NIL || target->right != NIL) && target->data == val)
        {
            RBTreeNode *tmp = successor(target);
            if (target == tmp)
            {
                tmp = predecessor(target);
            }

            swap(tmp->data, target->data); // Swap values
            target = tmp;
        }
        RBTreeNode *parent = target->parent;
        if (parent == nullptr)
        {
            target->color = BLACK;
            return;
        }
        // if target on the left of the parent
        if (parent->left == target)
        {

            // case if the target node is red
            if (target->color == RED)
            {
                parent->left = NIL;
                parent->left->parent = parent;
                delete target;
                return;
            }

            RBTreeNode *sibling = parent->right; // the sibling of the target
            // case if the sibling is black and children are black
            if (sibling->color == BLACK && sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                // delete in the first call
                if (target->data == val)
                {
                    delete target;
                    parent->left = NIL;
                    parent->left->parent = parent;
                }
                if (sibling != NIL)
                    sibling->color = RED;

                if (parent->color == RED)
                {
                    parent->color = BLACK;
                }
                else
                {
                    fixDelete(parent, val);
                }
                return;
            }
            // case if the sibling is red
            if (sibling->color == RED)
            {
                swap(sibling->color, parent->color);
                leftRotation(parent);
                fixDelete(target, val);
                return;
            }
            // case if the sibling is black and near child is red
            if (sibling->color == BLACK && sibling->left->color == RED)
            {
                swap(sibling->color, sibling->left->color);
                rightRotation(sibling);
                fixDelete(target, val);
                return;
            }
            // case if the sibling is black and near child is black
            if (sibling->color == BLACK && sibling->right->color == RED)
            {
                swap(parent->color, sibling->color);
                sibling->right->color = BLACK;
                parent->left = NIL;
                parent->left->parent = parent;
                leftRotation(parent);
                delete target;
                return;
            }
        }
        // if target on the right of the parent
        else
        {
            // case if the target node is red
            if (target->color == RED)
            {
                parent->right = NIL;
                parent->right->parent = parent;
                delete target;
                return;
            }

            RBTreeNode *sibling = parent->left; // the sibling of the target
            // case if the sibling is black and children are black
            if (sibling->color == BLACK && sibling->left->color == BLACK && sibling->right->color == BLACK)
            {
                // delete in the first call
                if (target->data == val)
                {
                    delete target;
                    parent->right = NIL;
                    parent->right->parent = parent;
                }
                if (sibling != NIL)
                    sibling->color = RED;

                if (parent->color == RED)
                {
                    parent->color = BLACK;
                }
                else
                {
                    fixDelete(parent, val);
                }
                return;
            }
            // case if the sibling is red
            if (sibling->color == RED)
            {
                swap(sibling->color, parent->color);
                rightRotation(parent);
                fixDelete(target, val);
                return;
            }
            // case if the sibling is black and near child is red
            if (sibling->color == BLACK && sibling->right->color == RED)
            {
                swap(sibling->color, sibling->right->color);
                leftRotation(sibling);
                fixDelete(target, val);
                return;
            }
            // case if the sibling is black and near child is black
            if (sibling->color == BLACK && sibling->left->color == RED)
            {
                swap(parent->color, sibling->color);
                sibling->left->color = BLACK;
                parent->right = NIL;
                parent->right->parent = parent;
                rightRotation(parent);
                if (target->data == val)
                {
                    delete target;
                }
                return;
            }
        }
    }

public:
    // Constructor initializes the tree
    RedBlackTree()
    {
        // Initialize TNULL as a BLACK node
        NIL = new RBTreeNode(0);
        NIL->color = BLACK;
        root = NIL;
    }

    RBTreeNode *getRoot()
    {
        return root;
    }

    void deletion(RBTreeNode *root, int value)
    {
        RBTreeNode *target = this->root;
        bool checkRoot = false;
        while (target != NIL && target->data != value)
        {
            checkRoot = true;
            if (target->data == value)
            {
                break;
            }
            if (target->data < value)
            {
                target = target->right;
            }
            else
                target = target->left;
        }
        if (!checkRoot && target->left == NIL && target->right == NIL)
        {
            delete target;
            this->root = NIL;
            return;
        }
        fixDelete(target, target->data);
    }
    void Insert(RBTreeNode *root, int value)
    {
        RBTreeNode *newNode = new RBTreeNode(value);
        newNode->right = NIL;
        newNode->left = NIL;
        RBTreeNode *current = this->root;
        RBTreeNode *parent = nullptr;

        while (current != NIL)
        {
            parent = current;
            if (current->data < value)
                current = current->right;
            else
                current = current->left;
        }
        newNode->parent = parent;
        if (parent == nullptr)
        {
            newNode->color = BLACK;
            this->root = newNode;
            return;
        }
        else if (value < parent->data)
        {
            parent->left = newNode;
        }
        else
        {
            parent->right = newNode;
        }
        fixInsert(newNode);
    }
    // Level Order printing with color

    void print()
    {
        if (root == NIL)
            return;
        queue<RBTreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            RBTreeNode *tmp = q.front();
            q.pop();
            cout << tmp->data << ' ' << tmp->color << '\n';

            // if (tmp->parent != nullptr)
            //     cout << tmp->data << ' ' << tmp->color << ' ' << tmp->parent->data << '\n';
            if (tmp->left != NIL)
                q.push(tmp->left);
            if (tmp->right != NIL)
                q.push(tmp->right);
        }
    }
};