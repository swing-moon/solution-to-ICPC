//
//  main.cpp
//  HDU2766
//
//  Created by zhangmin chen on 2019/3/4.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <map>

#define debug(x) cout << #x << ": " << x << endl
#define Set(x, v) memset(x, v, sizeof(x))
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define FOR(i, l, r) for(int i = (l); i < (r); i++)

using namespace std;
typedef long long llong;
typedef map<llong, int>::iterator mli;
typedef vector<int>::iterator vit;

const int maxn = 24;

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);
    
    string line;
    map<llong, int> tree;
    
    while(kase--) {
        tree.clear();
        cin >> line;
        int sz = (int)line.length();
        
        int depth = 0, tot = 0;
        for(int i = 0; i < sz; i++) {
            //
            char ch = line[i];
            if(ch == '[') depth++;
            else if(ch == ']') depth--;
            else if(isdigit(ch)) {
                //
                llong x = ch - '0';
                int j;
                for(j = i+1; j < sz && isdigit(line[j]); j++) {
                    //
                    x *= 10;
                    x += line[j] - '0';
                }
                i = j-1;
                x <<= depth;
                tree[x]++;
                tot++;
            }
        }
        
        int ans = -1;
        for(mli p = tree.begin(); p != tree.end(); p++) {
            ans = max(ans, p->second);
        }
        printf("%d\n", tot-ans);
    }
    
}
