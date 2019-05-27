//
//  main.cpp
//  LA4592
//
//  Created by zhangmin chen on 2019/4/24.
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

using namespace std;
typedef long long llong;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)

typedef pair<int, int> pii;
int m, n;
map<string, int> idx;

const int maxr = 10000 + 10;
const int maxc = 100 + 10;

int db[maxr][maxc], cnt = 0;

void init() {
    memset(db, 0, sizeof(db));
    idx.clear();
}

int getID(const string& str) {
    if(!idx.count(str)) return idx[str] = ++cnt;
    return idx[str];
}

void solve() {
    for(int c1 = 0; c1 < m; c1++) for(int c2 = c1+1; c2 < m; c2++) {
        map<pii, int> group;
        // group[c1, c2] = ith row
        
        // const pii& pr = make_pair();
        
        for(int i = 0; i < n; i++) {
            // group[(i,c1), (i,c2)] = ith row
            const pii& pr = make_pair(db[i][c1], db[i][c2]);
            
            if(group.count(pr)) {
                //
                printf("NO\n");
                printf("%d %d\n", group[pr]+1, i+1);
                printf("%d %d\n", c1+1, c2+1);
                return;
            }
            group[pr] = i;
        }
    }
    printf("YES\n");
    return;
}


int main() {
    freopen("input.txt", "r", stdin);
    while(cin >> n >> m) {
        init();
        
        
        string str;
        getline(cin, str);
        
        for(int i = 0; i < n; i++) {
            getline(cin, str);
            // cout << str << endl;
            // split by ','
            
            int k = -1;
            for(int j = 0; j < m; j++) {
                int p = (int)str.find(',', k+1);
                if(p == string::npos) p = (int)str.length();
                
                int hashv = getID(str.substr(k+1, p-k-1));
                db[i][j] = hashv;
                k = p;
                // db[i][j] = hash(substr)
            }
            
        }
        
        // get data finished!
        // then we solve the problem
        
        solve();
    }
}
