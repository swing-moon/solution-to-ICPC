//
//  main.cpp
//  strcmp
//
//  Created by zhangmin chen on 2018/8/20.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

const int maxnode = 4000 * 1000 + 20;
const int sigma_size = 26;

struct Trie {
    int head[maxnode];
    int next[maxnode];
    int sz;
    char ch[maxnode];
    int tot[maxnode];
    
    long long ans;
    
    void clear(){
        sz = 1;
        tot[0] = head[0] = next[0] = 0;
    }
    
    void insert(const char* s) {
        int n = strlen(s);
        int u = 0; tot[0]++;
        int v;
        
        for(int i = 0; i <= n; i++) {
            bool found = false;
            for(v = head[u]; v != 0; v = next[v]) {
                //get a bug! first time! I wrote v = head[0]!
                //In fact, v = head[u]
                if(ch[v] == s[i]) {
                    found = true;
                    break;
                }
            }
            
            if(!found) {
                v = sz++;
                ch[v] = s[i];
                tot[v] = 0;
                
                next[v] = head[u];
                head[u] = v;
                head[v] = 0;
            }
            
            u = v;
            tot[u]++;
        }
    }
    
    void dfs(int depth, int u) {
        if(head[u] == 0) {
            ans += tot[u] * (tot[u] - 1) * depth;
        } else {
            int sum = 0;
            for(int v = head[u]; v != 0; v = next[v])
                sum += tot[v] * (tot[u] - tot[v]);
            
            ans += sum / 2 * (depth * 2 + 1);
            
            for(int v = head[u]; v != 0; v = next[v])
                dfs(depth + 1, v);
            
        }
    }
    
    long long count(){
        ans = 0;
        dfs(0,0);
        return ans;
    }
};

const int maxl = 1000 + 10;
int N;
char word[maxl];
Trie trie;

int main() {
    int kase = 1;
    while(scanf("%d", &N) == 1 && N) {
        trie.clear();
        
        for(int i = 0; i < N; i++) {
            scanf("%s", word);
            trie.insert(word);
        }
        
        printf("Case %d: %lld\n", kase++, trie.count());
    }
}
