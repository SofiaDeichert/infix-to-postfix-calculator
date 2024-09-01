#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath> 
#include <sstream>
#include <iomanip>
#include "Stack.h" //include definition of Stack class so it can be used in file

using namespace std;

//function returning precedence of operators
int precedence(char op)
{
    if (op == '^') //if character is exponent operator
    {
        return 3; //return 3 since it has highest precedence
    }

    else if (op == '*' || op == '/') //otherwise, if character is multiplication or division operator
    {
        return 2; //return 2 since these have next highest precedence
    }

    else if (op == '+' || op == '-') //otherwise, if character is addition or subtraction operator
    {
        return 1; //return 1 since they have lowest precedence
    }
    return 0; //return zero for any character that is not recognized operator
}

//function performing arithmetic operations based on operator
double applyOperation(double a, double b, char op) 
{
    switch (op) //switch statement based on operator
    {
    case '+': return a + b;     //if operator is '+', return sum
    case '-': return a - b;     //if operator is '-', return difference
    case '*': return a * b;     //if operator is '*', return product
    case '/': return a / b;     //if operator is '/', return quotient
    case '^': return pow(a, b); //if operator is '^', return power
    }
    return 0; //return value if no valid operator
}

//function to convert infix expression to postfix
string infixToPostfix(const string& infix) 
{
    Stack operationStack; //create stack variable to hold operators
    string postfixExpression = ""; //initialize resulting postfix expression as empty string


    for (size_t i = 0; i < infix.length(); i++) //iterate through each character in infix expression
    {
        if (isdigit(infix[i]) || infix[i] == '.') //if character is digit or decimal point
        {
            postfixExpression += infix[i]; //add numeric character to postfix expression

            if ((i == infix.length() - 1) || (!isdigit(infix[i + 1]) && infix[i + 1] != '.')) 
            {
                postfixExpression += " "; //add space after numbers to separate them in postfix string
            }
        }
        else if (infix[i] == '(') //if character is open parenthesis
        {
            operationStack << new Node(Data(infix[i])); //push '(' onto stack
        }
        else if (infix[i] == ')') //if character is close parenthesis
        {        
            Node* topNode; //declare pointer to hold node popped from stack
            operationStack >> topNode; //pop top node from stack into topNode

            //loop until opening parenthesis '(' encountered in stack
            while (topNode->getPayload().getOperator() != '(') 
            {
                postfixExpression += topNode->getPayload().getOperator(); //append operator from node to postfix expression
                postfixExpression += " "; //append space to separate elements in postfix expression
                delete topNode; //delete node to free memory
                operationStack >> topNode; //pop next node from stack into topNode
            }
            delete topNode; //delete node containing '(' to free memory
        }
        else //otherwise, if character is an operator
        {
            //process all operators in stack that have greater or equal precedence than current operator
            while (operationStack.getHead() != nullptr && precedence(infix[i]) <= precedence(operationStack.getHead()->getPayload().getOperator())) 
            {
                Node* top; //declare pointer to hold node popped from stack
                operationStack >> top; //pop top node from stack
                postfixExpression += top->getPayload().getOperator(); //append operator from node to postfix expression
                postfixExpression += " "; //append space to separate elements in postfix expression
                delete top; //delete node to free memory
            }
            operationStack << new Node(Data(infix[i])); //push current operator onto stack wrapped in Node
        }
    }

    //after processing all characters, empty stack of any remaining operators
    while (operationStack.getHead() != nullptr)
    {
        Node* topNode; //declare pointer to hold node popped from stack
        operationStack >> topNode; //pop top node from stack
        postfixExpression += topNode->getPayload().getOperator(); //append operator from node to postfix expression
        postfixExpression += " "; //append space to separate elements in postfix expression
        delete topNode;  //delete node to free memory
    }

    return postfixExpression; //return constructed postfix expression
}

//function to calculate result of postfix expression
double calculatePostfix(const string& postfix) 
{
    Stack valueStack; //Stack variable to store operands as nodes
    stringstream postfixStream(postfix); //create stream to read elements of postfix expression
    string element;  //create variable to store each element read from stream

    while (getline(postfixStream, element, ' '))  //read each element from postfix expression separated by spaces
    {
        if (!element.empty())  //if element is not empty
        {
            //if element is numeric (operand) - if first character of 'element' is digit/'element' contains decimal point
            if (isdigit(element[0]) || element.find('.') != string::npos)  
{ 
                //convert string element to double and push it as data in new node onto stack
                valueStack << new Node(Data(stod(element), '\0')); 
            }
            else  //otherwise, if element is an operator
            {
                Node* secondOperand; //create pointer to store second operand
                Node* firstOperand; //create pointer to store first operand
                valueStack >> secondOperand; //pop top node (second operand) from stack
                valueStack >> firstOperand;  //pop next node (first operand) from stack

                //call applyOperation function to calculate result of operation using two operands and operator
                double result = applyOperation(firstOperand->getPayload().getOperand(), secondOperand->getPayload().getOperand(), element[0]);

                valueStack << new Node(Data(result, '\0')); //push result back onto stack as new node
                delete firstOperand; //free memory of first operand node
                delete secondOperand; //free memory of second operand node
            }
        }
    }
     
    Node* resultNode;  //create pointer to store final result node
    valueStack >> resultNode;  //pop result node from stack
    double result = resultNode->getPayload().getOperand();  //retrieve result from node
    delete resultNode;  //free memory of result node
    return result;  //return calculated result
}

int main() 
{
    string inputFilename;  //create string variable to store name of file to be read
    cout << "Enter the name of the file to be read from: "; //prompt user to enter name of file
    cin >> inputFilename; //read filename input from user and store in inputFilename

    ifstream file(inputFilename); //create input filestream object for file provided by user

    //check if file can be opened; if it cannot, print an error to console and exit
    if (!file)
    {
        cerr << "File could not be opened for reading.\n";
        return 1;
    }

    string line; //create string variable to store each line read from file

    //while there are still lines to process, store each file line in our 'line' string object
    while (getline(file, line)) 
    {
        string postfix = infixToPostfix(line);  //call function to convert infix expression read from line to postfix notation
        double result = calculatePostfix(postfix); //call function to calculate result of evaluated postfix expression

        //output postfix expression and its result, formatted to three decimal places
        cout << postfix << '\t' << fixed << setprecision(3) << result << '\n';
    }

    file.close(); //close file after all lines have been processed

    return 0; //return 0 to indicate successful execution of program
}
