#include <iostream>
#include <map>
#include <string>
#include <cctype>
#include <stdexcept>
using namespace std;

template <typename T>
class stackHCY {
    int mS;     // Maximum size of the stack
    int tI;     // Index of the top element
    T* stk;     // Array to store stack elements
public:
    stackHCY(int a = 0) {
        mS = a;
        tI = -1;
        stk = new T[mS];
    }
    ~stackHCY() { delete[] stk; }
    int size() { return tI + 1; }
    bool empty() { return tI < 0; }
    T& top() {
        if (empty()) throw runtime_error("Stack is empty"); 
        return stk[tI];
    }
    void push(const T& e) {
        if (tI >= mS - 1) throw runtime_error("Stack overflow");
        stk[++tI] = e;
    }
    void pop() {
        if (empty()) throw runtime_error("Stack underflow");
        tI--;
    }
};

template <typename T>
class calExp {
    map<char, int> op = {{'+', 1}, {'-', 1}, {'*', 2}, {'/', 2}};
    
    float tinhToan(float a, float b, char op) {
        switch (op) {
            case '+': return a + b;
            case '-': return a - b;
            case '*': return a * b;
            case '/': 
                if (b == 0) throw runtime_error("Division by zero");
                return a / b;
            default: throw runtime_error("Invalid operator");
        }
    }

public:
    string AlgBaLan(const string& str) {
        stackHCY<char> operators(100);
        string output;

        for (size_t i = 0; i < str.length(); ++i) {
            if (isdigit(str[i])) {
                // Append digit to the output
                output += str[i];
            } else if (str[i] == '(') {
                operators.push(str[i]);
            } else if (str[i] == ')') {
                // Pop operators until '(' is encountered
                while (!operators.empty() && operators.top() != '(') {
                    output += operators.top();
                    operators.pop();
                }
                if (!operators.empty() && operators.top() == '(') {
                    operators.pop();
                }
            } else if (op.find(str[i]) != op.end()) {
                // Handle operator precedence
                while (!operators.empty() && op[operators.top()] >= op[str[i]]) {
                    output += operators.top();
                    operators.pop();
                }
                operators.push(str[i]);
            }
        }

        // Append remaining operators
        while (!operators.empty()) {
            output += operators.top();
            operators.pop();
        }

        return output;
    }

    float calStackBaLan(const string& postfix) {
        stackHCY<float> evalStack(100);

        for (char token : postfix) {
            if (isdigit(token)) {
                evalStack.push(static_cast<float>(token - '0'));
            } else if (op.find(token) != op.end()) {
                if (evalStack.size() < 2) throw runtime_error("Invalid postfix expression");
                float b = evalStack.top(); evalStack.pop();
                float a = evalStack.top(); evalStack.pop();
                evalStack.push(tinhToan(a, b, token));
            }
        }

        if (evalStack.size() != 1) throw runtime_error("Invalid postfix evaluation");
        return evalStack.top();
    }
};

int main() {
    string input;
    getline(cin, input);

    calExp<char> calculator;
    string postfix = calculator.AlgBaLan(input);

    // Print postfix expression
    cout << "Postfix Expression: " << postfix << endl;

    // Calculate result of postfix expression
    float result = calculator.calStackBaLan(postfix);
    cout << "Result: " << result << endl;

    return 0;
}
