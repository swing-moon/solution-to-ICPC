//
//  main.cpp
//  la5059
//
//  Created by zhangmin chen on 2019/2/26.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

/* test SG
#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
const int maxn = 100;
int SG[maxn], vis[maxn];

int main() {
    SG[1] = 0;
    for(int i = 2; i <= 30; i++) {
        memset(vis, 0, sizeof(vis));
        for(int j = 1; j*2 <= i; j++) vis[SG[i-j]] = 1;
        for(int j = 0; ; j++) if(!vis[j]) {
            SG[i] = j;
            break;
        }
    }
    for(int i = 2; i <= 30; i++) printf("%-2d ", SG[i]);
    printf("\n");
    for(int i = 2; i <= 30; i++) if(i % 2 == 0) printf("%-2d    ", SG[i]);
    printf("\n");
    for(int i = 2; i <= 30; i++) if(i % 2 == 0) printf("%-2d    ", i/2);
    printf("\n");
    for(int i = 2; i <= 30; i++) if(i % 2) printf("   %-2d ", SG[i]);
    printf("\n");
    for(int i = 2; i <= 30; i++) if(i % 2) printf("   %-2d ", SG[i/2]);
}
*/

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
typedef long long llong;

llong SG(llong x) {
    return x%2 == 0 ? x/2 : SG(x/2);
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    while(T--) {
        int n;
        cin >> n;
        llong a, v = 0;
        for(int i = 0; i < n; i++) {
            cin >> a;
            v ^= SG(a);
        }
        if(v) cout << "YES\n";
        else cout << "NO\n";
    }
}

