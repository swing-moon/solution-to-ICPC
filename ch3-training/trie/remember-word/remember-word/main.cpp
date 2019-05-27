//
//  main.cpp
//  remember-word
//
//  Created by zhangmin chen on 2018/8/20.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//


#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>

using namespace std;

const int maxnode = 4000 * 100 + 10;
const int sigma_size = 26;

struct Trie {
    int ch[maxnode][sigma_size];
    //ch means word id is maxnode, walk in direction of sigam_size
    
    int val[maxnode];
    
    int tot;
    //tot is the node id; we get No.tot node!
    
    void clear() { tot = 1; memset(ch[0], 0, sizeof(ch[0])); }
    int idx(char c) { return c - 'a'; }
    
    //insert
    void insert(const char* s, int v){
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++){
            int c = idx(s[i]);
            
            if(!ch[u][c]){
                memset(ch[tot], 0, sizeof(ch[tot]));
                //important! ch[tot] not! ch[u]
                // ch[tot] means current node id is tot
                
                val[tot] = 0;
                ch[u][c] = tot++;
            }
            
            u = ch[u][c];
            //means id from 0 to tot
        }
        val[u] = v;
        // last string takes the message val!
        // only last alpha gets the value! else alpha takes the value 0!!!
    }
    
    void check_prefix(const char* s, int len, vector<int>& ans) {
        int u = 0;
        for(int i = 0; i < len; i++) {
            if(s[i] == '\0') break;
            int c = idx(s[i]);
            
            if(!ch[u][c])   break;
            u = ch[u][c];
            if(val[u] != 0) //means the last alpha of the string
                ans.push_back(val[u]);
        }
    }
};

const int maxl = 300000 + 10;
const int maxw = 4000 + 10;
const int maxwl = 100 + 10;
const int MOD = 20071027;

int d[maxl];    char text[maxl];
int len[maxw];  char word[maxwl];
int S;
Trie trie;

int main(){
    int kase = 1;
    while(scanf("%s%d", text, &S) == 2){
        trie.clear();
        for(int i = 1; i <= S; i++){
            scanf("%s",word);
            len[i] = strlen(word);
            trie.insert(word, i);
        }
        
        memset(d, 0, sizeof(d));
        int L = strlen(text);
        d[L] = 1;
        
        for(int i = L-1; i >= 0; i--){
            vector<int> res;
            trie.check_prefix(text+i, L-i, res);
            for(int j = 0; j < res.size(); j++) {
                d[i] = (d[i] + d[i + len[res[j]]] ) % MOD;
            }
        }
        
        printf("Case %d: %d\n", kase++, d[0]);
    }
}
