#include <iostream>
#include <vector>
#include <string>
#include <stack>

using namespace std;

string input;
vector<string> vec;
vector<string> res;
bool wrong = false;
int answer;

int priority(char c){
    if(c >= 48 && c <= 57) return 0;
    if(c == '(' || c == ')') return 1;
    if(c == '+' || c == '-') return 2;
    if(c == '*' || c == '/') return 3;
    else return -1;
}

void cut(){
    for(int i = 0; i < input.length(); i++){
        if(vec.empty() == false && priority(input[i]) == 0 && priority(vec.back()[0]) == 0){
            string temp = vec.back();
            vec.pop_back();
            temp += input[i];
            vec.push_back(temp);
        }
        else{
            string temp = "";
            temp += input[i];
            vec.push_back(temp);
        }
    }
}

void postfix(){
    stack<string> s;
    for(int i = 0; i < vec.size(); i++){
        int p = priority(vec[i][0]);
        if(p == 0) res.push_back(vec[i]);
        else if(p == 1){
            if(vec[i] == "("){
                s.push(vec[i]);
            }
            else if(vec[i] == ")"){
                while(true){
                    if(s.top() == "("){
                        s.pop();
                        break;
                    }
                    else{
                        res.push_back(s.top());
                        s.pop();
                    }
                }
            }
        }
        else if(p == 2 || p == 3){
            if(s.empty()) s.push(vec[i]);
            else if(priority(s.top()[0]) < p) s.push(vec[i]);
            else{
                res.push_back(s.top());
                s.pop();
                s.push(vec[i]);
            }
        }
    }
    int size = s.size();
    for(int i = 0; i < size; i++){
        res.push_back(s.top());
        s.pop();
    }
}

void eval(){
    stack<int> s;
    for(int i = 0; i < res.size(); i++){
        if(priority(res[i][0]) == 0){
            s.push(stoi(res[i]));
        }
        else{
            if(s.size() < 2){
                wrong = true;
                break;
            }
            else{
                char c = res[i][0];
                int m = s.top();
                s.pop();
                int n = s.top();
                s.pop();
                if(c == '+') s.push(n + m);
                else if(c == '-') s.push(n - m);
                else if(c == '*') s.push(n * m);
                else if(c == '/') s.push(n / m);
            }
        }
    }
    if(s.size() > 1) wrong = true;
    else answer = s.top();
}

int main(){
    cin >> input;
    cut();
    postfix();
    eval();
    if(wrong == true) cout << "ROCK";
    else cout << answer;
}