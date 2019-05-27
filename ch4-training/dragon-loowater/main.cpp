#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int maxn = 20000 + 5;
int dragon[maxn], knight[maxn];
// dragon[n]  knight[m]

int main(){
    int n,m;

    while( (scanf("%d%d",&n,&m)==2) && n && m){
        memset(knight,0,sizeof(knight));
        memset(dragon,0, sizeof(dragon));
        for(int i = 0; i < n; i++)  scanf("%d",&dragon[i]);
        for(int i = 0; i < m; i++)  scanf("%d",&knight[i]);

        sort(dragon,dragon+n);
        sort(knight,knight+m);

        int dcur = 0;
        int cost = 0;
        for(int i = 0; i < m; i++){
            if(knight[i] >= dragon[dcur]){
                cost += knight[i];
                dcur++;
                if(dcur == n)
                    break;
            }
        }
        if(dcur < n)
            printf("Loowater is doomed!\n");
        else
            printf("%d\n",cost);
    }
    return 0;
}