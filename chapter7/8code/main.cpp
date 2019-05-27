//  main.cpp
//  8code
//
//  Created by zhangmin chen on 2018/9/27.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <set>

using namespace std;

typedef int State[9];
const int MAXSTATE = 1000000;
State st[MAXSTATE], goal;
//State& s --> s[0...8]
// goal[0...8]

int dist[MAXSTATE];

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};


//we build hash table
const int HASHSIZE = 1000003;
int head[HASHSIZE], Next[MAXSTATE];
void init_lookup_table() { memset(head, 0, sizeof(head)); }

//we build hash map:
int Hash(State& s) {
    int v = 0;
    for(int i = 0; i < 9; i++) v = v * 10 + s[i];

    return v % HASHSIZE;
}

//build hash link
int try_to_insert(int s) {
    //try to insert st[s]
    int h = Hash(st[s]);

    int u = head[h];
    while(u) {
        //try to found!
        if(memcmp(st[u], st[s], sizeof(st[s])) == 0) return 0;
        u = Next[u];
    }

    Next[s] = head[h];
    head[h] = s;
    // I made a bug here
    // I wrote Next[s] = head[u], it's wrong
    // in fact, u = head[h]

    return 1;
}

int bfs() {
    init_lookup_table();
    int front = 1, rear = 2;
    while(front < rear) {
        State& s = st[front];
        if(memcmp(goal, s, sizeof(s)) == 0) return front;

        //get next state:
        int z;
        for(z = 0; z < 9; z++) if(!s[z]) break;
        int x = z / 3, y = z % 3;

        for(int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            int nz = nx * 3 + ny;

            if(nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                State& t = st[rear];
                // t[0...9]
                memcpy(&t, &s, sizeof(s));

                t[nz] = s[z]; //s[z] == 0
                t[z] = s[nz]; // s[nz] = value
                dist[rear] = dist[front] + 1;

                if(try_to_insert(rear)) rear++;
                // cut stretch
            }
        }

        front++;
    }
    return 0;
}

int main() {
    for(int i = 0; i < 9; i++)
        scanf("%d", &st[1][i]);
    // we don't use id = 0, because 0 is regarded as non-exist
    for(int i = 0; i < 9; i++)
        scanf("%d", &goal[i]);

    int ans = bfs();
    if(ans > 0) printf("%d\n", dist[ans]);
    else printf("-1\n");

    return 0;
}