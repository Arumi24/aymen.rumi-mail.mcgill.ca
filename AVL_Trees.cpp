#include <stddef.h>
#include <iostream>
#include <algorithm>
using namespace std;

struct Node
{
    int value;
    Node *left;
    Node *right;
    Node *parent;
    int balanceFactor;
    int height;
};

class AVL_Tree
{
public:
    AVL_Tree();
    void insert(int value);
    void remove(int value);
    void printLevelOrder();
    void rotateRight(Node *node);
    void rotateLeft(Node *node);
    int subTreeHeight(Node *node);
    void balanceFactor(Node *node);
    void balance();
    void balance(Node *node);

    int detectUnbalance(Node *node);

    Node *root;

private:
    void insert(int value, Node *node);

    void printLevelOrder(Node *node, int level);

    int height;
};

AVL_Tree::AVL_Tree()
{
    root = NULL;
}

int AVL_Tree::detectUnbalance(Node *node)
{
    if (node->balanceFactor == 2 || node->balanceFactor == -2)
    {
        if (node->right != NULL && node->left != NULL)
        {
            return 1 + detectUnbalance(node->right) + detectUnbalance(node->left);
        }
        else if (node->right != NULL && node->left == NULL)
        {
            return 1 + detectUnbalance(node->right);
        }
        else if (node->right == NULL && node->left != NULL)
        {
            return 1 + detectUnbalance(node->left);
        }
        else
        {
            return 1;
        }
    }
    else
    {
        if (node->right != NULL && node->left != NULL)
        {
            return 0 + detectUnbalance(node->right) + detectUnbalance(node->left);
        }
        else if (node->right != NULL && node->left == NULL)
        {
            return 0 + detectUnbalance(node->right);
        }
        else if (node->right == NULL && node->left != NULL)
        {
            return 0 + detectUnbalance(node->left);
        }
        else
        {
            return 0;
        }
    }
}
void AVL_Tree::insert(int value, Node *node)
{

    if (value > node->value)
    {
        if (node->right == NULL)
        {
            node->right = new Node;
            node->right->value = value;
            node->right->right = NULL;
            node->right->left = NULL;
            node->right->height = node->height + 1;
            node->right->parent = node;

            balanceFactor(node->right);

            while (detectUnbalance(root) != 0)
            {
                balance(root);
            }

            if (node->height + 1 > height)
            {
                height = node->height + 1;
            }
        }
        else
        {
            insert(value, node->right);
        }
    }
    else
    {
        if (node->left == NULL)
        {
            node->left = new Node;
            node->left->value = value;
            node->left->right = NULL;
            node->left->left = NULL;
            node->left->height = node->height + 1;
            node->left->parent = node;
            balanceFactor(node->left);

            while (detectUnbalance(root) != 0)
            {
                balance(root);
            }

            if (node->height + 1 > height)
            {
                height = node->height + 1;
            }
        }
        else
        {
            insert(value, node->left);
        }
    }
}

void AVL_Tree::insert(int value)
{
    if (root == NULL)
    {
        root = new Node;
        root->value = value;
        root->right = NULL;
        root->left = NULL;
        root->parent = NULL;
        root->height = 0;
        balanceFactor(root);
        height = 0;
    }
    else
    {
        insert(value, root);
    }
}

void AVL_Tree::rotateRight(Node *node)
{
    if (node->parent == NULL)
    {
        node->left->parent = NULL;
        node->parent = node->left;

        if (node->parent->right == NULL)
        {
            node->left = NULL;
            node->parent->right = node;
        }
        else
        {
            node->left = node->parent->right;
            node->parent->right = node;
        }

        root = node->parent;

        balanceFactor(node);
    }
    else
    {
        if (node->parent->left != NULL && node->parent->left == node)
        {
            node->left->parent = node->parent;
            node->parent->left = node->left;
            node->parent = node->left;

            if (node->parent->right == NULL)
            {
                node->left = NULL;
                node->parent->right = node;
            }
            else
            {
                node->left = node->parent->right;
                node->parent->right = node;
            }

            balanceFactor(node);
        }
        else if (node->parent->right != NULL && node->parent->right == node)
        {
            node->left->parent = node->parent;
            node->parent->right = node->left;
            node->parent = node->left;
            if (node->parent->right == NULL)
            {
                node->left = NULL;
                node->parent->right = node;
            }
            else
            {
                node->left = node->parent->right;
                node->parent->right = node;
            }
            balanceFactor(node);
        }
    }
}

