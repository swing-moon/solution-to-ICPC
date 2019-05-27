#include <cstring>
#include <cstdio>

using namespace std;
const int maxn = 100;

int T, n, G[maxn][maxn], ideg[maxn], odeg[maxn];
int vis[maxn];

void dfs(int u) {
    vis[u] = 1;
    for(int v = 0; v < 26; v++) {
        if(G[u][v] && !vis[v])
            dfs(v);
    }
}

int main() {
    char s[2000];
    scanf("%d", &T);

    while(T--) {
        memset(vis, 1, sizeof(vis));
        memset(G, 0, sizeof(G));
        memset(ideg, 0, sizeof(ideg));
        memset(odeg, 0, sizeof(odeg));

        scanf("%d", &n);

        for(int i = 0; i < n; i++) {
            scanf("%s", s);
            int len = strlen(s);

            int beg = s[0] - 'a';
            int fin = s[len-1] - 'a';

            G[beg][fin] = 1;
            vis[beg] = vis[fin] = 0;
            odeg[beg]++;    ideg[fin]++;
        }

        int flag = 0;
        int root = 0, cnt_b = 0, cnt_f = 0, cnt = 0;

        for(int i = 0; i < 26; i++) {
            if(odeg[i] == ideg[i])
                continue;

            if(odeg[i] == ideg[i]+1) {
                cnt_b++;
                root = i;
            } else if (ideg[i] == odeg[i]+1) {
                cnt_f++;
            } else {
                cnt++;
            }
        }

        if(cnt > 0) {
            printf("The door cannot be opened.\n");
            continue;
        }

        if(cnt_b == 1 && cnt_f == 1 || cnt_b == 0 && cnt_f == 0)
            flag = 1;
        else
            flag = 0;

        dfs(root);
        for(int i = 0; i < 26; i++) {
            if(!vis[i])  flag = 0;
        }

        if(flag)    printf("Ordering is possible.\n");
        else    printf("The door cannot be opened.\n");
    }
}