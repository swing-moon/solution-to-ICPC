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
#define lowbit(i) (i & (-i))

const int maxn = 15 + 1;
const int MOD = 16;
const int maxk = 225 + 1;
int N, M, K;
int A[maxn][maxn];

int f[maxn][maxk][maxn][maxn][2][2];
int pre[maxn][maxk][maxn][maxn][2][2];

int code(int l, int r, int dl, int dr) {
    return (l << 12) + (r << 8) + (dl << 4) + dr;
}

void decode(const int val, int& l, int& r, int& dr, int& dl) {
    l = (val >> 12) % MOD;
    r = (val >> 8) % MOD;
    dr = (val >> 4) % MOD;
    dl = (val) % MOD;
}


void initDP() {
    Set(f, 0);
    Set(pre, 0);
}

int dp(int& ans, int& fi) {
    initDP();

    _rep(i, 1, N) _rep(k, 1, K) _rep(l, 1, M) _rep(r, 1, M) {
                    if(k < (r - l + 1)) continue;

                    // (spand, spand)
                    int& _f1 = f[i][k][l][r][1][0];
                    int& _pre1 = pre[i][k][l][r][1][0];

                    int maxv1 = 0;
                    _rep(p, l, r) _rep(q, p, r) {
                            const int last = f[i - 1][k - (r - l + 1)][p][q][1][0];
                            if(maxv1 < last) {
                                maxv1 = last;
                                //_pre1 = {i - 1, k - (r - l + 1), p, q, 1, 0};
                                //debug(_pre1.k);
                                //_pre1 = code(p, q, 1, 0);
                                _pre1 = (p << 12) + (q << 8) + (1 << 4) + 0;
                            }
                        }
                    _rep(j, l, r) maxv1 += A[i][j];
                    _f1 = maxv1;

                    // (spand, shrink)
                    int& _f2 = f[i][k][l][r][1][1];
                    int& _pre2 = pre[i][k][l][r][1][1];

                    int maxv2 = 0;
                    _rep(p, l, r) _rep(q, r, M) _for(dr, 0, 2) {
                                const int last = f[i - 1][k - (r - l + 1)][p][q][1][dr];
                                if(maxv2 < last) {
                                    maxv2 = last;
                                    //_pre2 = code(p, q, 1, dr);
                                    //debug(_pre2.k);
                                    _pre2 = (p << 12) + (q << 8) + (1 << 4) + dr;
                                }
                            }
                    _rep(j, l, r) maxv2 += A[i][j];
                    _f2 = maxv2;

                    // (shrink, spand)
                    int& _f3 = f[i][k][l][r][0][0];
                    int& _pre3 = pre[i][k][l][r][0][0];

                    int maxv3 = 0;
                    _rep(p, 1, l) _rep(q, l, r) _for(dl, 0, 2) {
                                const int last = f[i - 1][k - (r - l + 1)][p][q][dl][0];
                                if(maxv3 < last) {
                                    maxv3 = last;
                                    //_pre3 = code(p, q, dl, 0);
                                    //debug(_pre3.k);
                                    _pre3 = (p << 12) + (q << 8) + (dl << 4) + 0;
                                }
                            }
                    _rep(j, l, r) maxv3 += A[i][j];
                    _f3 = maxv3;

                    // (shrink, shrink)
                    int& _f4 = f[i][k][l][r][0][1];
                    int& _pre4 = pre[i][k][l][r][0][1];

                    int maxv4 = 0;
                    _rep(p, 1, l) _rep(q, r, M) _for(dl, 0, 2) _for(dr, 0, 2) {
                                    const int last = f[i - 1][k - (r - l + 1)][p][q][dl][dr];
                                    if(maxv4 < last) {
                                        maxv4 = last;
                                        //_pre4 = code(p, q, dl, dr);
                                        //debug(_pre4.k);
                                        _pre4 = (p << 12) + (q << 8) + (dl << 4) + dr;
                                    }
                                }
                    _rep(j, l, r) maxv4 += A[i][j];
                    _f4 = maxv4;
                }

    // then get ret;
    int ret = 0;
    _rep(i, 1, N) _rep(l, 1, M) _rep(r, l, M) _for(dl, 0, 2) _for(dr, 0, 2) {
                        if(ret < f[i][K][l][r][dl][dr]) {
                            ret = f[i][K][l][r][dl][dr];
                            //ans = {i, K, l, r, dl, dr};
                            // ans = code(l, r, dl, dr);
                            ans = (l << 12) + (r << 8) + (dl << 4) + dr;
                            fi = i;
                        }
                    }

    return ret;
}

void printAns(int ans, int row, int K) {
    if(row == 0 || K <= 0) return;
    int al, ar, adl, adr;
    //decode(ans, al, ar, adl, adr);
    al = (ans >> 12) % MOD;
    ar = (ans >> 8) % MOD;
    adl = (ans >> 4) % MOD;
    adr = (ans) % MOD;

    _rep(i, al, ar) printf("%d %d\n", row, i);

    printAns(pre[row][K][al][ar][adl][adr], row - 1, K - (ar - al + 1));
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d%d", &N, &M, &K);

    _rep(i, 1, N) _rep(j, 1, M) scanf("%d", &A[i][j]);

    // then dp

    int ans, ai;
    printf("Oil : %d\n", dp(ans, ai));

    printAns(ans, ai, K);
}