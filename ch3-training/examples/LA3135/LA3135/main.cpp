//
//  main.cpp
//  LA3135
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

class Topic {
public:
    int _qnum, _period, _time;
    bool operator< (const Topic& rhs) const {
        if(_time != rhs._time) return _time > rhs._time;
        return _qnum > rhs._qnum;
    }
};

priority_queue<Topic> topics;

void init() {
    while(!topics.empty()) topics.pop();
}

int main() {
    freopen("input.txt", "r", stdin);
    char cmd[20];
    init();
    while (scanf("%s", cmd) && cmd[0] != '#') {
        Topic cur;
        scanf("%d%d", &cur._qnum, &cur._period);
        cur._time = cur._period;
        topics.push(cur);
    }
    
    int k;
    scanf("%d", &k);
    while (k--) {
        Topic x = topics.top();
        topics.pop();
        printf("%d\n", x._qnum);
        x._time += x._period;
        topics.push(x);
    }
}
