//header guard - prevents contents of header from being included more than once into given code file
#ifndef NODE_H
#define NODE_H

//include definition of Data class so it can be used in file
#include "Data.h"

//define node class that will be used in linked list
class Node 
{
private:
    //member variables:
    Data m_payload; //variable of type Data that stores data (operand or operator)
    Node* m_next;   //variable of type Node that point to next node in linked list

public:
    //default constructor (initializes node with no next node)
    //sets next node pointer to nullptr, indicates no subsequent node (last one in list or next node not yet defined)
    Node() : m_next{ nullptr } {}

    //overloaded constructor (initializes node with data and no next node)
    Node(const Data& data) : m_payload{ data }, m_next{ nullptr } {}

    //accessors for member variables:  
    //payload accessor - returns data stored in this node
    Data getPayload() const { return m_payload; }  

    //next node pointer accessor - returns pointer to next node in list (may be nullptr if last node)
    Node* getNext() const { return m_next; }        

    //mutators for member variables:
    //payload mutator - allows data stored in node to be modified after creation of node
    void setPayload(const Data& data) { m_payload = data; }

    //next node pointer mutator - sets next node in linked list (allows modifications like insertion/deletion)
    void setNext(Node* node) { m_next = node; }  
};
#endif //NODE_H