void AVL_Tree::rotateLeft(Node *node)
{

    if (node->parent == NULL)
    {
        node->right->parent = NULL;
        node->parent = node->right;

        if (node->parent->left == NULL)
        {
            node->right = NULL;
            node->parent->left = node;
        }
        else
        {
            node->right = node->parent->left;
            node->parent->left = node;
        }

        root = node->parent;
        balanceFactor(node);
    }
    else
    {
        if (node->parent->left != NULL && node->parent->left == node)
        {
            node->right->parent = node->parent;
            node->parent->left = node->right;
            node->parent = node->right;

            if (node->parent->left == NULL)
            {
                node->right = NULL;
                node->parent->left = node;
            }
            else
            {
                node->right = node->parent->left;
                node->parent->left = node;
            }
            balanceFactor(node);
        }
        else if (node->parent->right != NULL && node->parent->right == node)
        {
            node->right->parent = node->parent;
            node->parent->right = node->right;
            node->parent = node->right;

            if (node->parent->left == NULL)
            {
                node->right = NULL;
                node->parent->left = node;
            }
            else
            {
                node->right = node->parent->left;
                node->parent->left = node;
            }
            balanceFactor(node);
        }
    }
}

void AVL_Tree::balance(Node *node)
{

    if (node->balanceFactor == 2 && (node->left != NULL && (node->left->balanceFactor == 1 || node->left->balanceFactor == -1)))
    {

        if (node->left->balanceFactor == 1)
        {

            rotateRight(node);
        }
        else if (node->left->balanceFactor == -1)
        {

            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    else if (node->balanceFactor == -2 && (node->right != NULL && (node->right->balanceFactor == 1 || node->right->balanceFactor == -1)))
    {

        if (node->right->balanceFactor == 1)
        {
            rotateRight(node->right);
            rotateLeft(node);
        }
        else if (node->right->balanceFactor == -1)
        {
            rotateLeft(node);
        }
    }
    else
    {
        if (node->left != NULL)
        {

            balance(node->left);
        }
        if (node->right != NULL)
        {
            balance(node->right);
        }
    }
}

void AVL_Tree::printLevelOrder(Node *node, int level)
{

    if (level == 0)
    {
        cout << node->value << " " << node->balanceFactor << " ,";
    }
    else
    {
        if (node->left != NULL)
        {
            printLevelOrder(node->left, level - 1);
        }
        if (node->right != NULL)
        {
            printLevelOrder(node->right, level - 1);
        }
    }
}

int AVL_Tree::subTreeHeight(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    else if (node->left == NULL && node->right == NULL)
    {
        return 1;
    }
    else if (node->left != NULL && node->right != NULL)
    {
        return 1 + max(subTreeHeight(node->left), subTreeHeight(node->right));
    }
    else if (node->left != NULL && node->right == NULL)
    {
        return 1 + subTreeHeight(node->left);
    }
    else if (node->left == NULL && node->right != NULL)
    {
        return 1 + subTreeHeight(node->right);
    }
    else
    {
        return 0;
    }
}

void AVL_Tree::balanceFactor(Node *node)
{

    if (node->right == NULL && node->left == NULL)
    {
        node->balanceFactor = 0;
    }
    else if (node->right != NULL && node->left == NULL)
    {
        node->balanceFactor = -subTreeHeight(node->right);
    }
    else if (node->right == NULL && node->left != NULL)
    {
        node->balanceFactor = subTreeHeight(node->left);
    }
    else if (node->right != NULL && node->left != NULL)
    {
        node->balanceFactor = subTreeHeight(node->left) - subTreeHeight(node->right);
    }

    if (node->parent != NULL)
    {

        balanceFactor(node->parent);
    }
}

void AVL_Tree::printLevelOrder()
{
    for (int i = 0; i <= height; i++)
    {
        printLevelOrder(root, i);
        cout << endl;
    }
}

int main()
{
    AVL_Tree tree;

    tree.insert(10);
    tree.insert(12);
    tree.insert(11);
    tree.insert(15);
    tree.insert(7);
    tree.insert(8);
    tree.insert(13);
    tree.insert(20);
    tree.insert(21);
    tree.insert(16);
    tree.insert(14);
    tree.insert(1);
    tree.insert(2);
    tree.insert(13);
    tree.insert(30);
    tree.insert(31);


    tree.printLevelOrder();

    cout << endl;
}
