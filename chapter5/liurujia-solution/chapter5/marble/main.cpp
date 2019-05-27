#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 10000;

int main(){
    int A[maxn];
    int n,q,kase = 0;
    int x;

    while(scanf("%d%d",&n,&q) == 2 && n){
        printf("CASE# %d:\n",++kase);

        for(int i = 0; i < n; i++){
            scanf("%d",&A[i]);
        }
        sort(A,A+n);

        while(q--){
            scanf("%d",&x);
            int p = lower_bound(A,A+n,x) - A;
            if(A[p] == x)
                printf("%d found at %d\n",x,p+1);
            else
                printf("%d not found\n",x);
        }
    }

}