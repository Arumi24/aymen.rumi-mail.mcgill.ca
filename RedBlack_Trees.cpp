#include <stddef.h>
#include <iostream>
#include <algorithm>
using namespace std;

/**

Red-Black Tree Properties:

1. A node is either red or black
2. Root & leaves(NULL) are black
3. If a node is red, then it's children are black
4. All paths from a node to its NULL descendants
   contain the same number of black nodes

**/

enum Color {RED, BLACK};
enum Relationship {LeftChild,RightChild,Root};

struct Node{

        int value;
        Node *left;
        Node *right;
        Node *parent;
        Color color;
        Relationship relation;
};


class RedBlack_Tree{

    public:
        RedBlack_Tree();
        void insert(int value);
        void remove(int value);
        void restoreProperty(Node *node);
        void rightRotate(Node *node);
        void leftRotate(Node *node);
        void printLevelOrder();


    private:

        void insert(int value,Node *node);
        void remove(int value, Node *node);
        void printLevelOrder(Node *node, int level);
        Node *root;
};


RedBlack_Tree::RedBlack_Tree()
{
    root=NULL;
}

void RedBlack_Tree::rightRotate(Node *node)
{
    if(node->parent==NULL)
    {
        node->left->parent=NULL;
        root=node->left;
    }
    else
    {
        node->left->parent=node->parent;

        if(node->relation==LeftChild)
        {
            node->left->relation=LeftChild;
            node->parent->left=node->left;
        }
        else
        {
            node->left->relation=RightChild;
            node->parent->right=node->left;
        }
    }

    node->parent=node->left;
    
    if(node->left->right!=NULL)
    {
        node->left=node->left->right;
        node->left->parent=node;
    }
    node->parent->right=node;
    
    node->parent->color=BLACK;
    node->parent->right->color=RED;
    node->parent->left->color=RED;
}


void RedBlack_Tree::leftRotate(Node *node)
{
    if(node->parent==NULL)
    {
        node->right->parent=NULL;
        root=node->right;
    }
    else
    {
        node->right->parent=node->parent;

        if(node->relation==LeftChild)
        {
            node->right->relation=LeftChild;
            node->parent->left=node->right;
        }
        else
        {
            node->right->relation=RightChild;
            node->parent->right=node->right;
        }    
    }

    node->parent=node->right;

    if(node->right->left!=NULL)
    {
        node->right=node->right->left;
        node->right->parent=node;
    }
    else
    {
        node->right=NULL;
    }

    node->parent->left=node;

    node->parent->left->color=RED;

    node->parent->right->color=RED;
}

void RedBlack_Tree::restoreProperty(Node *node)
{  
    if(node==root)
    {
  
        node->color=BLACK;
    }
    else if( node!=root && node->parent->color!=BLACK)
    {
        if(node->parent->relation==LeftChild)
        {
            if(node->parent->parent->right!=NULL && node->parent->parent->right->color==RED)
            {
         
                node->parent->color=BLACK;
                node->parent->parent->right->color=BLACK;
                node->parent->parent->color=RED;
                restoreProperty(node->parent->parent);
            }

            else if(node->parent->parent->right!=NULL && node->parent->parent->right->color==BLACK)
            {
                if(node->relation==LeftChild)
                {
                    rightRotate(node->parent->parent);
                }
                else if(node->relation==RightChild)
                {
                    leftRotate(node);
                    rightRotate(node->parent->parent);
                }
            }
        }
        else if(node->parent->relation==RightChild)
        {
            if(node->parent->parent->left!=NULL && node->parent->parent->left->color==RED)
            {
         
                node->parent->color=BLACK;
                node->parent->parent->left->color=BLACK;
                node->parent->parent->color=RED;
                restoreProperty(node->parent->parent);
            } 

            else if(node->parent->left!=NULL && node->parent->left->color==BLACK)
            {
                if(node->relation==LeftChild)
                {
                    leftRotate(node->parent->parent);
                }
                else if(node->relation==RightChild)
                {
                    rightRotate(node);
                    leftRotate(node->parent->parent);
                }
            } 
        }
    }
}

void RedBlack_Tree::insert(int value, Node *node)
{
    if(value>node->value)
    {
        if(node->right==NULL)
        {
            node->right=new Node;
            node->right->value=value;
            node->right->parent=node;
            node->right->left=NULL;
            node->right->right=NULL;
            node->right->relation=RightChild;
            node->right->color=RED;

            if(node->color!=BLACK)
            {

                restoreProperty(node->right);
            }
        }
        else
        {
            insert(value,node->right);
        }
        
    }
    else 
    {
        if(node->left==NULL)
        {
            node->left=new Node;
            node->left->value=value;
            node->left->parent=node;
            node->left->left=NULL;
            node->left->right=NULL;
            node->left->relation=LeftChild;
            node->left->color=RED;

            if(node->color!=BLACK)
            {
                
                restoreProperty(node->left);
            }
        }
        else
        {
            insert(value,node->left);
        }
        
    }
}

void RedBlack_Tree::insert(int value)
{
    if(root==NULL)
    {
        root=new Node;
        root->value=value;
        root->left=NULL;
        root->right=NULL;
        root->relation=Root;
        root->parent=NULL;
    }
    else
    {
        insert(value,root);
    } 
}

void RedBlack_Tree::printLevelOrder(Node *node, int level)
{

    if (level == 0)
    {
        if(node->color==RED)
        {
            cout << node->value << " " << "RED" << " ,";
        }
        else
        {
            cout << node->value << " " << "BLACK" << " ,";
        }     
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

void RedBlack_Tree::printLevelOrder()
{
    for (int i = 0; i <= 10; i++)
    {
        printLevelOrder(root, i);
        cout << endl;
    }
}

int main()
{
    RedBlack_Tree tree;

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(3);
    tree.insert(6);
    tree.insert(2);
    tree.insert(4);
    tree.insert(1);
  
    tree.printLevelOrder();
}
