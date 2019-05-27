//
//  main.cpp
//  LA5185
//
//  Created by zhangmin chen on 2019/3/30.
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

const int CNT = 52;
const int maxn = 7;

int read() {
    int x;
    scanf("%d", &x);
    return x;
}

struct Pile {
    deque<int> cards;
    Pile *left, *right;
    
    void init() {
        cards.clear();
        left = right = nullptr;
    }
};

typedef Pile* Pilep;
Pile piles[maxn+1], *nil;
set<string> status;

deque<int> hcards;

void link(Pilep l, Pilep r) {
    l->right = r;
    r->left = l;
}

void start() {
    // init
    hcards.clear();
    status.clear();
    for(int i = 0; i <= maxn; i++) {
        piles[i].init();
    }
}

void deal(Pile& p) {
    int sz = (int)p.cards.size();
    if(sz < 3) return;
    
    if( (p.cards[0]+p.cards[1]+p.cards.back()) % 10 == 0 ) {
        //
        hcards.push_back(p.cards[0]); hcards.push_back(p.cards[1]); hcards.push_back(p.cards.back());
        p.cards.pop_front(); p.cards.pop_front(); p.cards.pop_back();
        deal(p);
        return;
    }
    
    if( (p.cards[0]+p.cards[sz-2]+p.cards[sz-1]) % 10 == 0 ) {
        //
        hcards.push_back(p.cards[0]); hcards.push_back(p.cards[sz-2]); hcards.push_back(p.cards[sz-1]);
        p.cards.pop_front(); p.cards.pop_back(); p.cards.pop_back();
        deal(p);
        return;
    }
    
    if( (p.cards[sz-3]+p.cards[sz-2]+p.cards[sz-1]) % 10 == 0 ) {
        hcards.push_back(p.cards[sz-3]); hcards.push_back(p.cards[sz-2]); hcards.push_back(p.cards[sz-1]);
        p.cards.pop_back(); p.cards.pop_back(); p.cards.pop_back();
        deal(p);
        return;
    }
}

void encode(string& ans) {
    ans.clear();
    Pilep first = nil->right;
    while(first != nil) {
        for(int i = 0; i < first->cards.size(); i++) ans += (char)first->cards[i];
        
        ans += '|';
        first = first->right;
    }
    
    for(int i = 0; i < hcards.size(); i++) ans += (char) hcards[i];
}

void putCard() {
    int cur = hcards.front();
    hcards.pop_front();
    
    Pilep first = nil->right;
    link(nil, first->right);
    link(nil->left, first);
    link(first, nil);
    
    first->cards.push_back(cur);
    deal(*first);
    if(first->cards.empty()) link(first->left, first->right);
}

bool simulate(int times) {
    if(nil->right == nil) {
        cout << "Win : " << times << endl;
        return false;
    }
    if(hcards.empty()) {
        cout << "Loss: " << times << endl;
        return false;
    }
    
    string st;
    encode(st);
    
    if(status.count(st)) {
        //
        cout << "Draw: " << times << endl;
        return false;
    } else {
        status.insert(st);
    }
    
    putCard();
    return true;
}


int main() {
    freopen("input.txt", "r", stdin);
    
    
    while(true) {
        //
        // start()
        start();
        
        nil = &(piles[0]);
        nil->init();
        nil->right = &(piles[1]);
        
        for(int i = 1; i <= CNT; i++) {
            int val = read();
            if(val == 0) return 0;
            
            // get pile
            hcards.push_back(val);
        }
        
        for(int i = 1; i <= 7; i++) {
            Pile& p = piles[i];
            p.init();
            
            // get_link and get_data
            p.left = &(piles[i-1]);
            if(i+1 <= 7) p.right = &(piles[i+1]);
            p.cards.push_back(hcards.front());
            hcards.pop_front();
        }
        
        Pilep last = &(piles[7]);
        link(last, nil);
        //debug(nil->right);
        
        // simulate()
        int t = 7;
        while(true) if(!simulate(t++)) break;
        
    }
}
