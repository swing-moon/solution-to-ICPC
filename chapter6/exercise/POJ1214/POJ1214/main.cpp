//
//  main.cpp
//  POJ1214
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

struct Card {
    //
    char suit, rank;
    Card(int s, int r) : suit(s), rank(r) {}
    
    bool operator == (const Card& rhs) const {
        return suit == rhs.suit || rank == rhs.rank;
    }
};

struct Pile {
    // Link-list
    stack<Card> cards;
    Pile *left, *right;
    
    void init() {
        while(!cards.empty()) cards.pop();
        left = right = nullptr;
    }
};
typedef Pile* Pilep;

void link(Pilep l, Pilep r) {
    if(l) l->right = r;
    if(r) r->left = l;
}


Pile piles[CNT+1];
Pilep nil;

// use Linklist to deal piles[CNT]

Pilep getleft3(Pilep cur) {
    for(int i = 0; i < 3; i++) {
        cur = cur->left;
        if(cur == nullptr) return nullptr;
    }
    return cur;
}

void solve() {
    Pilep from, to, cur;
    
    while(true) {
        from = to = nullptr;
        cur = nil->right;
        
        while(cur) {
            //
            Pilep l3 = getleft3(cur);
            if(l3 != nullptr && l3 != nil) {
                //
                if(l3->cards.top() == cur->cards.top()) {
                    from = cur; to = l3;
                    break;
                }
            }
            
            Pilep l1 = cur->left;
            if(l1 != nullptr && l1 != nil) {
                if(l1->cards.top() == cur->cards.top()) {
                    from = cur; to = l1;
                    break;
                }
            }
            
            cur = cur->right;
        }
        
        if(from == nullptr) break;
        to->cards.push(from->cards.top());
        from->cards.pop();
        
        if(from->cards.empty()) link(from->left, from->right);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    
    string str;
    nil = &(piles[0]);
    nil->init();
    nil->right = &(piles[1]);
    
    while(true) {
        for(int i = 1; i <= CNT; i++) {
            //
            if(cin >> str && str.size() == 2) {
                // get str, and card
                Pile& p = piles[i];
                p.init();
                
                p.left = &(piles[i-1]);
                if(i+1 <= CNT) p.right = &(piles[i+1]);
                
                p.cards.push(Card(str[0], str[1]));
                
            }
            else return 0;
        }
        
        // get data
        // then we solve
        
        solve();
        vector<int> ans;
        
        Pilep cur = nil->right;
        while(cur) {
            ans.push_back((int)cur->cards.size());
            cur = cur->right;
        }
        
        printf("%d", (int)ans.size());
        printf(" pile");
        if(ans.size() > 1) printf("s");
        printf(" remaining:");
        
        for(int i = 0; i < ans.size(); i++) {
            printf(" %d", ans[i]);
        }
        
        printf("\n");
    }
}
