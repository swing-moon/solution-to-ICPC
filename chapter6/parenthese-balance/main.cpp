#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <cassert>

using namespace std;

bool isValid(const char* s) {
    stack<char> stk;

    for(int i = 0; i < strlen(s); i++) {
        char cur = s[i];
        if(cur == '(' || cur == '[') stk.push(cur);
        else {
            assert(cur == ')' || cur == ']');

            if(stk.empty()) return false;
            char t = stk.top();

            if(cur == ')') {
                if(t == '(') stk.pop();
                else break;
            }
            else if(cur == ']') {
                if(t == '[') stk.pop();
                else break;
            }
        }
    }
    return stk.empty();
}

int main() {
    int n;
    char buf[256];

    scanf("%d\n", &n);
    while(n--) {
        gets(buf);
        if(isValid(buf)) puts("Yes");
        else puts("No");
    }
    return 0;
}