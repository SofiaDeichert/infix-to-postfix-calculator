#include "Stack.h" //include definition of Stack class so it can be used in file

//full definition of copy constructor - initializes new stack as deep copy of existing stack
//iteratively copies each node from source stack to new stack
Stack::Stack(const Stack& other) : m_head{ nullptr } 
{
    if (other.m_head) //if source stack (other) is not empty
    {
        //create new node copying payload of head node of source stack
        m_head = new Node(other.m_head->getPayload());

        //set 'current' to point to new head node of newly created stack
        Node* current = m_head;

        //set 'otherCurrent' to point to second node of source stack (or nullptr if only one node exists)
        Node* otherCurrent = other.m_head->getNext();

        //iterate through rest of nodes in source stack:
        while (otherCurrent) //while 'otherCurrent' is not nullptr (points to valid node)
        {
            //create new node copying payload of current node pointed by 'otherCurrent'
            Node* newNode = new Node(otherCurrent->getPayload());

            //link new node to 'next' of current node of new stack
            current->setNext(newNode);

            //move 'current' forward to new node, making it last node in new stack
            current = newNode;

            //move 'otherCurrent' forward to next node in source stack
            otherCurrent = otherCurrent->getNext();
        }
    }
}

//recursive destructor - deletes all nodes in stack to free memory
Stack::~Stack() 
{
    //calls private helper function to delete nodes starting from head
    deleteNodes(m_head);
}

//overloaded operator << for pushing node onto stack (full definition)
Stack& Stack::operator<<(Node* node) 
{
    node->setNext(m_head);  //set new node's next pointer to current head of stack
    m_head = node;          //update head of stack to new node, pushing it onto stack
    return *this;           //return current implicit stack object (reference to stack) so multiple operations can be chained together
}

//overloaded operator >> for popping node from stack (full definition)
Stack& Stack::operator>>(Node*& node) 
{
    if (m_head == nullptr)  //if stack if empty
    {
        node = nullptr; //set node pointer to nullptr to indicate no nodes available to pop
    }
    else 
    {
        node = m_head; //retrieve top node from stack by assigning it to node parameter
        m_head = m_head->getNext(); //move head pointer to next node, removing top node from stack
        node->setNext(nullptr); //detach popped node from stack by setting its next pointer to nullptr
    }
    return *this;  //return current implicit stack object so multiple operations can be chained together
}

//overloaded operator << for outputting contents of stack to output stream (full definition)
std::ostream& operator<<(std::ostream& out, const Stack& stack) 
{
    Node* current = stack.m_head; //start at head of stack
    if (current == nullptr) //if stack is empty
    {
        return out; //return output stream directly
    }

    //create flag to determine whether stack contains operands or operators based on type of payload in first node
    //flag is set to true if operator character in payload of current (first) node is null character ('\0')
    bool isOperandStack = current->getPayload().getOperator() == '\0';

    //loop through each node in stack
    while (current != nullptr) 
    {
        if (isOperandStack) //if stack contains operands
        {
            out << current->getPayload().getOperand(); //output operand value
        }
        else  //otherwise, if stack contains operators
        {
            out << current->getPayload().getOperator(); //output operator character
        }
        if (current->getNext() != nullptr) //if there is another node to output after this one
        {
            out << ", "; //add comma and space to separate stack elements
        }
        current = current->getNext(); //move to next node in stack
    }
    return out;  //return output stream after all nodes have been processed
}

//function to clear all nodes in stack
void Stack::clear() 
{
    deleteNodes(m_head); //delete all nodes
    m_head = nullptr;    //set head pointer to nullptr to indicate stack is empty
}   

