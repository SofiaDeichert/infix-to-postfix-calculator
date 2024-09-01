# Infix to Postfix Calculator

This project implements a calculator that converts infix expressions to postfix notation and evaluates them. It's written in C++ and demonstrates the use of custom data structures like stacks and linked lists.

## Features

- Converts infix expressions to postfix notation
- Evaluates postfix expressions
- Supports basic arithmetic operations (+, -, *, /, ^)
- Handles parentheses in expressions
- Reads expressions from a file and outputs results

## Project Structure

The project consists of the following files:

- `main.cpp`: Contains the main program logic
- `Stack.h` and `Stack.cpp`: Implement the Stack data structure
- `Node.h`: Defines the Node class for the linked list
- `Data.h`: Defines the Data class to store operands and operators
- `a.txt`: Input file containing infix expressions to be evaluated

## Example

Input file (`a.txt`):
```
3+4*5/6
(300+23)*(43-21)/(84+7)
(4.5+8.2)*(6-5)/((3.25-2.61)*(2+2^2))
```

Output:
```
3 4 5 * 6 / +    6.333
300 23 + 43 21 - * 84 7 + /    70.637
4.5 8.2 + 6 5 - * 3.25 2.61 - 2 2 2 ^ + * /    2.746
```

## Implementation Details

1. **Stack Implementation**: 
   - The Stack class is implemented as a singly linked list.
   - Each node in the list contains a Data object and a pointer to the next node.
   - The Stack class provides operations like push (using `operator<<`) and pop (using `operator>>`).
   - A copy constructor is implemented for deep copying of stacks.
   - The destructor ensures proper memory deallocation using a recursive `deleteNodes` function.

2. **Data Class**:
   - The Data class is designed to store either an operand (as a double) or an operator (as a char).
   - This dual-purpose design allows the same stack to be used for both operands and operators during conversion and evaluation.

3. **Infix to Postfix Conversion**:
   - The `infixToPostfix` function implements the Shunting Yard algorithm.
   - It uses a stack to keep track of operators and parentheses.
   - The function handles operator precedence, ensuring correct order of operations.
   - Operands are immediately added to the output, while operators are pushed and popped from the stack based on their precedence.

4. **Postfix Evaluation**:
   - The `calculatePostfix` function evaluates the postfix expression.
   - It uses a stack to store operands.
   - When an operator is encountered, it pops the required number of operands, performs the operation, and pushes the result back onto the stack.
   - The final result is the only value left on the stack after processing all tokens.

5. **Operator Precedence**:
   - The `precedence` function defines the precedence of operators:
     - Exponentiation (^) has the highest precedence (3)
     - Multiplication and division (* and /) have the next highest precedence (2)
     - Addition and subtraction (+ and -) have the lowest precedence (1)

6. **File Input/Output**:
   - The program reads infix expressions from a file specified by the user.
   - Each line of the input file is treated as a separate expression.
   - The program outputs both the postfix form of each expression and its evaluated result.

7. **Error Handling**:
   - Basic error handling is implemented for file opening operations.
   - The program checks for invalid file names and provides appropriate error messages.

This implementation showcases the use of custom data structures, operator overloading, and algorithm implementation in C++. It provides a practical example of how stacks can be used to solve mathematical expression parsing and evaluation problems.
