#pragma once

#include <istream>
#include <cctype>
#include <sstream>
#include <cassert>

#include "expression.h"

enum class Associativity {
    LEFT,
    RIGHT
};

struct Operation {
    char symbol;
    char operation;
    unsigned short priority;
    Associativity associativity;

    static double calculate(char operation, double lhs, double rhs) {
        switch (operation) {
        case '+': return lhs + rhs;
        case '-': return lhs - rhs;
        case '*': return lhs * rhs;
        case '/': {
            if (rhs == 0.0) {
                throw incorrect_expression("Division by zero!");
            }
            return lhs / rhs;
        }
        default: throw incorrect_expression("Invalid operation!");
        }
    }
};

class OperationSet {
private:
    bool availableOperators[256]{};
    Operation operations[26];

public:
    OperationSet(std::istream& ops) {
        char buffer[1024];
        while (ops.getline(buffer, 1024)) {
            std::stringstream ss(buffer);
            char symbol = tolower(ss.get());
            char operation;
            ss >> operation;
            int num;
            ss >> num;
            char ch;
            ss >> ch;
            Associativity associativity = ch == 'R' ? Associativity::RIGHT : Associativity::LEFT;
            assert(symbol >= 'a');
            assert(symbol <= 'z');
            operations[symbol - 'a'] = Operation{ symbol, operation, static_cast<unsigned short>(num), associativity };
            availableOperators[symbol] = true;
        }
    }
    Operation get(char operation) {
        if (!availableOperators[operation]) {
            throw incorrect_expression("There is no such operator!");
        }
        char symbol = tolower(operation);
        assert(operation >= 'a');
        assert(operation <= 'z');
        return operations[symbol - 'a'];
    }
};
