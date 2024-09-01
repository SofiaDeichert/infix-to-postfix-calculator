//header guard - prevents contents of header from being included more than once into given code file
#ifndef STACK_H
#define STACK_H

#include "Node.h"   //include node class for use in defining stack
#include <iostream> 

//define stack class, which implements linked list to manage stack of nodes
class Stack 
{
private:
    //member variables:
    Node* m_head; //pointer variable to top (head) of stack

    //private member function to recursively delete all nodes in stack
    //called by destructor to ensure all memory is properly freed
    void deleteNodes(Node* node) 
    {
        if (node) //check if node exists (if node is not null, continue recursion)
        {
            deleteNodes(node->getNext());   //recursive function call to delete next node
            delete node;                    //delete current node after its next nodes are deleted
        }
    }

public:
    //default constructor - head pointer set to nullptr indicating stack is initially empty
    Stack() : m_head{ nullptr } {}     

    //overloaded constructor - starts stack with single node
    //sets head of stack to provided node
    Stack(Node* node) : m_head(node) {}      

    //copy constructor - creates new stack as deep copy of another stack
    //copies all nodes from other stack to this one, keeping it in order
    Stack(const Stack& other);            

    //destructor - cleans up all nodes in stack 
    //calls deleteNodes to recursively delete all linked list nodes starting from head
    ~Stack();                                      

    //accessors for member variables:
    //accessor for head node - returns pointer to head node, which is top of stack
    Node* getHead() const { return m_head; }

    //mutator for member variables:
    //mutator for head node - allows head of stack to be set to new node, modifying top of stack
    void setHead(Node* node) { m_head = node; }

    //overloaded operators:
    //overloaded operator << to push node onto stack
    //adds node to top of stack, making it new head
    Stack& operator<<(Node* node); 

    //overloaded operator >> to pop node from stack
    //removes top node from stack 
    Stack& operator>>(Node*& node); 

    //overloaded operator << for outputting contents of stack to output stream
    //allows stack to be printed 
    friend std::ostream& operator<<(std::ostream& os, const Stack& stack); 

    //function to clear all elements from stack
    //resets stack to be empty without leaking memeory
    void clear();
};
#endif //STACK_H
