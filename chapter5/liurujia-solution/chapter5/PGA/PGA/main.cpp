//
//  main.cpp
//  PGA
//
//  Created by zhangmin chen on 2019/4/26.
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

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)

// const int maxn = 145;
const int przn = 70;


class Player {
public:
    string name;
    double prize;
    bool amat;
    bool t;
    
    int rnd[4];
    int dq;
    int rank;
    int pre, tot;
    
    // pre used to decide which one can be in round[3, 4], make the cut
    // tot used to divide money
    // only made the cut plyer can get money
    
    // divide prize:
    // 1/ parallel
    // 2/ amt don't get prize
    // 3/ get prize?    Not amter && rank[1,70]
    
    
    // DQ:
    // 1/ DQ > 2, plyer can make the cut
    // 2/ but not rank in rnd[3,4]
    
    // make the cut:
    // DQ == 0 || DQ > 2   ---> make the cut
    
    // rank:
    // only DQ == 0 rank
    
    Player() {
        name.clear();
        prize = 0.0;
        amat = t = false;
        
        memset(rnd, 0, sizeof(rnd));
        dq = 4;
        rank = 0;
        pre = tot = 0;
    }
    
    void init() {
        prize = 0.0;
        amat = t = false;
        
        memset(rnd, 0, sizeof(rnd));
        dq = 4;
        rank = 0;
        pre = tot = 0;
    }
};

int n;

vector<Player> plyers;
double priz[przn];
double sum;

int str2num(const string& str) {
    int val = 0;
    for(int i = 0; i < str.length(); i++) {
        val = val * 10 + str[i] - '0';
    }
    //debug(val);
    return val;
}


void init() {
    //
    //for(int i = 0; i < n; i++) plyers[i].init();
    plyers.clear();
    
    memset(priz, 0, sizeof(priz));
    scanf("%lf", &sum);
    
    for(int i = 0; i < 70; i++) {
        scanf("%lf", &priz[i]);
        priz[i] = priz[i] / 100.0 * sum;
    }
}

void initPlyer() {
    //scanf("%d", &n);
    cin >> n;
    plyers.resize(n+1);
    
    string str;
    getline(cin, str);
    
    for(int i = 0; i < n; i++) {
        plyers[i].tot = 0;
        getline(cin, str);
        
        plyers[i].name = str.substr(0, 20);
        str = str.substr(20);
        
        if(plyers[i].name.find('*') != string::npos) {
            plyers[i].amat = true;
        }
        
        
        stringstream ss(str);
        //string data;
        // is >> data
        for(int j = 0; j < 4; j++) {
            string data;
            ss >> data;
            
            if(data == "DQ") {
                plyers[i].dq = j;
                break;
            }
            else {
                plyers[i].rnd[j] = str2num(data);
            }
            
            if(j < 2) {
                plyers[i].pre += str2num(data);
            }
            plyers[i].tot += str2num(data);
        }
        // debug("----");
    }
}


bool cmp1(const Player& lhs, const Player& rhs) {
    if(lhs.dq > 1 && rhs.dq > 1) return lhs.pre < rhs.pre;
    return lhs.dq > rhs.dq;
}


int makeCut() {
    sort(plyers.begin(), plyers.begin() + n, cmp1);
    int pos = 0;
    
    while (pos < min(70, n) && plyers[pos].dq > 1) {
        pos++;
    }
    // [0, 69] --> 70
    
    while (plyers[pos].dq > 1 && plyers[pos].pre == plyers[pos-1].pre) {
        pos++;
    }
    
    return pos;
}

// usage: int pos = makeCut
// getRank(pos)


bool cmp2(const Player& lhs, const Player& rhs) {
    if(lhs.dq != rhs.dq) return lhs.dq > rhs.dq;
    if(lhs.tot != rhs.tot) return lhs.tot < rhs.tot;
    return lhs.name < rhs.name;
}

// important!
// difficult: parallel situation
void getRank(int num) {
    //
    sort(plyers.begin(), plyers.begin() + num, cmp2);
    
    // divide money
    // 1. parallel
    // 2. amte cannot get money
    // no amte and rank from [0, 70]
    
    // now: plyers[0...num-1]
    
    
    int k = 0, rkp = 0;
    int rk = 0;
    while(k < num) {
        if(plyers[k].dq < 4) break;
        
        // parallel: [k, p) rank: rk
        
        int p = k, cnt = 0;
        double sum = 0.0;
        
        int prll = 0;
        while(plyers[p].dq == 4 && plyers[p].tot == plyers[k].tot) {
            //
            if(!plyers[p].amat) {
                //
                sum += priz[rkp + cnt];
                cnt++;
                //
            }
            p++;
            prll++;
        }
        
        sum /= cnt;
        
        // assign prize:
        for(int i = k; i < p; i++) {
            plyers[i].rank = rk + 1;
            
            // prize is not enough
            if(rkp > 69) {
                plyers[i].amat = true;
                plyers[i].t = false;
            }
            
            if(!plyers[i].amat) {
                plyers[i].prize = sum;
                plyers[i].t = cnt > 1;
            }
        }
        
        
        
        // [k, p) rank: rk
        // rk [0, 70)
        // [p, ...) rank: rk += cnt
        // plyers[].rank = rk + 1;
        
        k = p;
        rkp += cnt;
        rk += prll;
    }
    
}


void printAns(int num) {
    //
    printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n");
    printf("-----------------------------------------------------------------------\n");
    
    for(int i = 0; i < num; i++) {
        printf("%-21s", plyers[i].name.c_str());
        
        if(plyers[i].dq < 4) printf("          ");
        else {
            char t[5];
            sprintf(t, "%d%c", plyers[i].rank, plyers[i].t ? 'T' : ' ');
            printf("%-10s", t);
        }
        
        for(int j = 0; j < plyers[i].dq; j++) printf("%-5d", plyers[i].rnd[j]);
        for(int j = plyers[i].dq; j < 4; j++) printf("     ");
        
        if(plyers[i].dq < 4) printf("DQ");
        else if(!plyers[i].amat) printf("%-10d", plyers[i].tot);
        else printf("%d", plyers[i].tot);
        
        if(plyers[i].dq < 4 || plyers[i].amat) {
            printf("\n");
            continue;
        }
        
        printf("$%9.2lf\n", plyers[i].prize);
        //int ans = floor((plyers[i].prize + 0.0050001) * 100);
        //plyers[i].prize = ans / 100.0;
        //cout.setf(ios::right);
        //cout << "$" << setw(9) << fixed << setprecision(2) << plyers[i].prize << endl;
        
        //int ans = (int)((plyers[i].prize + 0.0005) * 10000);
        //printf("$%9.2lf\n", ans / 1000.0);
    }
    
}

// attend rnd[3,4], we need plyer.dq > 2


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int kase;
    scanf("%d", &kase);
    
    while(kase--) {
        
        init();
        // get prize data
        initPlyer();
        
        int num = makeCut();
        getRank(num);
        printAns(num);
        if(kase) printf("\n");
        
    }
}
