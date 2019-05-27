#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <queue>

using namespace std;
int readint(){
    int x;  scanf("%d",&x); return x;
}
const int maxn = 130;
const int maxp = 10;
int priority[maxn],pcnt[maxp];
queue<int> q;
int n,m;

void init(){
    while(!q.empty())   q.pop();

    n = readint();  m = readint();
    fill_n(priority,maxn,0);
    fill_n(pcnt,maxp,0);

    for(int i = 0; i < n; i++){
        q.push(i);
        priority[i] = readint();
        pcnt[priority[i]]++;
    }
}

int main(){
    int kase;
    scanf("%d",&kase);

    while(kase--){
        init();

        int timer = 1;
        while(!q.empty()){
            int id = q.front();
            int p = priority[id];
            bool lower = false;

            for(int hp = maxp-1; hp > p; hp--){
                if(pcnt[hp] > 0){
                    lower = true;
                    break;
                }
            }

            q.pop();
            if(lower){
                q.push(id);
                continue;
            }

            if(id == m) break;

            pcnt[priority[id]]--;
            timer++;
        }
        printf("%d\n",timer);
    }
}