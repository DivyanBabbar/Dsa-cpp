// Classic stack problem: are (), {}, [] balanced and properly nested?
// Rule: push every opener. On a closer, the top must be its matching opener.
#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool isBalanced(const string& text) {
    stack<char> openers;
    for (char ch : text) {
        if (ch == '(' || ch == '{' || ch == '[') {
            openers.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']') {
            if (openers.empty()) return false;       // closer with nothing to match
            char top = openers.top();
            openers.pop();
            bool matches = (ch == ')' && top == '(') ||
                           (ch == '}' && top == '{') ||
                           (ch == ']' && top == '[');
            if (!matches) return false;
        }
    }
    return openers.empty();                          // leftover openers = unbalanced
}

int main() {
    cout << isBalanced("{[()]}") << endl;    // 1
    cout << isBalanced("{[(])}") << endl;    // 0 (wrong nesting)
    cout << isBalanced("((") << endl;        // 0 (unclosed)
    cout << isBalanced("())") << endl;       // 0 (extra closer)
    return 0;
}
