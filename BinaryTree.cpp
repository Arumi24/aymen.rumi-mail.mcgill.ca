#include <stddef.h>
#include <iostream>
using namespace std;


struct Node
{
    int key;
    Node *left;
    Node *right;

};


class BinaryTree
{
    public:
    
        BinaryTree();
        ~BinaryTree();
        void deleteTree();
        void insert(int key);
        void printTree();

    private:

        void insert(int key, Node *node);
        void printNode(Node *node);
        void printTree(Node *node);
        void deleteNode(Node *node);
        Node *root;
};


BinaryTree::BinaryTree()
{
    root=NULL;
}

BinaryTree::~BinaryTree()
{
    deleteTree();
}

void BinaryTree::deleteNode(Node *node)
{
    if(node!=NULL)
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
    if (key>node->key)
    {
        if(node->right==NULL)
        {
            node->right=new Node;
            node->right->key=key;
            node->right->right=NULL;
            node->right->left=NULL;
        }
        else
        {
            insert(key,node->right);
        }
    }
    else
    {
        if(node->left==NULL)
        {
            node->left=new Node;
            node->left->key=key;
            node->left->right=NULL;
            node->left->left=NULL;

        }
        else
        {
            insert(key,node->left);
        }   
    }
}

void BinaryTree::insert(int key)
{
    if(root!=NULL)
    {
        insert(key,root);
    }
    else
    {
        root=new Node;
        root->key=key;
        root->left=NULL;
        root->right=NULL;
    }
}



int main ()
{
  BinaryTree tree;
  tree.insert(5);
  tree.insert(10);
  tree.insert(1);

  

}