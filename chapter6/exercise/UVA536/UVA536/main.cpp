//
//  main.cpp
//  UVA536
//
//  Created by zhangmin chen on 2019/3/3.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <vector>
#include <cstdlib>
#include <algorithm>

#define debug(x) cout << #x << ": " << x << endl;
#define Set(a, v) memset(a, v, sizeof(a));
using namespace std;


const int maxn = 100000 + 10;

char preOrd[maxn], inOrd[maxn];
void init() {
    Set(preOrd, 0); Set(inOrd, 0);
}

struct Node {
    Node* left;
    Node* right;
    char val;
    
    Node(char v) {
        val = v;
        left = NULL;
        right = NULL;
    }
};
typedef Node *nodep;

// pre[l1...r1], root + left + right
// inOrd[l2...r2] left + root + right
nodep build(int l1, int r1, int l2, int r2) {
    //
    if(l1 > r1) return NULL;
    // important!
    char val = preOrd[l1];
    nodep root = new Node(val);
    
    int p = l2;
    for(; p <= r2; p++) {
        if(inOrd[p] == val) break;
    }
    
    int cnt = p-l2;
    root->left = build(l1+1, l1+1+cnt-1, l2, p-1);
    root->right = build(l1+cnt+1, r1, p+1, r2);
    
    return root;
}

void printTree(nodep u) {
    if(u->left != NULL) printTree(u->left);
    if(u->right != NULL) printTree(u->right);
    printf("%c", u->val);
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%s%s", preOrd, inOrd) == 2) {
        //
        int len1 = (int)strlen(preOrd), len2 = (int)strlen(inOrd);
        
        // build tree
        nodep tree = build(0, len1-1, 0, len2-1);
        printTree(tree);
        printf("\n");
    }
}
