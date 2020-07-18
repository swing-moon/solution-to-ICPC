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
typedef long long ll;
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
#define MPR(a, b) make_pair(a, b)

const int K = 2;
const int inf = 0x3f3f3f3f;

// == tree definition ==
class Node {
public:
    int point[K];
    Node *cld[2];
};

typedef Node* T;

T create(const int arr[]) {
    T cur = new Node();
    _for(i, 0, K) cur->point[i] = arr[i];
    cur->cld[0] = cur->cld[1] = NULL;

    return cur;
}
// == tree finished ==

// == insert function ==
T insertRec(T u, const int point[], int dep) {
    if(u == NULL) return create(point);

    int cd = dep % K;

    if(point[cd] < u->point[cd]) u->cld[0] = insertRec(u->cld[0], point, dep + 1);
    else u->cld[1] = insertRec(u->cld[1], point, dep + 1);

    return u;
}

T insert(T u, const int point[]) {
    return insertRec(u, point, 0);
}
// == insert finished ==

// == search rectangle ==
bool equalPoint(const int point1[], const int point2[]) {
    _for(i, 0, K) if(point1[i] != point2[i]) return false;
    return true;
}

bool searchRec(T u, const int point[], int dep) {
    if(u == NULL) return false;
    if(equalPoint(u->point, point)) return true;

    int cd = dep % K;

    if(point[cd] < u->point[cd]) return searchRec(u->cld[0], point, dep + 1);
    return searchRec(u->cld[1], point, dep + 1);
}

bool search(T u, const int point[]) {
    return searchRec(u, point, 0);
}
// == search finished ==

// == find min rec ==
T findMinRec(T u, int _cd, int dep) {
    if(u == NULL) return NULL;

    int cd = dep % K;

    if(cd == _cd) {
        if(u->cld[0] == NULL) return u;
        return findMinRec(u->cld[0], _cd, dep + 1);
    }

    T left = findMinRec(u->cld[0], _cd, dep + 1);
    T right = findMinRec(u->cld[1], _cd, dep + 1);
    T cur = left->point[_cd] < right->point[_cd] ? left : right;

    return cur->point[_cd] < u->point[_cd] ? cur : u;
}

T findMin(T u, int _cd) {
    return findMinRec(u, _cd, 0);
}
// == find finished ==

// == delete node ==
void copyPoint(int to[], const int point[]) {
    _for(i, 0, K) to[i] = point[i];
}

T delRec(T u, const int point[], int dep) {
    if(u == NULL) return NULL;

    int cd = dep % K;

    // it is the point to be deleted
    if(equalPoint(u->point, point)) {
        if(u->cld[1]) {
            T _min = findMin(u->cld[1], cd);
            copyPoint(u->point, _min->point);
            u->cld[1] = delRec(u->cld[1], _min->point, dep + 1);
        }

        else if(u->cld[0]) {
            T _min = findMin(u->cld[0], cd);
            copyPoint(u->point, _min->point);
            u->cld[1] = delRec(u->cld[0], _min->point, dep + 1);
        }
        else {
            // is leaf node
            delete u;
            return NULL;
        }
        return u;
    }

    if(point[cd] < u->point[cd]) u->cld[0] = delRec(u->cld[0], point, dep + 1);
    else u->cld[1] = delRec(u->cld[1], point, dep + 1);
    return u;
}

T del(T u, const int point[]) {
    return delRec(u, point, 0);
}
// == delete finished ==

int n;
int main() {
    T root = NULL;
    int points[][K] = {
            {3,6}, {17, 15}, {13, 15}, {6, 12},
            {9, 1}, {2, 7}, {10, 19}
    };

    n = sizeof(points) / sizeof(points[0]);

    _for(i, 0, n) root = insert(root, points[i]);


    int p1[] = {10, 19};
    search(root, p1) ? printf("Found\n") : printf("Not found\n");

    int p2[] = {12, 19};
    search(root, p2) ? printf("Found\n") : printf("Not found\n");

    int p3[] = {10, 19};
    int p4[] = {9, 1};
    del(root, p3);
    search(root, p3) ? printf("Found\n") : printf("Not found\n");
    search(root, p4) ? printf("Found\n") : printf("Not found\n");
}