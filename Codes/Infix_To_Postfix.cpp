// Write a program in cpp to convert an infix expression into a postfix expression by implementing stack.

#include <iostream>
#include <cctype>

class Stack {
private:
    int maxSize;
    int top;
    char* stackArray;

public:
    Stack(int size) : maxSize(size), top(-1) {
        stackArray = new char[maxSize];
    }

    ~Stack() {
        delete[] stackArray;
    }

    void push(char value) {
        if (top < maxSize - 1) {
            stackArray[++top] = value;
        } else {
            std::cerr << "Stack overflow\n";
        }
    }

    char pop() {
        if (top >= 0) {
            return stackArray[top--];
        } else {
            std::cerr << "Stack underflow\n";
            return '\0';
        }
    }

    char peek() const {
        if (top >= 0) {
            return stackArray[top];
        } else {
            std::cerr << "Stack is empty\n";
            return '\0';
        }
    }

    bool isEmpty() const {
        return top == -1;
    }
};

bool isOperator(char ch) {
    return (ch == '+' || ch == '-' || ch == '*' || ch == '/');
}

int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    else if (op == '*' || op == '/')
        return 2;
    return 0;
}

std::string infixToPostfix(const std::string& infix) {
    std::string postfix;
    Stack operatorStack(infix.size());

    for (char ch : infix) {
        if (std::isalnum(ch)) {
            postfix += ch;
        } else if (isOperator(ch)) {
            while (!operatorStack.isEmpty() && getPrecedence(operatorStack.peek()) >= getPrecedence(ch)) {
                postfix += operatorStack.pop();
            }
            operatorStack.push(ch);
        } else if (ch == '(') {
            operatorStack.push(ch);
        } else if (ch == ')') {
            while (!operatorStack.isEmpty() && operatorStack.peek() != '(') {
                postfix += operatorStack.pop();
            }
            operatorStack.pop(); // This is to Pop the opening parenthesis
        }
    }

    while (!operatorStack.isEmpty()) {
        postfix += operatorStack.pop();
    }

    return postfix;
}

int main() {
    std::string infixExpression;

    std::cout << "Enter infix expression: ";
    std::getline(std::cin, infixExpression);

    std::string postfixExpression = infixToPostfix(infixExpression);

    std::cout << "Postfix expression: " << postfixExpression << std::endl;

    return 0;
}
