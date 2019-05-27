#include <iostream>
#include <cstring>
#include <map>
#include <cstdio>
#include <queue>

using namespace std;

const int maxt = 1000+10;

int main(){
    int kase = 0, t;
    while(scanf("%d",&t) == 1 && t){
        printf("Scenario #%d\n",++kase);

        map<int,int> team;
        for(int i = 0; i < t; i++){
            int n,x;
            scanf("%d",&n);
            while(n--){
                scanf("%d",&x);
                team[x] = i;
            }
        }

        //simulate
        queue<int> q, group[maxt];
        for(;;){
            int val;
            char cmd[10];
            scanf("%s",cmd);
            if(cmd[0] == 'S')
                break;
            else if(cmd[0] == 'E'){
                scanf("%d",&val);
                int t = team[val];
                if(group[t].empty())
                    q.push(t);
                group[t].push(val);
            } else if(cmd[0] == 'D'){
                int t = q.front();
                printf("%d\n",group[t].front());
                group[t].pop();

                if(group[t].empty())
                    q.pop();
            }
        }
        printf("\n");
    }
}