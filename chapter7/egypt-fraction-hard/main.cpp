#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>

using namespace std;

typedef long long llong;
const int maxn = 100 + 5;
const int maxv = 200000;

int a, b, maxd;
llong v[maxn], ans[maxn];
//maxn means depth = 0, 1 ... maxd
int k;
set<llong> mask;
const int inf = 0x3f3f3f3f;

llong gcd(llong a, llong b) {
    return b == 0 ? a : gcd(b, a%b);
}

inline int get_first(llong a, llong b) {
    return b/a+1;
}

bool better(int d) {
    for(int i = d; i >= 0; i--) {
        if(v[i] != ans[i]) {
            return ans[i] == -1 || v[i] < ans[i];
        }
    }
    return false;
}

bool dfs(int d, int from, llong aa, llong bb) {
    //cur depth = d, from means we search the value from 1/(from), until we found suitable value 1/k
    // aa/bb means value = 1/i + 1/(i+1)...
    // we search from 1/(i+1), 1/(i+2) ... until we found suitable value 1/k
    // v[d] = 1/i, v[d+1] = 1/(i+1) .... v[maxd] = 1/k (k > i)

    if(d == maxd) {
        //return? if any sub num is better?
        if(bb % aa) return false;
        if(mask.count(bb/aa)) return false;

        v[d] = bb/aa;
        if(better(d)) {
            memcpy(ans, v, sizeof(llong) * (d+1));
        }
        return true;
    }

    bool ok = false;
    from = max(from, get_first(aa, bb));
    for(int i = from; i < inf ; i++) {
        //cut stretch
        // from 1/i, 1/(i+1), 1/(i+2) ... 1/(k) we found suitable k
        if(bb * (maxd+1-d) <= aa * i) break;
        if(mask.count(i)) continue;

        v[d] = i;

        // get new aa, bb
        llong b2 = bb * i;
        llong a2 = aa * i - bb;
        llong g = gcd(a2, b2);

        if(dfs(d+1, i+1, a2/g, b2/g)) {
            // means current depth = d+1, we found from 1/(i+1)
            // until we found suitable value 1/k
            ok = true;
        }
    }
    return ok;
}



int main() {
    int kase = 0;
    int t;
    cin >> t;

    while(t--) {
        mask.clear();
        cin >> a >> b >> k;
        llong v;
        for(int i = 0; i < k; i++) {
            cin >> v;
            mask.insert(v);
        }

        int ok = 0;
        for(maxd = 1; maxd <= 100; maxd++) {
            memset(ans, -1, sizeof(ans));
            if(dfs(0, get_first(a, b), a, b)) {
                ok = 1;
                break;
            }
        }

        //judge ok:
        cout << "Case " << ++kase << ": ";
        if(ok) {
            cout << a << "/" << b << "=";
            for(int i = 0; i < maxd; i++) {
                cout << "1/" << ans[i] << "+";
            }
            cout << "1/" << ans[maxd] << "\n";
        } else cout << "No solution.\n";
    }
    return 0;
}