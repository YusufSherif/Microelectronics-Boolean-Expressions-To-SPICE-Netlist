#include <iostream>
#include <string>
#include <stack>
#include <map>
#include "Node.h"

using namespace std;


Node ands_1(string s);

Node mother_function(string s);

Node nots(string s);

Node bracket_eval(string s);

int main() {
    string input;
    string expression = "";
    string gen_out;
    cout << "Please enter your expression." << endl <<
         "Please note that the negation of x is denoted by !x instead of x'." << endl << endl;
    cin >> input;
    Node out;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '=') {
            expression = "";

            while (input[i] != ';' && i < input.length()) {
                if (input[i] != '=')
                    expression += input[i];
                i++;
            }
            out = mother_function(expression);
            gen_out = out.get_circuit_string();
            cout << gen_out << endl;
        } else if (isalpha(input[i])) {
            Node tmp(input[i]);
            out = tmp; //set name of output node.
        }
    }
    //mother_function(input);
    //string gen_out = Node::get_circuit_string();
    //cout << gen_out;
    return 0;
}

Node mother_function(string s) {
    string right = "", left = "";
    int k;
    bool flag = false;

    std::stack<char> stk;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(')
            stk.push('(');
        else if (s[i] == ')')
            stk.pop();
        if(stk.empty())
            if (s[i] == '|') {
                k = i;
                flag = true;
                break;
            }
    }
    if (flag) {
        for (int t = 0; t < k; t++) {
            right = right + s[t];
        }
        for (int l = k + 1; l < s.size(); l++) {
            left = left + s[l];
        }
        Node *l_p, *r_p;
        if (left.size() == 1) {
            l_p = new Node(left);
            *l_p = mother_function(left);
        } else
            l_p = new Node(mother_function(left));
        if (right.size() == 1) {
            r_p = new Node(right);
            *r_p = mother_function(right);
        } else
            r_p = new Node(mother_function(right));
        Node res;
        res = *l_p | *r_p;
        delete (l_p);
        delete (r_p);
        return res;
    } else {
        return ands_1(s);
    }
}

Node ands_1(string s) {
    string right = "", left = "";
    int k;
    bool flag = false;

    std::stack<char> stk;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(')
            stk.push('(');
        else if (s[i] == ')')
            stk.pop();
        if(stk.empty())
            if (s[i] == '&') {
            k = i;
            flag = true;
            break;
        }
    }
    if (flag) {
        for (int t = 0; t < k; t++) {
            right = right + s[t];
        }
        for (int l = k + 1; l < s.size(); l++) {
            left = left + s[l];
        }

        Node *l_p, *r_p;
        if (left.size() == 1) {
            l_p = new Node(left);
            *l_p = mother_function(left);
        } else
            l_p = new Node(mother_function(left));
        if (right.size() == 1) {
            r_p = new Node(right);
            *r_p = mother_function(right);
        } else
            r_p = new Node(mother_function(right));
        Node res;
        res = *l_p & *r_p;
        delete (l_p);
        delete (r_p);
        return res;
    } else {
        return nots(s);
    }
}

Node bracket_eval(string s){
    stack<char> stk;
    int start=0, end=0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(') {
            if(stk.empty()) start = i;
            stk.push('(');
        }
        else if (s[i] == ')') {
            stk.pop();
            if(stk.empty()) end = i;
        }
    }
    string bracket = start==end? "" : s.substr(start+1,end-(start+1));
    return start==end? Node(s):mother_function(bracket);

}

Node nots(string s) {
    stack<char> stk;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(')
            stk.push('(');
        else if (s[i] == ')')
            stk.pop();
        if(stk.empty())
            if (s[i] == '!') {
                return !bracket_eval(s);
            } else {
                return bracket_eval(s);
            }
    }
    return bracket_eval(s);
}
