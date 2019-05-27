//
//  main.cpp
//  LA5266
//
//  Created by zhangmin chen on 2019/3/3.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>

#define debug(x) cout << #x << ": " << x << endl;
#define Set(x, v) memset(x, v, sizeof(x));

using namespace std;
const int maxn = 10000 + 10;
const int maxv = 0x3f3f3f3f;

struct Node {
    Node* left;
    Node* right;
    int val;
    Node(int x) {
        left = NULL;
        right = NULL;
        val = x;
    }
};

typedef Node *nodep;
int n;

bool read(int* ans) {
    string line;
    if(!getline(cin, line)) return false;
    stringstream ss(line);
    n = 0;
    int x;
    while(ss >> x) ans[n++] = x;
    return n > 0;
}

int inOrd[maxn], postOrd[maxn];

void init() {
    Set(inOrd, 0); Set(postOrd, 0);
}

// inorder[l1...r1], left + root + right
// postorder[l2...r2] left + right + root
nodep build(int l1, int r1, int l2, int r2) {
    if(l1 > r1) return 0;
    int val = postOrd[r2];
    
    nodep root = new Node(val);
    int p = l1;
    for(; p <= r1; p++) {
        if(inOrd[p] == val) break;
    }
    
    int cnt = p-l1;
    root->left = build(l1, p-1, l2, l2+cnt-1);
    root->right = build(p+1, r1, l2+cnt, r2-1);
    
    return root;
}

int bestw, bestsum;

void dfs(nodep u, int sum) {
    sum += u->val;
    if(u->left == NULL && u->right == NULL) {
        if(sum < bestsum || (sum == bestsum && u->val < bestw)) {
            bestw = u->val;
            bestsum = sum;
        }
    }
    if(u->left != NULL) dfs(u->left, sum);
    if(u->right != NULL) dfs(u->right, sum);
}


int main() {
    freopen("input.txt", "r", stdin);
    while (read(inOrd)) {
        read(postOrd);
        
        // build:
        nodep tree = build(0, n-1, 0, n-1);
        bestsum = maxv;
        dfs(tree, 0);
        printf("%d\n", bestw);
        init();
    }
}


