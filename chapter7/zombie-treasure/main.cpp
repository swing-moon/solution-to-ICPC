//
//  main.cpp
//  zombie-treasure
//
//  Created by zhangmin chen on 2018/10/12.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

// s2(1) means s2 sizes of treasure 1
// s1(2) means s1 sizes of treasure 2
// if s1(2) == s2(1) && s2(1)*v1 > s1(2)*v2
// treasure 2 at most s1-1, if not, we can change s1 to s2, because s1 == s2
// than we have greater value s2*v1

#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long llong;
const int inf = 65536;

int main() {
    int T;
    scanf("%d", &T);

    for(int kase = 1; kase <= T; kase++) {
        int n, s1, v1, s2, v2;
        scanf("%d%d%d%d%d", &n, &s1, &v1, &s2, &v2);

        // enumerate: let n/s2 < n/s1 --> s2 >= s1
        if(s1 > s2) {
            swap(s1, s2);
            swap(v1, v2);
        }

        llong ans = 0;
        // enumerate cnt number i

        if(n / s2 >= inf) {
            // both s1 and s2 are small
            for(llong i = 0; i <= s1; i++) {
                ans = max(ans, v2*i + (n - s2*i)/s1*v1);
                // treasure2 have cnt number i
            }

            for(llong i = 0; i <= s2; i++) {
                ans = max(ans, v1*i + (n - s1*i)/s2*v2);
            }
        } else {
            // s2 is large
            for(llong i = 0; s2*i <= n; i++) {
                ans = max(ans, v2*i + (n-s2*i)/s1*v1);
            }
        }

        printf("Case #%d: %lld\n", kase, ans);
    }
    return 0;
}