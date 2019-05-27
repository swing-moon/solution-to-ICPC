#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main(){
    int n,m;
    while(scanf("%d%d",&n,&m) == 2){
        double ans = 0.0;

        for(int i = 0; i < n; i++){
            double pos = (double) i / n * (n+m);
            ans += fabs(pos-floor(pos+0.5)) / (n+m);
        }

        printf("%.4lf\n",ans*10000);
    }
}