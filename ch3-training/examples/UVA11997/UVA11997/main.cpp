//
//  main.cpp
//  UVA11997
//
//  Created by zhangmin chen on 2019/7/8.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

const int maxn = 750 + 10;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _forS(i, l, r) for(set<int>::iterator i = (l); i != (r); i++)
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)

int A[maxn][maxn];
int n;

void init() {
    Set(A, 0);
}

class Node {
public:
    int S, b;
    Node(int _S = 0, int _b = 0) : S(_S), b(_b) {}
    
    bool operator< (const Node& rhs) const {
        return S > rhs.S;
    }
};

void _merge(int* A, int* B, int* C, int n) {
    priority_queue<Node> pq;
    _for(i, 0, n) pq.push(Node(A[i] + B[0], 0));
    
    _for(i, 0, n) {
        Node x = pq.top();
        pq.pop();
        
        C[i] = x.S;
        if(x.b + 1 < n) pq.push(Node(x.S - B[x.b] + B[x.b+1], x.b+1));
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1) {
        init();
        _for(i, 0, n) _for(j, 0, n) scanf("%d", &A[i][j]);
        _for(i, 0, n) sort(A[i], A[i] + n);
        
        _for(i, 1, n) _merge(A[0], A[i], A[0], n);
        
        printf("%d", A[0][0]);
        _for(i, 1, n) printf(" %d", A[0][i]);
        
        printf("\n");
    }
}
