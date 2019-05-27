#include <iostream>
#include <cstring>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <sstream>

using namespace std;
const int maxn = 20000 + 10;
char str[100];

int pa[maxn], r[maxn];
int n, m;

void init() {
    for(int i = 0; i <= n; i++) {
        pa[i] = i;
        r[i] = 0;
    }
}

int main() {
    int kase = 1;
    while(scanf("%d%d", &n, &m) == 2 && (n+m)) {
        //
        printf("Case %d:\n", kase++);
        init();

        while(m--) {
            scanf("%s", str);
            if(str[0] == 'I') {
                //
                fflush(stdin);
                cin.getline(str, 100);
                // cout << str << endl;
                /*
                int a, b;
                stringstream ss(str);
                ss >> a >> b;
                printf("a: %d, b: %d\n", a, b);
                */


            }

            if(str[0] == 'Q') {
                //
            }
        }
    }
}