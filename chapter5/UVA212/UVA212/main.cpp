//
//  main.cpp
//  UVA212
//
//  Created by zhangmin chen on 2019/5/7.
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

class Room {
public:
    int beg, id;
    Room(int beg, int id) : beg(beg), id(id) {}
    
    bool operator < (const Room& rhs) const {
        if(beg != rhs.beg) return beg > rhs.beg;
        return id > rhs.id;
    }
};

// we use priority queue;
// room --> bed

class Patient {
public:
    char name[105];
    int opT, bedT;
    int id, roomID, bedID;
    int opS, opEnd;
    int bedS, bedEnd;
};

bool cmp(Patient& lhs, Patient& rhs) {
    if(lhs.opEnd != rhs.opEnd) return lhs.opEnd < rhs.opEnd;
    return lhs.roomID < rhs.roomID;
}

bool cmp2(Patient& lhs, Patient& rhs) {
    return lhs.id < rhs.id;
}

// n opRooms, m beds, H start hours
// t1 trans-time, t2 pre-opTime, t3 pre-bedTime
// k paitients

int main() {
    freopen("input.txt", "r", stdin);
    
    int n, m, H, t1, t2, t3, k;
    while(~ (scanf("%d%d%d%d%d%d%d", &n, &m, &H, &t1, &t2, &t3, &k)) ) {
        // init
        
        vector<Patient> pents(k);
        priority_queue<Room> rooms;
        vector<int> rUsed(n+1, 0);
        
        for(int i = 1; i <= n; i++) rooms.push(Room(H*60, i));
        // then we get all rooms
        
        for(int i = 0; i < k; i++) {
            Patient& p = pents[i];
            cin >> p.name >> p.opT >> p.bedT;
            p.id = i+1;
            
            // then we get each patient
            
            Room r = rooms.top(); rooms.pop();
            
            p.opS = r.beg; p.opEnd = p.opS + p.opT;
            p.bedS = p.opEnd + t1; p.bedEnd = p.bedS + p.bedT;
            
            p.roomID = r.id;
            rUsed[r.id] += p.opT;
            
            rooms.push(Room(p.opEnd + t2, r.id));
        }
        
        // we arrange op-Room for each patient
        
        sort(pents.begin(), pents.end(), cmp);
        
        // then arrange bed for each patient
        int END = 0;
        vector<int> bUsed(m+1, 0);
        vector<int> Beds(m+1, H*60);
        
        for(int i = 0; i < k; i++) {
            Patient& p = pents[i];
            int j;
            for(j = 1; j <= m; j++) {
                if(Beds[j] <= p.opEnd) break;
            }
            
            // &p: get into Beds[j];
            
            p.bedID =j;
            Beds[j] = p.bedEnd + t3;
            bUsed[j] += p.bedT;
            
            END = max(END, p.bedEnd);
        }
        
        
        // we arrange beds for each patient
        sort(pents.begin(), pents.end(), cmp2);
        
        puts(" Patient          Operating Room          Recovery Room");
        puts(" #  Name     Room#  Begin   End      Bed#  Begin    End");
        puts(" ------------------------------------------------------");
        
        for(int i = 0; i < k; i++) {
            const Patient& p = pents[i];
            printf("%2d  %-9s ", p.id, p.name);
            printf("%2d  %3d:%02d  %3d:%02d     ", p.roomID, p.opS/60, p.opS%60, p.opEnd/60, p.opEnd%60);
            printf("%2d  %3d:%02d  %3d:%02d\n", p.bedID, p.bedS/60, p.bedS%60, p.bedEnd/60, p.bedEnd%60);
        }
        printf("\n");
        
        puts("Facility Utilization");
        puts("Type  # Minutes  % Used");
        puts("-------------------------");
        
        for(int i = 1; i <= n; i++)
            printf("Room %2d %7d %7.2f\n", i, rUsed[i], rUsed[i] * 100.0 / (END - H*60));
        for(int i = 1; i <= m; i++)
            printf("Bed  %2d %7d %7.2f\n", i, bUsed[i], bUsed[i] * 100.0 / (END - H*60));
        
        printf("\n");
    }
}
