#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int posture[24][6] = {
        {2, 1, 5, 0, 4, 3},
        {2, 0, 1, 4, 5, 3},
        {2, 4, 0, 5, 1, 3},
        {2, 5, 4, 1, 0, 3},
        {4, 2, 5, 0, 3, 1},
        {5, 2, 1, 4, 3, 0},
        {1, 2, 0, 5, 3, 4},
        {0, 2, 4, 1, 3, 5},
        {0, 1, 2, 3, 4, 5},
        {4, 0, 2, 3, 5, 1},
        {5, 4, 2, 3, 1, 0},
        {1, 5, 2, 3, 0, 4},
        {5, 1, 3, 2, 4, 0},
        {1, 0, 3, 2, 5, 4},
        {0, 4, 3, 2, 1, 5},
        {4, 5, 3, 2, 0, 1},
        {1, 3, 5, 0, 2, 4},
        {0, 3, 1, 4, 2, 5},
        {4, 3, 0, 5, 2, 1},
        {5, 3, 4, 1, 2, 0},
        {3, 4, 5, 0, 1, 2},
        {3, 5, 1, 4, 0, 2},
        {3, 1, 0, 5, 4, 2},
        {3, 0, 4, 1, 5, 2},
};

const int maxn = 4;
int cubes[maxn][6], ans;
int n;
void check();


vector<string> cnames;
int getid(const char* name){
    string cur(name);
    int n = cnames.size();
    for(int i = 0; i < n; i++){
        if(cnames[i] == cur)
            return i;
    }
    cnames.push_back(cur);
    return n;
    //返回的是颜色编号id-1，即vector数组下标
    //有一个元素的时候，n=0，恰好cnames[0] = 这个元素
    //n = 1, cnames[0] cnames[1]这两个元素 --> cnames[1]=name
}
//找到颜色不一样的
//如果颜色一样，返回第一次出现该颜色的id
//cnames中的各个颜色都不一样！
//该函数的作用相当于一个<set>


int rota[maxn], color[maxn][6];


void enumdfs(int curid){
    if(curid == n)
        check();
    else{
        for(int i = 0; i < 24; i++){
            rota[curid] = i;
            enumdfs(curid+1);
        }
    }
}

//实际上执行了24^3次
//按不同的姿态，分别染色，染入给定的颜色cubes[i][j]
void check(){
    memset(color,0, sizeof(color));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 6; j++){
            int p_face = posture[rota[i]][j];
            color[i][p_face] = cubes[i][j];
            //涂色
        }
    }
    //finished painting

    //以面作为标准
    int tot = 0;
    for(int k = 0; k < 6; k++){
        int cnt[maxn*6];
        memset(cnt,0, sizeof(cnt));

        int maxface = 0;
        //color[i][k]
        for(int i = 0; i < n; i++){
            maxface = max(maxface, ++cnt[color[i][k]]);
        }

        tot += n-maxface;
    }
    ans = min(ans,tot);
}

int main(){
    while(scanf("%d",&n) == 1 && n){
        cnames.clear();

        for(int i = 0; i < n; i++){
            for(int j = 0; j < 6; j++){
                char name[30];
                scanf("%s",name);
                cubes[i][j] = getid(name);
            }
        }

        ans = n*6;
        rota[0] = 0;
        enumdfs(1);
        printf("%d\n",ans);
    }
}