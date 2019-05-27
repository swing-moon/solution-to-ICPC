#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 1000000+10;
long long A[maxn], C[maxn], tot, M;

int main(){
    int n;
    while(scanf("%d",&n) == 1){
        tot = 0;
        for(int i = 0; i < n; i++){
            scanf("%d",&A[i]);
            tot += A[i];
        }

        M = tot / n;

        C[0] = 0;
        for(int i = 1; i < n; i++){
            C[i] = C[i-1]+A[i]-M;
        }

        sort(C,C+n);
        long long fin = C[n/2], ans = 0;
        for(int i = 0; i < n; i++){
            ans += abs(fin-C[i]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}