#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 60000;
int T, kase;
int cnt, done[maxn];
char expr[maxn], *p;

struct Node {
    string s;
    int hash, left, right;
    bool operator < (const Node& rhs) const {
        if(hash != rhs.hash) return hash < rhs.hash;
        if(left != rhs.left) return left < rhs.left;
        return right < rhs.right;
    }
} nodes[maxn];

map<Node, int> dict;

// build() return root id
// print out id+1
int build() {
    int id = cnt++;
    Node& u = nodes[id];

    u.left = u.right = -1;
    u.hash = 0;
    u.s = "";

    // traversal
    while(isalpha(*p)) {
//        u.hash = u.hash * 27 + (*p - 'a' + 1);
        u.hash <<= 8;
        u.hash |= *p;
        u.s.push_back(*p);
        p++;
    }

    if(*p == '(') {
        p++; u.left = build();
        // recursion, *p = ')', recall;

        p++; u.right = build();
        p++;
    }

    // if *p is ')', means we finished
    // recall, check u is existed

    if(dict.count(u) != 0) {
        id--; cnt--;
        return dict[u];
    }
    return dict[u] = id;
}

void print(int v) {
    //
    if(done[v] == kase) {
        printf("%d", v+1);
    } else {
        done[v] = kase;
        // traversal, if we meet v, done[v] is already get the value
        // kase, we print out immediately
        printf("%s", nodes[v].s.c_str());

        if(nodes[v].left != -1) {
            printf("(");
            print(nodes[v].left);
            printf(",");
            print(nodes[v].right);
            printf(")");
        }
    }
}


int main() {
    scanf("%d", &T);
    for(kase = 1; kase <= T; kase++) {
        //
        dict.clear();
        cnt = 0;
        scanf("%s", expr);
        p = expr;
        print(build());
        printf("\n");
    }
}