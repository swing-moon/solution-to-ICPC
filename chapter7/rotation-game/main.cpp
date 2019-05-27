#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

/*
 *       00    01
 *       02    03
 * 04 05 06 07 08 09 10
 *       11    12
 * 13 14 15 16 17 18 19
 *       20    21
 *       22    23
 */

int line[8][7] = {
        // get id
        { 0, 2, 6, 11, 15, 20, 22},
        { 1, 3, 8, 12, 17, 21, 23},
        { 10, 9, 8, 7, 6, 5, 4},
        {19, 18, 17, 16, 15, 14,13},
};
const int rev[8] = {5, 4, 7, 6, 1, 0, 3, 2};
// if line > 3, for example line = 5, means move F
// means we need to reverse rev[5] = 0 --> move A

void rev_line() {
    for(int i = 4; i < 8; i++) {
        for(int j = 0; j < 7; j++) {
            line[i][j] = line[rev[i]][6-j];
        }
    }
}

int a[24];
char res[2000];

const int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

inline void move(int i) {
    // now line[i][j]  -> operate a[line[i][j]]
    int tmp = a[line[i][0]];
    for(int j = 0; j < 6; j++) {
        a[line[i][j]] = a[line[i][j+1]];
    }
    a[line[i][6]] = tmp;
}
// move(0)-> move A
// move(1)-> move B

bool final() {
    for(int i = 0; i < 8; i++) {
        if(a[center[i]] != a[center[0]])
            return false;
    }
    return true;
}

int cnt_diff(int target) {
    int ans = 0;
    for(int i = 0; i < 8; i++) {
        if(a[center[i]] != target) ans++;
    }
    return ans;
}

inline int h() {
    return min(min(cnt_diff(1), cnt_diff(2)), cnt_diff(3));
}

bool dfs(int d, int maxd) {
    if(final()) {
        res[d] = '\0';
        printf("%s\n", res);
        return true;
    }

    if(d + h() > maxd) return false;
    for(int i = 0; i < 8; i++) {
        res[d] = 'A' + i;
        move(i);
        if( dfs(d+1, maxd) ) return true;
        move(rev[i]);
    }
    return false;
}

int main() {
    rev_line();

    while(scanf("%d", &a[0]) == 1 && a[0]) {
        for(int i = 1; i < 24; i++) scanf("%d", &a[i]);
        for(int i = 0; i < 24; i++) if(!a[i]) return 0;

        if(final())
            printf("No moves needed\n");
        else {
            // IDA* algorithm
            for(int maxd = 1; ; maxd++) {
                if(dfs(0, maxd)) break;
            }
        }
        printf("%d\n", a[6]);
    }
    return 0;
}
