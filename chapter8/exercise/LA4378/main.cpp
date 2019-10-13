#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <bitset>
#include <assert.h>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;



#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _forS(i, l, r) for(set<int>::iterator i = (l); i != (r); i++)
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)

const int maxn = 100000 + 10;

class Data {
public:
    int val, id;
    Data(int v = 0, int i = 0) : val(v), id(i) {}
};

bool cmp(const Data& lhs, const Data& rhs) {
    return lhs.val > rhs.val;
}

Data data[maxn];
int ans[maxn];
int n;

void init() {
    Set(ans, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (~scanf("%d", &n)) {
        init();
        llong sum = 0;
        _for(i, 0, n) {
            scanf("%d", &data[i].val);
            data[i].id = i;
            sum += data[i].val;
        }

        if(sum % 2) {
            printf("No\n");
            continue;
        }
        else sum /= 2;

        sort(data, data + n, cmp);
        _for(i, 0, n) {
            if(data[i].val <= sum) {
                sum -= data[i].val;
                ans[data[i].id] = 1;
            }
            else ans[data[i].id] = -1;
        }

        printf("Yes\n");
        _for(i, 0, n - 1) printf("%d ", ans[i]);
        printf("%d\n", ans[n - 1]);
    }
}