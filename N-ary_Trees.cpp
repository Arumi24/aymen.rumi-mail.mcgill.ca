#include <stddef.h>
#include <iostream>
#include <list>
#include <vector>
using namespace std;


struct Node
{
    vector<Node *> children;
    Node *parent;
    int value;
    int index;
    int depth;
};

class Tree
{
    public:
        Tree(); 
        void insertRoot(int value);   
        void insert(int value,int depth, int index);   
        void printPreOrder();
        void printPostOrder();
        

    private:
        void insert(int value,int depth, int index, Node *node);
        void printPreOrder(Node *node);
        void printPostOrder(Node *node);
        Node *root;
};


Tree::Tree()
{
    root=NULL;
}

void Tree::insert(int value,int depth, int index, Node *node)
{
    if (node->index==index && node->depth==depth)
    {
        Node *child;
        child= new Node;
        child->parent=node;
        child->depth=child->parent->depth+1;
        child->value=value;
        node->children.push_back(child);
        child->index=node->children.size()-1;

    }
    else
    {
        for(int i=0;i<node->children.size();i++)
        {
            insert(value,depth,index,node->children[i]);
        }
    }

}

void Tree::insertRoot(int value)
{
    if (root==NULL)
    {
        root= new Node;
        root->parent=NULL;
        root->depth=0;
        root->index=0;
        root->value=value;
    }
   
}

void Tree::insert(int value,int depth, int index)
{
   
    insert(value,depth, index, root);
    
}


void Tree::printPreOrder(Node *node)
{
    if (node!=NULL)
    {
        cout << node->value <<endl;

        for(int i=0;i<node->children.size();i++)
        {
            printPreOrder(node->children[i]);
        }     
    }
}

void Tree::printPreOrder()
{
    printPreOrder(root);
}


void Tree::printPostOrder(Node *node)
{
    if (node!=NULL)
    {
        

        for(int i=0;i<node->children.size();i++)
        {
            printPostOrder(node->children[i]);
        }
        
        cout << node->value <<endl;
    }
}

void Tree::printPostOrder()
{
    printPostOrder(root);
}



int main()
{
    Tree tree;
    tree.insertRoot(1);
    tree.insert(5,0,0);
    tree.insert(10,0,0);
    tree.insert(11,0,0);
    tree.insert(13,0,0);
    tree.insert(7,1,0);
    tree.insert(21,1,1);
    tree.insert(22,1,1);

    tree.printPreOrder();
    cout <<endl;
    tree.printPostOrder();
}

    
