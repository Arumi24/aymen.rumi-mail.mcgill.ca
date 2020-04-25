#include <stddef.h>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

struct Node
{
    int value;
    Node *left;
    Node *right;
    Node *parent;
    int level;
    Node *extraPointer;
};

class MinHeap
{
public:
    MinHeap();
    void insert(int value);
    void heapify(Node *node);
    void remove(int value);
    void printTree();
    int height;
    int countNodes();

    Node *root;

private:
    void insert(int value, Node *node);
    void bubbleUp(Node *node);
    void remove(int value, Node *node);
    void bubbleDown(Node *node);
    int leftMostLeaf(Node *node);
    void printTree(Node *node, int level);

    int countNodes(Node *node);
};

class MaxHeap
{
public:
    MaxHeap();
    void insert(int value);
    void heapify(Node *node);
    void remove(int value);
    void printTree();
    int height;

private:
    void insert(int value, Node *node);
    void bubbleUp(Node *node);
    void printTree(Node *node, int level);
    Node *root;
};

MinHeap::MinHeap()
{
    root = NULL;
}

void MinHeap::bubbleUp(Node *node)
{
    if (node->parent != NULL)
    {
        if (node->parent->value > node->value)
        {
            int temp = node->value;
            node->value = node->parent->value;
            node->parent->value = temp;
            bubbleUp(node->parent);
        }
    }
}

int MinHeap::countNodes(Node *node)
{

    if (node->left != NULL && node->right != NULL)
    {

        return 2 + countNodes(node->left) + countNodes(node->right);
    }
    else if (node->left != NULL && node->right == NULL)
    {
        return 1 + countNodes(node->left);
    }
    else if (node->left == NULL && node->right != NULL)
    {
        return 1 + countNodes(node->right);
    }
    else
    {
        return 0;
    }
}

int MinHeap::countNodes()
{
    return countNodes(root) + 1;
}

void MinHeap::insert(int value, Node *node)
{
    if (node->left == NULL && node->right == NULL)
    {
        node->left = new Node;
        node->left->value = value;
        node->left->level = node->level + 1;
        node->left->left = NULL;
        node->left->right = NULL;
        node->left->parent = node;
        node->extraPointer = root;
        bubbleUp(node->left);
        root->extraPointer = node->left;

        if (node->left->level > height)
        {
            height = node->left->level;
        }
    }
    else if (node->left != NULL && node->right == NULL)
    {
        node->right = new Node;
        node->right->value = value;
        node->right->level = node->level + 1;
        node->right->left = NULL;
        node->right->right = NULL;
        node->right->parent = node;
        node->extraPointer = root;
        bubbleUp(node->right);
        root->extraPointer = node->right;

        if (node->right->level > height)
        {
            height = node->left->level;
        }
    }
    else if (node->left != NULL && node->right != NULL)
    {
        if (countNodes(node->left) > countNodes(node->right))
        {
            cout << "here bitches" << endl;
            cout << "left tree is " << countNodes(node->left) << endl;
            cout << "right tree is " << countNodes(node->right) << endl;
            cout << endl;
            if (countNodes(node->left) % 2 != 0)
            {
                cout << "inserting " << value << " left" << endl;
                insert(value, node->left);
            }
            else if (countNodes(node->left) % 2 == 0)
            {
                cout << "inserting " << value << " right" << endl;
                insert(value, node->right);
            }
        }
        else if (countNodes(node->left) == countNodes(node->right))
        {
            cout << "left tree is " << countNodes(node->left) << endl;
            cout << "right tree is " << countNodes(node->right) << endl;
            cout << "inserting " << value << " left throught middle" << endl;
            cout << endl;
            insert(value, node->left);
        }
    }
}

void MinHeap::insert(int value)
{
    if (root == NULL)
    {
        root = new Node;
        root->parent = NULL;
        root->value = value;
        root->left = NULL;
        root->right = NULL;
        root->level = 0;
        root->extraPointer = NULL;
        height = root->level;
    }
    else
    {
        insert(value, root);
    }
}

void MinHeap::remove(int value, Node *node)
{
    if (node->value == value)
    {
        node->value = leftMostLeaf(node);
        bubbleDown(node);
    }
    else
    {

        if (node->left != NULL)
        {

            remove(value, node->left);
        }
        if (node->right != NULL)
        {

            remove(value, node->right);
        }
    }
}

