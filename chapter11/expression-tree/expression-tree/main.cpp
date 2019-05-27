//
//  main.cpp
//  expression-tree
//
//  Created by zhangmin chen on 2018/10/19.
//  Copyright © 2018 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 1000;
int lch[maxn], rch[maxn];
// we check id of left node and right node

char op[maxn];
// reserve the result in op[]

int cnt = 0;

int build_tree(char* s, int x, int y) {
    // y is (the last char of string) + 1
    int c1 = -1, c2 = -1, br = 0;
    int u;
    
    if(y - x <= 1) {
        // only one node
        u = cnt++;
        lch[u] = rch[u] = 0;
        op[u] = s[x];
        return u;
    }
    
    for(int i = x; i < y; i++) {
        switch (s[i]) {
            case '(': br++; break;
            case ')': br--; break;
            case '+': case '-': if(br == 0) c1 = i; break;
            case '*': case '/': if(br == 0) c2 = i; break;
        }
    }
    
    if(c1 < 0) c1 = c2;
    if(c1 < 0) return build_tree(s, x+1, y-1);
    
    // create node
    u = cnt++;
    lch[u] = build_tree(s, x, c1);
    rch[u] = build_tree(s, c1+1, y);
    op[u] = s[c1];
    return u;
}


// op[node] --> print

void print_tree(int u) {
    if(lch[u]) print_tree(lch[u]);
    printf(" %c", op[u]);
    if(rch[u]) print_tree(rch[u]);
}

void print_by_level_twopoint(int u) {
    vector<int> vec;
    vec.push_back(u);
    int s = 0, t = 1;
    int level = 0;
    
    while(s < vec.size()) {
        t = (int)vec.size();
        while(s < t) {
            printf(" %c", op[vec[s]]);
            if(lch[vec[s]]) vec.push_back(lch[vec[s]]);
            if(rch[vec[s]]) vec.push_back(rch[vec[s]]);
            s++;
        }
        printf("level: %d\n", ++level);
    }
}

void print_by_level_queue(int u) {
    queue<int> q1, q2;
    int level = 0;

    q1.push(u);
    while(!q1.empty()) {
        while(!q1.empty()) {
            int cur = q1.front(); q1.pop();
            printf(" %c", op[cur]);
            
            if(lch[cur]) q2.push(lch[cur]);
            if(rch[cur]) q2.push(rch[cur]);
        }
        
        printf(" level: %d\n", ++level);
        q1.swap(q2);
    }
}

int main() {
    char str[maxn];
    scanf("%s", str);
    int n = (int)strlen(str);
    cout << n << endl;
    
    build_tree(str, 0, n);
    print_tree(0);
    cout << endl;
    
    // ergodic at level
    // cout << "print by level" << endl;
    print_by_level_twopoint(0);
    cout << endl;
    print_by_level_queue(0);
}
