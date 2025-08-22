#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class ExpressionConverter {
private:
    string operatorStack;
    string outputStack;

    int priority(char element) {
        switch(element) {
            case '^': return 3;
            case '*':
            case '/': return 2;
            case '+':
            case '-': return 1;
        }
        return -1;
    }

public:
    void pushOperator(char element) {
        operatorStack.push_back(element);
    }

    char popOperator() {
        char ch = operatorStack.back();
        operatorStack.pop_back();
        return ch;
    }

    char peekOperator() {
        return operatorStack.back();
    }

    void pushOutput(char element) {
        outputStack.push_back(element);
    }

    void displayStacks() {
        cout << "\nOperator stack\t= ";
        for (char c : operatorStack) cout << "| " << c << " ";
        cout << "\nOutput stack\t= ";
        for (char c : outputStack) cout << "| " << c << " ";
        cout << "\n";
    }

    string convertToPostfix(const string& infix) {
        outputStack.clear();
        operatorStack.clear();

        for (char element : infix) {
            if (element == '(') {
                pushOperator(element);
            } else if (element == ')') {
                while (peekOperator() != '(') {
                    pushOutput(popOperator());
                }
                popOperator();
            } else if (element == '*' || element == '/' || element == '+' || element == '-' || element == '^') {
                while (!operatorStack.empty() && priority(peekOperator()) >= priority(element)) {
                    pushOutput(popOperator());
                }
                pushOperator(element);
            } else {
                pushOutput(element);
            }
            displayStacks();
        }

        while (!operatorStack.empty()) {
            pushOutput(popOperator());
        }

        return outputStack;
    }

    string convertToPrefix(const string& infix) {
        string reversedInfix = infix;
        reverse(reversedInfix.begin(), reversedInfix.end());
        for (char &c : reversedInfix) {
            if (c == '(') c = ')';
            else if (c == ')') c = '(';
        }

        outputStack.clear();
        operatorStack.clear();

        for (char element : reversedInfix) {
            if (element == '(') {
                pushOperator(element);
            } else if (element == ')') {
                while (peekOperator() != '(') {
                    pushOutput(popOperator());
                }
                popOperator();
            } else if (element == '*' || element == '/' || element == '+' || element == '-' || element == '^') {
                while (!operatorStack.empty() && priority(peekOperator()) > priority(element)) {
                    pushOutput(popOperator());
                }
                pushOperator(element);
            } else {
                pushOutput(element);
            }
        }

        while (!operatorStack.empty()) {
            pushOutput(popOperator());
        }

        reverse(outputStack.begin(), outputStack.end());
        return outputStack;
    }
};

int main() {
    ExpressionConverter converter;
    string infix;

    cout << "Enter infix expression: ";
    cin >> infix;

    cout << "\nInfix Expression = " << infix << "\n";

    string postfix = converter.convertToPostfix(infix);
    cout << "\nPostfix Expression = " << postfix << "\n";

    string prefix = converter.convertToPrefix(infix);
    cout << "\nPrefix Expression = " << prefix << "\n";

    return 0;
}
