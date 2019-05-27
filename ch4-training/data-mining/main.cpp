#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <cmath>
#include <iomanip>
#include <climits>

using namespace std;

typedef long long LL;
#define INF LLONG_MAX;

LL f(LL x, int a, int b){
    return (x + (x<<a)) >> b;
}

int main(){
    LL n,sp,sq;
    while(scanf("%lld%lld%lld", &n,&sp,&sq) == 3){
        int a = 0, b = 0, cur_a = 0, cur_b = 0;
        LL k = LLONG_MAX;
        for(a = 0; a < 32; a++){
            for(b = 0; b < 32; b++){
                if(f(sp,a,b) < sq)
                    continue;

                LL cur = f(sp*(n-1) , a, b) + sq;
                if(cur < k){
                    k = cur;
                    cur_a = a;
                    cur_b = b;
                }
            }
        }
        printf("%lld %d %d\n",k,cur_a,cur_b);
    }
}