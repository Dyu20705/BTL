#include <bits/stdc++.h>
using namespace std;
template <typename T>
class stackHCY {
    int mS;     
    int tI;    
    T* stk;     
public:
    stackHCY(int a=0) {
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
        if (tI >= mS - 1) {
            throw runtime_error("Stack overflow"); 
        }
        tI++;
        stk[tI] = e;
    }
    void pop() {
        if (empty()) {
            throw runtime_error("Stack underflow"); 
        }
        tI--;
    }
    void chuyenPhanTu(stackHCY<T>& b) {
        while (!this->empty()) {
            b.push(this->top());
            this->pop();
        }
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
            case '/': return a / b;
            default: throw runtime_error("Invalid operator"); 
        }
    }
public:
    stackHCY<T> AlgBaLan(string str) {
        stackHCY<T> a(100), b(100);
        for (int i = 0; i < str.length(); i++) {
            if (isdigit(str[i])) {
                b.push(str[i]);
            }
            else if (str[i] == '(') {
                a.push(str[i]);
            }
            else if (str[i] == ')') {
                while (!a.empty() && a.top() != '(') {
                    b.push(a.top());
                    a.pop();
                }
                if (!a.empty()) a.pop(); 
            }
            else if (op.find(str[i]) != op.end()) { 
                while (!a.empty() && op[a.top()] >= op[str[i]]) {
                    b.push(a.top());
                    a.pop();
                }
                a.push(str[i]); 
            }
        }
        a.chuyenPhanTu(b); 
        return b;
    }
    float calStackBaLan(stackHCY<T>& a) {
    	stackHCY<float> b(100);
    	stackHCY<char> c(100);
    	a.chuyenPhanTu(c);
    	while (!c.empty()) {
        	char d = c.top(); 
        	if (isdigit(d)) {
            b.push(static_cast<float>(d - '0')); 
        	} 
        	else if (op.find(d) != op.end()) {
            	float y = b.top(); b.pop();
            	float x = b.top(); b.pop();
            	b.push(tinhToan(y, x, d)); 
    		}
        	c.pop();
    	}
    	return b.top();
	}
};
main() {
    string a;
    getline(cin, a); 
    calExp<char> b;
    stackHCY<char> c = b.AlgBaLan(a);
    stackHCY<char>d(100);
    c.chuyenPhanTu(d); 
    while (!d.empty()) {
        cout << d.top() ;
        d.pop();
    }
    cout << endl;
    float res = b.calStackBaLan(c);
    cout <<  res << endl;
    return 0;
}

