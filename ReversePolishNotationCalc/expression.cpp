#include "expression.h"

#include <sstream>
#include <cctype>
#include <stack>
#include <vector>
#include <string>

#include "OperationSet.h"

///
/// @brief Evaluates an expression.
///
/// @param expression
///   A null-terminated string that contains the expression.
/// @param ops
///   An input stream which contains the descriptions of all operations used in the expression.
///
/// @return The calculated value of the expression
///
double evaluate(const char* expression, std::istream& ops) {
    if (!expression) {
        throw incorrect_expression("Expression is nullptr!");
    }

    const char* str = expression;
    bool isEmpty = true;
    while (*str != '\0') {
        if (!std::isspace(static_cast<unsigned char>(*str))) {
            isEmpty = false;
            break;
        }
        ++str;
    }
    if (isEmpty) {
        return 0;
    }

    enum class Inputs {
        EMPTY,
        NUMBER,
        OPERATOR,
        OPENING_BRACKET,
        CLOSING_BRACKET
    };
    Inputs lastInput = Inputs::EMPTY; //keep track of what the last input from the expression is

    OperationSet allowedOperations(ops);
    std::stack<double> numbers;
    std::stack<char> operations;

    std::stringstream ss(expression);
    char ch;
    while (ss >> ch) {
        // validate there are empty spaces between brackets and operations
        if (ch != '-' && !isdigit(ch) && ss.peek() != EOF && ss.peek() != ' ') {
            throw incorrect_expression("There is no empty space between brackets!");
        }

        if (ch == '(') {
            if (lastInput == Inputs::NUMBER || lastInput == Inputs::CLOSING_BRACKET) {
                throw incorrect_expression("There is a number or a closing bracket before an opening bracket!");
            }
            lastInput = Inputs::OPENING_BRACKET;

            operations.push(ch);
        }
        else if (ch == ')') {
            if (lastInput == Inputs::OPERATOR || lastInput == Inputs::OPENING_BRACKET || lastInput == Inputs::EMPTY) {
                throw incorrect_expression("There is an operator or an opening bracket before a closing bracket or it's the beggining of the expression!");
            }
            lastInput = Inputs::CLOSING_BRACKET;

            if (operations.empty()) {
                throw incorrect_expression("There are more opening brackets than closing brackets!");
            }

            while (operations.top() != '(') {
                calculate(numbers, allowedOperations.get(operations.top()).operation);
                operations.pop();

                if (operations.empty()) {
                    throw incorrect_expression("There are more closing brackets than opening brackets!");
                }
            }

            operations.pop(); //remove '('
        }
        else if (isalpha(ch)) {
            if (lastInput == Inputs::OPERATOR || lastInput == Inputs::OPENING_BRACKET || lastInput == Inputs::EMPTY) {
                throw incorrect_expression("There is an operator or an opening bracket before a closing bracket or it's the beggining of the expression!");
            }
            lastInput = Inputs::OPERATOR;

            //if stack is empty there is nothing to check
            if (operations.empty() || operations.top() == '(') {
                operations.push(ch);
                continue;
            }

            Operation lastOp = allowedOperations.get(operations.top()); // last in stack
            Operation currentOp = allowedOperations.get(ch); // current in loop

            //if last operation in stack has lower priority, just add the new one
            if (lastOp.priority < currentOp.priority) {
                operations.push(ch);
                continue;
            }

            //if last operation in stack has higher priority, calculate all operations with higher priority
            while (lastOp.priority > currentOp.priority || (lastOp.priority == currentOp.priority
                && lastOp.associativity == currentOp.associativity && lastOp.associativity == Associativity::LEFT)) {
                calculate(numbers, allowedOperations.get(operations.top()).operation);
                operations.pop();

                if (operations.empty() || operations.top() == '(') {
                    break;
                }

                lastOp = allowedOperations.get(operations.top());
            }

            if (operations.empty() || operations.top() == '(') {
                operations.push(ch);
                continue;
            }

            if (lastOp.priority == currentOp.priority && lastOp.associativity != currentOp.associativity) {
                throw incorrect_expression("Operations with same priority but different association!");
            }

            operations.push(ch);
        }
        else {
            if (lastInput == Inputs::NUMBER || lastInput == Inputs::CLOSING_BRACKET) {
                throw incorrect_expression("There is a number or a closing bracket before a number!");
            }
            lastInput = Inputs::NUMBER;

            bool negative = false;
            if (ch == '-') {
                ss.get(ch);
                if (ch == ' ') {
                    throw incorrect_expression("There can not be space between '-' and the number!");
                }
                negative = true;
            }

            int num = ch - '0';
            while (ss.get(ch) && ch != ' ') {
                num *= 10;
                num += ch - '0';
            }

            if (negative) {
                num = -num;
            }

            numbers.push(num);
        }
    }

    if (lastInput == Inputs::OPENING_BRACKET || lastInput == Inputs::OPERATOR) {
        throw incorrect_expression("Expression can not end with an opening bracket or an operator!");
    }

    while (!operations.empty() && operations.top() != '(') {
        calculate(numbers, allowedOperations.get(operations.top()).operation);
        operations.pop();
    }

    if (!operations.empty()) {
        throw incorrect_expression("There are more opening brackets than closing brackets!");
    }

    return numbers.top();
}

void calculate(std::stack<double>& nums, char operation) {
    double rhs = nums.top();
    nums.pop();
    double lhs = nums.top();
    nums.pop();
    double res = Operation::calculate(operation, lhs, rhs);
    nums.push(res);
}
