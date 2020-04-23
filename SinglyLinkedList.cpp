#include <stddef.h>
#include <iostream>
using namespace std;

struct Node
{
    int index;
    int value;
    Node *pointer;
};

struct Dummy
{
    Node *pointer;
};

class LinkedList
{
    public:
        LinkedList();
        void insert(int value);
        void insert(int value, int index);
        void printList();
        void get(int index);

    private:
        void insert(int value, Node *node);
        void insert(int value,int index, Node *node);
        void printNode(Node *node);
        void incrementIndex(Node *node);
        void get(int index, Node *node);
        Dummy *head;
        
};

LinkedList::LinkedList()
{
    head=NULL;
}

void LinkedList::insert(int value, Node *node)
{
    if (node->pointer==NULL)
    {
        node->pointer=new Node;
        node->pointer->value=value;
        node->pointer->index=(node->index)+1;
        node->pointer->pointer=NULL;
    }
    else
    {
        insert(value,node->pointer);
    }
    
}

void LinkedList::insert(int value)
{
    if (head==NULL)
    {
        head=new Dummy;
        head->pointer=new Node;
        head->pointer->index=0;
        head->pointer->value=value;
        head->pointer->pointer=NULL;
        
    }
    else
    {
        insert(value,head->pointer);
    }
    
}

void LinkedList::printList()
{
    if(head!=NULL)
    {
        printNode(head->pointer);
    }
}

void LinkedList::printNode(Node *node)
{
    if (node!=NULL)
    {   
        cout<<node->index;
        cout<<" ";
        cout<< node->value<<endl;
        
        printNode(node->pointer);
    }
    
}

void LinkedList::incrementIndex(Node *node)
{
    if (node!=NULL)
    {
        node->index=node->index+1;
        incrementIndex(node->pointer);
    }
}
void LinkedList::insert(int value,int index, Node *node)
{
    if (node->index==index-1)
    {
        Node *newNode;
        newNode= new Node;
        newNode->value=value;
        newNode->pointer=node->pointer;
        newNode->index=node->pointer->index;
        node->pointer=newNode;
        incrementIndex(newNode->pointer);

    }
    else
    {
        insert(value,index,node->pointer);
    }
    
}


void LinkedList::insert(int value,int index)
{
    if (head!=NULL)
    {
        insert(value,index,head->pointer);
    }
}

void LinkedList::get(int index)
{
    if (head!=NULL)
    {
        get(index,head->pointer);
    }
}

void LinkedList::get(int index, Node *node)
{
    if(node->index==index)
    {
        cout<< node->value<<endl;
    }
    else
    {
        get(index,node->pointer);
    }
    
}


int main()
{
    LinkedList list;
    list.insert(5);
    list.insert(4);
    list.insert(3);
    list.insert(2);
    list.insert(1);
    list.insert(7,2);
    list.printList();
    list.get(4);

}