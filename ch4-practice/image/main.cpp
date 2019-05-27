#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;

#define REP(i,n)    for(int i = 0; i < (n); i++)

const int maxn = 10;
int n;
char pos[maxn][maxn][maxn];
char view[maxn][maxn][maxn];


char read_char(){
    char ch;
    for(;;){
        ch = getchar();
        if( (ch >= 'A' && ch <= 'Z') || ch == '.' )
            return ch;
    }
}

void getxyz(int k, int i, int j, int depth, int& x, int& y, int& z){
    if(k == 0){
        x = depth; y = j; z = i;
    }
    if(k == 1){
        x = n-1-j; y = depth; z = i;
    }
    if(k == 2){
        x = n-1-depth; y = n-1-j; z = i;
    }
    if(k == 3){
        x = j; y = n-1-depth; z = i;
    }
    if(k == 4){
        x = n-1-i; y = j; z = depth;
    }
    if(k == 5){
        x = i; y = j; z = n-1-depth;
    }
}

void init(int n){
    REP(i,n) REP(k,6) REP(j,n){
        view[k][i][j] = read_char();
    }
    //k视图
    REP(i,n) REP(j,n) REP(l,n){
        pos[i][j][l] = '#';
    }
}

int cntempty(){
    int ans = 0;
    REP(i,n) REP(j,n) REP(k,n){
        if(pos[i][j][k] != '.')
            ans++;
    }
    return ans;
}

int cal() {
    REP(k,6) REP(i,n) REP(j,n){
        if(view[k][i][j] == '.'){
            REP(dep,n){
                int x,y,z;
                getxyz(k,i,j,dep,x,y,z);
                pos[x][y][z] = '.';
            }
        }
    }
    // finished clean position
    //
    //循环一层一层删除，到最后不能删除为止
    //每次删除一层，就得到一个新的立方体
    //新的立方体作为start，继续执行删除，直到不能删除为止

    for(;;){
        bool finished = true;
        REP(k,6) REP(i,n) REP(j,n){
            if(view[k][i][j] != '.'){
                REP(dep,n){
                    //一层一层检查，一层一层剥开你的心
                    int x,y,z;
                    getxyz(k,i,j,dep,x,y,z);

                    if(pos[x][y][z] == '.')
                        continue;
                    if(pos[x][y][z] == '#'){
                        pos[x][y][z] = view[k][i][j];
                        break;
                    }
                    if(pos[x][y][z] == view[k][i][j])
                        break;

                    pos[x][y][z] = '.';
                    finished = false;

                    //所有视图删除完之后，作为一个新的立方体
                    //重新进入循环
                    //删除！一直删到不能删为止
                }
            }
        }

        if(finished)
            break;
    }
    return cntempty();

}



int main(){
    while(scanf("%d",&n) == 1  && n){
        memset(pos,0, sizeof(pos));
        memset(view,0, sizeof(view));

        init(n);
        int ans = cal();
        printf("Maximum weight: %d gram(s)\n",ans);
    }
}