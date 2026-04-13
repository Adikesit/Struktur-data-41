#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int precedence(char c){
    if(c=='^'){
        return 3;
    }else if(c=='*' || c=='/'){
        return 2;
    }else if(c=='+' || c=='-'){
        return 1;
    }else {
        return 0;
    }
}

bool isOperator(char c){
    return(c=='*'||c=='/'||c=='+'||c=='-'||c=='^');
}

string inf_to_postf(string inf) {
    stack<char> st;
    string posf = "";

    for(int i = 0; i < inf.length(); i++) {
        char c = inf[i];

        if(isalnum(c)) posf += c;
        else if(c == '(') st.push(c);
        else if(c == ')') {
            while(!st.empty() && st.top() != '(') {
                posf += st.top();
                st.pop();
            }
            if(!st.empty()) st.pop();
        }
        else if(isOperator(c)) {
            while(!st.empty() && precedence(st.top()) >= precedence(c)) {
                posf += st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while(!st.empty()) {
        posf += st.top();
        st.pop();
    }

    return posf;
}

int main() {
    string infix;

    cout << "Masukkan string infix: ";
    cin >> infix;

    string postfix = inf_to_postf(infix);

    cout << "String postfix: " << postfix << endl;

    return 0;
}