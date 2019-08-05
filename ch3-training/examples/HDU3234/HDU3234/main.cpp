//
//  main.cpp
//  HDU3234
//
//  Created by zhangmin chen on 2019/7/10.
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

const int maxn = 20000 + 10;
const int maxl = 40000 + 10;

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


int n, q;
int pa[maxn], d[maxn];
int vis[maxn];
int line[maxl][3];
int data[maxn];

void initSet() {
    Set(line, 0);
    Set(data, 0);
    _for(i, 0, maxn) {
        pa[i] = i;
        d[i] = 0;
    }
}

int findSet(int x) {
    if(x == pa[x]) return x;
    else {
        int root = findSet(pa[x]);
        d[x] ^= d[pa[x]];
        return pa[x] = root;
    }
}


bool combine(int p, int q, int v) {
    int rootp = findSet(p);
    int rootq = findSet(q);
    
    if(rootp == rootq) return (d[p] ^ d[q]) == v;
    //debug(nil);
    
    // union rootp and rootq, d[p] ^ d[q] = v
    // pa[rootp] = rootq
    
    if(rootp == n) swap(rootp, rootq);
    pa[rootp] = rootq;
    d[rootp] = (d[p] ^ d[q] ^ v);
    return true;
}

int query(const int *data, int k) {
    int ans = 0;
    Set(vis, 0);
    _for(i, 0, k) {
        // d[data[i]]
        
        if(vis[i]) continue;
        int cnt = 0, root = findSet(data[i]);
        _for(j, i, k) {
            if(!vis[j] && root == findSet(data[j])) {
                vis[j] = 1;
                cnt++;
                
                ans ^= d[data[j]];
            }
        }
        if(root != n && cnt % 2 == 1) return -1;
    }
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    int cnt = 0;
    while (scanf("%d%d", &n, &q) && (n + q)) {
        initSet();
        printf("Case %d:\n", ++cnt);
        //debug(n);
        
        int ic = 0;
        bool bug = 0;
        _for(i, 0, q) {
            string str;
            cin >> str;
            
            if(str[0] == 'I') {
                //
                ic++;
                int sz = 0;
                while(cin >> line[i][sz++]) if(getchar() == '\n') break;
                if(bug) continue;
                
                int p = 0, q = 0, v = 0;
                if(sz == 2) {
                    // I p v, data[0] = p, data[1] = v
                    p = line[i][0]; v = line[i][1];
                    q = n;
                }
                else if(sz == 3) {
                    // I p q v
                    p = line[i][0]; q = line[i][1]; v = line[i][2];
                }
                
                if(!combine(p, q, v)) {
                    printf("The first %d facts are conflicting.\n", ic);
                    bug = 1;
                }
            }
            else if(str[0] == 'Q') {
                // k p1 p2 ... pk
                int k;
                scanf("%d", &k);
                // _for(i, 0, data.size()) cout << data[i] << " ";
                // cout << endl;
                _for(i, 0, k) scanf("%d", &data[i]);
                
                if(bug) continue;
                int res = query(data, k);
                if(res == -1) printf("I don't know.\n");
                else printf("%d\n", res);
                
            }
            // _for(i, 0, data.size()) cout << data[i] << " ";
            // cout << endl;
        }
        puts("");
    }
}
