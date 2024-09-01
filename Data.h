//header guard - prevents contents of header from being included more than once into given code file
#ifndef DATA_H
#define DATA_H

//define data class, which represents either operand or operator in expression
class Data 
{
private:
    //member variables:
    double m_operand;    //variable to hold numeric operand value
    char m_charOperator; //variable to hold character representing operator ('+', '-', '*', '/', '^')

public:
    //default constructor - initializes operand or operator with default values
    //optionally initializes with provided operand and operator character
    Data(double op = 0.0, char opChar = '\0') : m_operand(op), m_charOperator(opChar) {}

    //overloaded constructors:
    //overloaded constructor to initialize Data object with specific operand and default operator
    Data(double operand) : m_operand{ operand }, m_charOperator{ '\0' } {}

    //overloaded constructor to initialize Data object with specific operator and default operand
    Data(char charOperator) : m_operand{ 0 }, m_charOperator{ charOperator } {}

    //accessors for member variables:
    //accessor for operand value - returns double value of operand
    double getOperand() const { return m_operand; }

    //accessor for operator - returns character representing operator
    char getOperator() const { return m_charOperator; }

    //mutators for member variables:
    //mutator for operand - sets operand value to specified double
    void setOperand(double operand) { m_operand = operand; }

    //mutator for operator - setse operator character to specified char
    void setOperator(char charOperator) { m_charOperator = charOperator; }
};
#endif //DATA_H