int MinHeap::leftMostLeaf(Node *node)
{
    int value = node->extraPointer->extraPointer->value;

    if (node->extraPointer->extraPointer->parent->left != NULL && node->extraPointer->extraPointer->parent->left->value == node->extraPointer->extraPointer->value)
    {
        node->extraPointer->extraPointer->parent->left = NULL;
    }

    if (node->extraPointer->extraPointer->parent->right != NULL &&
        node->extraPointer->extraPointer->parent->right->value == node->extraPointer->extraPointer->value)
    {

        node->extraPointer->extraPointer->parent->right = NULL;
    }

    return value;
}

void MinHeap::bubbleDown(Node *node)
{

    if (node->left != NULL && node->right != NULL)
    {

        int left = node->left->value;
        int right = node->right->value;

        if (left > right)
        {
            node->left->value = node->value;
            node->value = left;
            bubbleDown(node->left);
        }
        else
        {
            node->right->value = node->value;
            node->value = right;
            bubbleDown(node->right);
        }
    }
    if (node->left != NULL && node->right == NULL)
    {
        cout << 2 << endl;
        int temp = node->right->value;

        node->right->value = node->value;

        node->value = temp;

        bubbleDown(node->right);
    }
    if (node->left == NULL && node->right != NULL)
    {
        cout << 3 << endl;
        int temp = node->left->value;

        node->left->value = node->value;

        node->value = temp;

        bubbleDown(node->left);
    }
}

void MinHeap::remove(int value)
{
    if (value == root->value)
    {
        root->value = root->extraPointer->value;

        if (root->extraPointer->parent->left != NULL && root->extraPointer->parent->left->value == root->extraPointer->value)
        {
            root->extraPointer->parent->left = NULL;
        }
        if (root->extraPointer->parent->right != NULL && root->extraPointer->parent->right->value == root->extraPointer->value)
        {
            root->extraPointer->parent->right = NULL;
        }

        bubbleDown(root);
    }
    else
    {
        if (root->left != NULL)
        {
            remove(value, root->left);
        }

        if (root->right != NULL)
        {
            remove(value, root->right);
        }
    }
}

void MinHeap::printTree(Node *node, int level)
{
    if (level == 0)
    {
        cout << node->value << " ";
    }
    else
    {
        if (node->left != NULL)
        {
            printTree(node->left, level - 1);
        }
        if (node->right != NULL)
        {
            printTree(node->right, level - 1);
        }
    }
}

void MinHeap::printTree()
{
    for (int i = 0; i <= height; i++)
    {
        printTree(root, i);
        cout << endl;
    }
}

MaxHeap::MaxHeap()
{
    root = NULL;
}

void MaxHeap::bubbleUp(Node *node)
{
    if (node->parent != NULL)
    {
        if (node->parent->value < node->value)
        {
            int temp = node->value;
            node->value = node->parent->value;
            node->parent->value = temp;
            bubbleUp(node->parent);
        }
    }
}

void MaxHeap::insert(int value, Node *node)
{
    if (node->left == NULL)
    {
        node->left = new Node;
        node->left->value = value;
        node->left->level = node->level + 1;
        node->left->left = NULL;
        node->left->right = NULL;
        node->left->parent = node;
        bubbleUp(node->left);

        if (node->left->level > height)
        {
            height = node->left->level;
        }
    }
    else if (node->right == NULL)
    {
        node->right = new Node;
        node->right->value = value;
        node->right->level = node->level + 1;
        node->right->left = NULL;
        node->right->right = NULL;
        node->right->parent = node;
        bubbleUp(node->right);

        if (node->right->level > height)
        {
            height = node->left->level;
        }
    }
    else if (node->left != NULL)
    {
        insert(value, node->left);
    }
    else
    {
        insert(value, node->right);
    }
}

void MaxHeap::insert(int value)
{
    if (root == NULL)
    {
        root = new Node;
        root->parent = NULL;
        root->value = value;
        root->left = NULL;
        root->right = NULL;
        root->level = 0;
        height = root->level;
    }
    else
    {
        insert(value, root);
    }
}

void MaxHeap::printTree(Node *node, int level)
{

    if (level == 0)
    {
        cout << node->value << " ";
    }
    else
    {
        if (node->left != NULL)
        {
            printTree(node->left, level - 1);
        }
        if (node->right != NULL)
        {
            printTree(node->right, level - 1);
        }
    }
}

void MaxHeap::printTree()
{
    for (int i = 0; i <= height; i++)
    {
        printTree(root, i);
        cout << endl;
    }
}

int main()
{
    MinHeap heap;

    cout << "hello" << endl;

    for (int i = 35; i > 0; i--)
    {
        heap.insert(i);
    }

    heap.printTree();

    cout << endl;
    heap.remove(1);
    heap.printTree();
}