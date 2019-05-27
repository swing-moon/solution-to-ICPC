#include <iostream>
#include <cstdio>
#include <string.h>

using namespace std;

const int MAXN = 16;

int vexp[MAXN][MAXN],hexp[MAXN][MAXN];
int hstart[MAXN][MAXN], vstart[MAXN][MAXN];
int square[MAXN];

int min(int a, int b)
{
    return a < b ? a : b;
}

void getdata(int& kase)
{
    while(kase--)
    {
        char type;
        int x,y;

        cin >> type >> x >> y;

        if(type == 'H')
            hstart[x][y] = 1;
        if(type == 'V')
            vstart[y][x] = 1;
    }
}

void stretch(int n)
{
    for(int i = n; i >= 1; i--){
        for(int j = n; j >= 1; j--){
            if(hstart[i][j]){
                hexp[i][j] = hexp[i][j+1] + 1;
            }
            if(vstart[i][j]){
                vexp[i][j] = vexp[i+1][j] + 1;
            }
        }
    }

    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            int mins = min(hexp[i][j],vexp[i][j]);

            for(int len = 1; len <= mins; len++){
                if(hexp[i+len][j] >= len && vexp[i][j+len] >= len){
                    square[len]++;
                }
            }
        }
    }
}

int main()
{
    int n;
    for(int t = 1; scanf("%d",&n)==1; t++)
    {
        if(t > 1)
            printf("\n**********************************\n\n");
        memset(vexp,0,sizeof(vexp));
        memset(hexp,0,sizeof(hexp));
        memset(hstart,0,sizeof(hstart));
        memset(vstart,0,sizeof(vstart));
        memset(square,0, sizeof(square));

        int kase;
        scanf("%d",&kase);
        getdata(kase);

        stretch(n);

//        for(int i = 0; i <= n; i++){
//            for(int j = 0; j <= n; j++)
//                cout << hexp[i][j] << " ";
//            cout << endl;
//        }
//        for(int i = 0; i <= n; i++){
//            for(int j = 0; j <= n; j++)
//                cout << vexp[i][j] << " ";
//            cout << endl;
//        }

        printf("Problem #%d\n\n",t);
        bool flag = false;
        for(int i = 1; i <= n; i++){
            if(square[i]){
                flag = true;
                printf("%d square (s) of size %d\n",square[i],i);
            }
        }
        if(!flag)
            printf("No completed squares can be found.\n");
    }
}