//
//  main.cpp
//  UVA506
//
//  Created by zhangmin chen on 2019/5/24.
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
typedef set<string>::iterator ssii;

const int maxn = 10000 + 10;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

vector<int> depends[maxn];
vector<int> pa[maxn];
int status[maxn];
int cnt = 0;

map<string, int> str2id;
string id2str[maxn];

vector<int> installed;

int ID(const string& item) {
    if(!str2id.count(item)) {
        //
        id2str[++cnt] = item;
        str2id[item] = cnt;
    }
    return str2id[item];
}


void init() {
    Set(status, 0);
    cnt = 0;
}

void list() {
    _for(i, 0, installed.size()) {
        int u = installed[i];
        cout << "   " << id2str[u] << endl;
    }
}

void install(int id, bool explicity) {
    //
    if(!status[id]) {
        // install id
        _for(i, 0, depends[id].size()) {
            int u = depends[id][i];
            install(u, false);
        }
        // dependencity has already been installed
        cout << "   Installing " << id2str[id] << endl;
        status[id] = explicity ? 1 : 2;
        
        installed.push_back(id);
    }
}


bool needed(int id) {
    //
    _for(i, 0, pa[id].size()) {
        int u = pa[id][i];
        if(status[u]) return true;
    }
    return false;
}

void rmv(int id, bool explicity) {
    //
    if( (explicity || status[id] == 2) && !needed(id) ) {
        status[id] = 0;
        installed.erase(find(installed.begin(), installed.end(), id));
        
        cout << "   Removing " << id2str[id] << endl;
        
        _for(i, 0, depends[id].size()) {
            int u = depends[id][i];
            rmv(u, false);
        }
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    
    init();
    string line, cmd;
    while (getline(cin, line)) {
        cout << line << endl;
        stringstream ss(line);
        ss >> cmd;
        
        if(cmd[0] == 'E') break;
        if(cmd[0] == 'L') list();
        else {
            //
            string item1, item2;
            ss >> item1;
            int id1 = ID(item1);
            
            if(cmd[0] == 'D') {
                while (ss >> item2) {
                    int id2 = ID(item2);
                    depends[id1].push_back(id2);
                    pa[id2].push_back(id1);
                }
            }
            else if(cmd[0] == 'I') {
                //
                if(status[id1]) cout << "   " << item1 << " is already installed." << endl;
                else install(id1, true);
            }
            else {
                if(!status[id1]) cout <<  "   " << item1 << " is not installed." << endl;
                else if(needed(id1)) cout << "   " << item1 << " is still needed." << endl;
                else rmv(id1, true);
            }
        }
    }
}
