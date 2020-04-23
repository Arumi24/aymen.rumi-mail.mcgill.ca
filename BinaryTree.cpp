#include <stddef.h>
#include <iostream>
using namespace std;

struct Node
{
    int key_value;
    Node *left;
    Node *right;
    int level;
};

class BinaryTree
{
public:
    BinaryTree();
    ~BinaryTree();
    void deleteTree();
    void insert(int key);
    void printInOrder();
    void printPreOrder();
    void printPostOrder();
    void printLevelOrder();

    

private:
    void insert(int key, Node *node);
    void deleteNode(Node *node);
    void printInOrder(Node *node);
    void printPreOrder(Node *node);
    void printPostOrder(Node *node);
    void printLevelOrder(Node *node, int level);

    int height;
    Node *root;
};

BinaryTree::BinaryTree()
{
    root = NULL;
}

BinaryTree::~BinaryTree()
{
    deleteTree();
}

void BinaryTree::deleteNode(Node *node)
{
    if (node != NULL)
    {
        deleteNode(node->left);
        deleteNode(node->right);
        delete node;
    }
}

void BinaryTree::deleteTree()
{
    deleteNode(root);
}

void BinaryTree::insert(int key, Node *node)
{
    if (key > node->key_value)
    {
        if (node->right == NULL)
        {
            node->right = new Node;
            node->right->key_value = key;
            node->right->level = node->level + 1;
            node->right->left = NULL;
            node->right->right = NULL;

            if (height < node->right->level)
            {
                height = node->right->level;
            }
        }
        else
        {
            insert(key, node->right);
        }
    }
    else
    {
        if (node->left == NULL)
        {
            node->left = new Node;
            node->left->key_value = key;
            node->left->level = node->level + 1;
            node->left->left = NULL;
            node->left->right = NULL;

            if (height < node->left->level)
            {
                height = node->left->level;
            }
        }
        else
        {
            insert(key, node->left);
        }
    }
}

void BinaryTree::insert(int key)
{
    if (root == NULL)
    {
        root = new Node;
        root->key_value = key;
        root->left = NULL;
        root->right = NULL;
        root->level = 0;
        height = 0;
    }
    else
    {
        insert(key, root);
    }
}

void BinaryTree::printInOrder(Node *node)
{
    if (node != NULL)
    {
        printInOrder(node->left);
        cout << node->key_value << " ";
        printInOrder(node->right);
    }
}

void BinaryTree::printInOrder()
{
    printInOrder(root);
}

void BinaryTree::printPreOrder(Node *node)
{
    if (node != NULL)
    {

        cout << node->key_value << " ";
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}

void BinaryTree::printPreOrder()
{
    printPreOrder(root);
}

void BinaryTree::printPostOrder(Node *node)
{
    if (node != NULL)
    {
        printPostOrder(node->left);
        printPostOrder(node->right);
        cout << node->key_value << " ";
    }
}

void BinaryTree::printPostOrder()
{
    printPostOrder(root);
}

void BinaryTree::printLevelOrder(Node *node, int level)
{

    if (level == 0)
    {
        cout << node->key_value << " ";
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

void BinaryTree::printLevelOrder()
{
    for (int i = 0; i <= height; i++)
    {
        printLevelOrder(root, i);
    }
}

int main()
{
    BinaryTree tree;

    tree.insert(10);
    tree.insert(15);
    tree.insert(14);
    tree.insert(25);
    tree.insert(3);
    tree.insert(5);
    tree.insert(7);
    tree.insert(2);

    tree.printInOrder();
    cout << endl;
    tree.printPreOrder();
    cout << endl;
    tree.printPostOrder();
    cout << endl;
    tree.printLevelOrder();
    cout << endl;
}
