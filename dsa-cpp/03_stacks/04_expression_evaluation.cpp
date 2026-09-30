// Infix -> postfix (shunting-yard) and postfix evaluation.
// Simplified: operands are single digits, operators are + - * / and parentheses.
#include <iostream>
#include <stack>
#include <string>
using namespace std;

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

string infixToPostfix(const string& infix) {
    string postfix;
    stack<char> operators;
    for (char ch : infix) {
        if (ch >= '0' && ch <= '9') {
            postfix += ch;                                   // operands go straight out
        } else if (ch == '(') {
            operators.push(ch);
        } else if (ch == ')') {
            while (!operators.empty() && operators.top() != '(') {
                postfix += operators.top();
                operators.pop();
            }
            if (!operators.empty()) operators.pop();         // discard '('
        } else {                                             // + - * /
            // pop operators that bind at least as tight (left-associative)
            while (!operators.empty() && precedence(operators.top()) >= precedence(ch)) {
                postfix += operators.top();
                operators.pop();
            }
            operators.push(ch);
        }
    }
    while (!operators.empty()) {
        postfix += operators.top();
        operators.pop();
    }
    return postfix;
}

int evaluatePostfix(const string& postfix) {
    stack<int> values;
    for (char ch : postfix) {
        if (ch >= '0' && ch <= '9') {
            values.push(ch - '0');
        } else {
            int right = values.top(); values.pop();          // right operand is popped first
            int left = values.top(); values.pop();
            if (ch == '+') values.push(left + right);
            else if (ch == '-') values.push(left - right);
            else if (ch == '*') values.push(left * right);
            else if (ch == '/') values.push(left / right);
        }
    }
    return values.top();
}

int main() {
    string infix = "2+3*(4-1)";
    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;                       // 2341-*+
    cout << "Result: " << evaluatePostfix(postfix) << endl;       // 11
    return 0;
}
