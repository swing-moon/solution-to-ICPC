//
//  main.cpp
//  UVA1598
//
//  Created by zhangmin chen on 2019/5/4.
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

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;


class Order {
public:
    string cmd;
    int price, size;
    
    Order(string str, int p, int s) : cmd(str), price(p), size(s) {}
};

map<int, set<int> > buypq, sellpq;
map<int, int> buytab, selltab;
vector<Order> books;

void init() {
    //
    books.clear();
    buypq.clear();
    sellpq.clear();
    
    buytab.clear();
    selltab.clear();
}

void trade(int flag) {
    //
    // flag 0 for buy, flag 1 for sell
    // buy -> match books[sell]
    // sell -> match books[buy]
    while (!buypq.empty() && !sellpq.empty()) {
        int bidP = buypq.rbegin()->first, askP = sellpq.begin()->first;
        
        if(bidP >= askP) {
            // trade
            set<int>& bitem = buypq.rbegin()->second;
            set<int>& sitem = sellpq.begin()->second;
            
            // bitem = {id1, id2....}, sitem = {id1, id2,...}
            
            int bi = *bitem.begin(), si = *sitem.begin();
            int sz = min(books[bi].size, books[si].size);
            
            // then print trade information
            printf("TRADE %d %d\n", sz, flag ? books[bi].price : books[si].price);
            
            // trade begin
            books[bi].size -= sz; books[si].size -= sz;
            buytab[books[bi].price] -= sz; selltab[books[si].price] -= sz;
            
            if(books[bi].size == 0) bitem.erase(bi);
            if(bitem.size() == 0) buypq.erase(books[bi].price);
            
            if(books[si].size == 0) sitem.erase(si);
            if(sitem.size() == 0) sellpq.erase(books[si].price);
        } else {
            return;
        }
    }
}

void quote() {
    //
    while(buytab.size() && buytab.rbegin()->second <= 0)
        buytab.erase(buytab.rbegin()->first);
    while(selltab.size() && selltab.begin()->second <= 0)
        selltab.erase(selltab.begin()->first);
    
    printf("QUOTE ");
    if(buytab.size()) {
        // print (size, price) = (second, first)
        printf("%d %d", buytab.rbegin()->second, buytab.rbegin()->first);
    } else {
        printf("0 0");
    }
    
    cout << " - ";
    
    if(selltab.size()) {
        printf("%d %d", selltab.begin()->second, selltab.begin()->first);
    } else {
        printf("0 99999");
    }
    cout << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    int n = 0, kase = 0;
    string cmd;
    
    while(scanf("%d", &n) == 1) {
        //
        if(kase++) cout << endl;
        
        init();
        
        int size, price;
        int id;
        for(int i = 0; i < n; i++) {
            cin >> cmd;
            if(cmd == "BUY") {
                cin >> size >> price;
                books.push_back(Order(cmd, price, size));
                
                buypq[price].insert(i);
                buytab[price] += size;
                trade(0);
            } else if(cmd == "SELL") {
                cin >> size >> price;
                books.push_back(Order(cmd, price, size));
                
                sellpq[price].insert(i);
                selltab[price] += size;
                trade(1);
            } else if(cmd == "CANCEL") {
                cin >> id; id--;
                books.push_back(Order(cmd, 0, id));
                // 0 is illegal
                
                if(books[id].cmd == "BUY") {
                    //
                    int p = books[id].price, q = books[id].size;
                    buypq[p].erase(id);
                    if(buypq[p].size() == 0) buypq.erase(p);
                    buytab[p] -= q;
                    
                    books[id].size = 0;
                    
                } else if(books[id].cmd == "SELL") {
                    //
                    int p = books[id].price, q = books[id].size;
                    sellpq[p].erase(id);
                    if(sellpq[p].size() == 0) sellpq.erase(p);
                    selltab[p] -= q;
                    
                    books[id].size = 0;
                }
            }
            
            // one cmd finished
            quote();
        }
    }
}
