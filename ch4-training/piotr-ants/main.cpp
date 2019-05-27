#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxn = 10000 + 5;

typedef struct Ants{
    int id;
    int pos;
    int dir;

    Ants(int id = 0, int pos =0, int dir = 0):id(id),pos(pos),dir(dir){}

    bool operator< (const Ants& A) const{
        return pos < A.pos;
    }
}ants;

ants before[maxn], after[maxn];

const char dirName[][10] = {"L","Turning","R"};
int probe[maxn];

void getval(){
    int L, T, n;
    scanf("%d%d%d",&L,&T,&n);

    for(int i = 0; i < n; i++){
        int p;
        char dir;
        cin >> p >> dir;

        int d = (dir == 'R' ? 1 : -1);

        before[i] = ants(i,p,d);
        after[i] = ants(0,p+T*d,d);
    }

    sort(before,before+n);
    for(int i = 0; i < n; i++){
        probe[before[i].id] = i;
    }

    sort(after,after+n);
    for(int i = 0; i < n-1; i++){
        if(after[i].pos == after[i+1].pos)
            after[i].dir = after[i+1].dir = 0;
    }

    for(int i = 0; i < n; i++){
        int cur = probe[i];
        //probe --> find before

        if(after[cur].pos < 0 || after[cur].pos > L){
            printf("Fell off\n");
        }
        else
            printf("%d %s\n",after[cur].pos,dirName[after[cur].dir+1]);
    }
}

int main(){
    int kase;
    scanf("%d",&kase);

    int cnt = 0;

    while(kase--){
//        int cnt = 0;
        printf("Case #%d:\n",++cnt);
        memset(before,0, sizeof(before));
        memset(after,0, sizeof(after));
        memset(probe,0, sizeof(probe));

        getval();
        printf("\n");
    }
}