#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;
const int maxn = 20;
int data[maxn][maxn], buffer[maxn][maxn];
int n;

int check(int val){
    memset(buffer,0, sizeof(buffer));

    for(int c = 0; c < n; c++){
        if(val & (1<<c))
            buffer[0][c] = 1;
        //enumerate
        else{
            // the number in high bits is 0
            if(data[0][c] == 1)
                // not 0，contradict with default
                // enumerate default --> binary bits
                return INF;
        }
    }

    for(int r = 1; r < n; r++){
        for(int c = 0; c < n; c++){
            int sum = 0;
            if(r > 1) sum += buffer[r-2][c];
            if(c > 0) sum += buffer[r-1][c-1];
            if(c+1 < n) sum += buffer[r-1][c+1];

            buffer[r][c] = sum % 2;

            if(data[r][c] == 1 && buffer[r][c] == 0)
                return INF;
        }
    }

    int cnt = 0;
    for(int r = 0; r < n; r++){
        for(int c = 0; c < n; c++){
            if(data[r][c] != buffer[r][c])
                cnt++;
        }
    }
    return cnt;
}

int main(){
    int kase;
    int k = 0;
    scanf("%d",&kase);
    while(kase--){
        scanf("%d",&n);

        for(int r = 0; r < n; r++){
            for(int c = 0; c < n; c++)
                scanf("%d",&data[r][c]);
        }

        int ans = INF;
        for(int v = 0; v < (1 << n); v++){
            ans = min(ans,check(v));
        }

        if(ans == INF)  ans = -1;

        printf("Case %d: %d\n",++k,ans);
    }
}