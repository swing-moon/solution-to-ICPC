//
//  main.cpp
//  Hospital-facilities
//
//  Created by zhangmin chen on 2018/8/23.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <map>
#include <cmath>
#include <sstream>

using namespace std;

const int maxn = 105;

struct Room {
    int beg, id;
    Room(int _beg, int _id) : beg(_beg), id(_id) {}
    bool operator< (const Room& r) const {
        if(beg != r.beg)    return r.beg < beg;
        return r.id < id;
    }
};

struct Patient {
    char name[105];
    int opT, bedT;
    int id, roomID, bedID;
    int opBeg, opEnd;
    int reBeg, reEnd;
};

int main() {
    int n, m, T, t1, t2, t3, k;
    while(~scanf("%d%d%d%d%d%d%d", &n, &m, &T, &t1, &t2, &t3, &k)) {
        // init:
        vector<Patient> patients(k);
        priority_queue<Room> pqRoom;
        vector<int> roomUsed(n+1, 0);
        for(int i = 1; i <= n; i++)
            pqRoom.push(Room(T*60, i));
        for(int i = 0; i < k; i++) {
            auto& cur(patients[i]);
            cin >> cur.name >> cur.opT >> cur.bedT;
            cur.id = i+1;
            
            //find suitable operating room
            // calculate t2 as lagging time (after a patient is operated)
            Room u = pqRoom.top();  pqRoom.pop();
            cur.opBeg = u.beg;  cur.opEnd = cur.opBeg + cur.opT;
            cur.reBeg = cur.opEnd + t1; cur.reEnd = cur.reBeg + cur.bedT;
            
            cur.roomID = u.id;  roomUsed[u.id] += cur.opT;
            pqRoom.push(Room(cur.opEnd+t2, u.id));
        }
        sort(patients.begin(), patients.end(), [](Patient& a, Patient& b)->bool { if(a.opEnd != b.opEnd)    return a.opEnd < b.opEnd;   return a.roomID < b.roomID; });
        
        int tEnd = 0;
        vector<int> reRoomT(m+1, T*60);
        vector<int> bedUsed(m+1, 0);
        //find the recovery room!
        for(int i = 0; i < k; i++) {
            auto& cur(patients[i]);
            int j;
            for(j = 1; j <= m; j++) {
                if(reRoomT[j] <= cur.opEnd)
                    //notice: patient will not wait! get into recovery room immediately!!!
                    break;
            }
            cur.bedID = j;  reRoomT[j] = cur.reEnd + t3;
            // I made a bug , it needs cur.reEnd
            bedUsed[j] += cur.bedT;
            tEnd = max(tEnd, cur.reEnd);
        }
        sort(patients.begin(), patients.end(), [](Patient& a, Patient& b)->bool { return a.id < b.id;} );
        
        puts(" Patient          Operating Room          Recovery Room");
        puts(" #  Name     Room#  Begin   End      Bed#  Begin    End");
        puts(" ------------------------------------------------------");
        
        for(int i = 0; i < k; i++) {
            auto& cur(patients[i]);
            printf("%2d  %-9s ", cur.id, cur.name);
            printf("%2d  %3d:%02d  %3d:%02d     ", cur.roomID, cur.opBeg/60, cur.opBeg%60, cur.opEnd/60, cur.opEnd%60);
            printf("%2d  %3d:%02d  %3d:%02d\n", cur.bedID, cur.reBeg/60, cur.reBeg%60, cur.reEnd/60, cur.reEnd%60);
            
        }
        printf("\n");
        
        puts("Facility Utilization");
        puts("Type  # Minutes  % Used");
        puts("-------------------------");
        for(int i = 1; i <= n; i++)
            printf("Room %2d %7d %7.2f\n", i, roomUsed[i], roomUsed[i]*100.0 / (tEnd-T*60));
        for(int i = 1; i <= m; i++)
            printf("Bed  %2d %7d %7.2f\n", i, bedUsed[i], bedUsed[i]*100.0 / (tEnd-T*60));
        printf("\n");
    }
}
