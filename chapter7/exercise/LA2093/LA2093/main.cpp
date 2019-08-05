//
//  main.cpp
//  LA2093
//
//  Created by zhangmin chen on 2019/7/27.
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
#include <bitset>
#include <assert.h>
#include <unordered_set>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;


#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
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

const int N = 15;
const int D = 6;

const int DIR[N + 1][D] = {
    {0, 0, 0, 0, 0, 0}, // 0
    {0, 0, 0, 0, 2, 3}, // 1
    {0, 1, 0, 3, 4, 5}, // 2
    {1, 0, 2, 0, 5, 6}, // 3
    {0, 2, 0, 5, 7, 8}, // 4
    {2, 3, 4, 6, 8, 9}, // 5
    {3, 0, 5, 0, 9, 10}, // 6
    {0, 4, 0, 8, 11, 12}, // 7
    {4, 5, 7, 9, 12, 13}, // 8
    {5, 6, 8, 10, 13, 14}, // 9
    {6, 0, 9, 0, 14, 15}, // 10
    {0, 7, 0, 12, 0, 0}, // 11
    {7, 8, 11, 13, 0, 0}, // 12
    {8, 9, 12, 14, 0, 0}, // 13
    {9, 10, 13, 15, 0, 0}, // 14
    {10, 0, 14, 0, 0, 0} // 15
};

template<typename T>
ostream& operator<< (ostream& os, const vector<T>& vec) {
    _for(i, 0, vec.size()) {
        if(i != 0) os << " ";
        os << vec[i];
    }
    return os;
}

class Board {
public:
    int st, cnt;
    vector<int> path;
    
    Board() {
        st = 0b1111111111111111;
        cnt = N;
        path.clear();
    }
    
    bool isEmpty(int i) const {
        if((st & (1 << i)) != 0) return false;
        else return true;
    }
    
    void clear(int i) {
        assert(!isEmpty(i));
        st ^= (1 << i);
        cnt--;
    }
    
    void put(int i) {
        assert(isEmpty(i));
        st |= (1 << i);
        cnt++;
    }
    
    int jumpTo(int i, int d) const {
        // follow the direction d to jump to xxx
        int to = DIR[i][d];
        if(!to || isEmpty(to)) return 0;
        // 0 is nil, means can not jump
        
        while(to && !isEmpty(to)) to = DIR[to][d];
        return to;
    }
    
    void dbg() {
        int len = 1, p = 1;
        cout << "cnt = " << cnt << endl;
        
        _rep(i, 1, N) {
            if(isEmpty(i)) cout << "_";
            else cout << "*";
            
            if(i == p) {
                cout << endl;
                len += 1; p += len;
            }
        }
        
        cout << endl;
        cout << path.size() << " -> " << path << endl;
    }
};

// Board bd;
queue<Board> que;
unordered_set<int> vis;

void init() {
    while(!que.empty()) que.pop();
    vis.clear();
}

void initBFS(int x) {
    Board bd;
    bd.clear(x);
    que.push(bd);
    vis.insert(bd.st);
}

void bfs(int x) {
    // x is init empty place
    initBFS(x);
    
    while (!que.empty()) {
        Board cur = que.front();
        que.pop();
        
        if(cur.cnt == 1 && !cur.isEmpty(x)) {
            // founded! print ans
            cout << cur.path.size() / 2 << endl;
            cout << cur.path << endl;
            return;
        }
        
        // then find next
        _rep(i, 1, N) {
            if(cur.isEmpty(i)) continue;
            
            _for(d, 0, D) {
                // jump to the next
                int to = cur.jumpTo(i, d);
                if(!to) continue;
                
                // i --dir d--> to
                Board nxtb = cur;
                assert(nxtb.isEmpty(i) == false);
                
                nxtb.clear(i);
                int j = DIR[i][d];
                while(j != to) {
                    nxtb.clear(j);
                    j = DIR[j][d];
                }
                // [i, to] in direction d, is all cleared
                
                // then put ball in hole to
                nxtb.put(to);
                if(vis.count(nxtb.st)) continue;
                
                vis.insert(nxtb.st);
                nxtb.path.push_back(i);
                nxtb.path.push_back(to);
                
                que.push(nxtb);
            }
        }
        
    }
    
    cout << "IMPOSSIBLE\n";
}


int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    
    while (T--) {
        // bfs(int x)
        // x is empty point
        
        init();
        int x;
        scanf("%d", &x);
        
        bfs(x);
    }
}
