#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
#include <string.h>

#define maxd 100
#define BIG 10000

using namespace std;

int sh[maxd][maxd], sh_buf[maxd][maxd], ans[maxd][maxd];
int row, col;
int begr, begc;
int change[maxd];

// int oldr,oldc;
// int newr,newc;

void init()
{
    for(int i = 1; i <= row; i++)
    {
        for(int j = 1; j <= col; j++)
            sh[i][j] = i*BIG+j;
    }
}

void movesh(char type,int fresh,int old)
{
    if(type == 'R')
    {
        for(int i = 1; i <= col; i++)
            sh[fresh][i] = sh_buf[old][i];
    }
    else
    {
        for(int i = 1; i <= row; i++)
            sh[i][fresh] = sh_buf[i][old];
    }
}
//算法处理一：用type=='R'，选择的方式，来把行变换和列变换统一起来

void del(char type)
{
    // memset(sh_buf,0,sizeof(sh_buf));
    //memset(change,0,sizeof(change));
    memcpy(sh_buf,sh,sizeof(sh));

    int cnt = 0;
    int way = (type == 'R' ? row : col);

    for(int i = 1; i <= way; i++)
    {
        if(change[i] == 0)
            movesh(type,++cnt,i);
    }
    if(type == 'R')
    {
        row = cnt;
        for(int i = row+1; i <= way; i++)
            for(int j = 1; j <= col; j++)
                sh[i][j] = 0;
    }
    else
    {
        col = cnt;
        for(int i = 1; i <= row; i++)
            for(int j = col+1; j <= way; j++)
                sh[i][j] = 0;
    }
}


void printsheet()
{
    for(int i = 0; i <= row+2; i++)
    {
        for(int j = 0; j <= col+2; j++)
            cout << sh[i][j] <<" ";
        cout << endl;
    }
}

void insert(char type)
{
    // memset(sh_buf,0,sizeof(sh_buf));
    memcpy(sh_buf,sh,sizeof(sh));

    int cnt = 0;
    int way = (type == 'R' ? row : col);
    for(int i = 1; i <= way; i++)
    {
        if(change[i] == 1)
            movesh(type,++cnt,0);
        movesh(type,++cnt,i);
        //这一步卡住了
    }
    if(type == 'R')
        row = cnt;
    else
        col = cnt;
}

// void reset()
// {
//     memcpy(sh_buf,sh,sizeof(sh));
//     for(int i = 1; i <= maxd; i++)
//     {
//         for(int j = 1; j <= maxd; j++)
//         {
//             if(i > row || j > col)
//                 sh_buf[i][j] = 0;
//         }
//     }
// }

int main()
{
    // cin >> row >> col;
    // // begr = row, begc = col;
    // init();
    // memset(change,0,sizeof(change));
    // printsheet();
    //
    // string cmd;
    // cin >> cmd;
    //
    // int op_row;
    // cin >> op_row;
    // change[op_row] = 1;
    // del(cmd[1]);
    // // reset();
    // printsheet();
    // memset(change,0,sizeof(change));
    // cmd.clear();
    //
    // cin >> cmd;
    // int op_col;
    // cin >> op_col;
    // change[op_col] = 1;
    // insert(cmd[1]);
    // // reset();
    // printsheet();
    // 操作数必须和原来的值保持一致
    int kase;
    char cmd[10];
    int sit = 0;
    memset(sh,0,sizeof(sh));

    while(scanf("%d%d%d",&row,&col,&kase)==3 && row)
    {
        init();

        while (kase--)
        {
            scanf("%s",cmd);
            int r1,c1,r2,c2;
            if(cmd[0] == 'E')
            {
                scanf("%d%d%d%d",&r1,&c1,&r2,&c2);
                swap(sh[r1][c1],sh[r2][c2]);
                // printsheet();
            }
            else
            {
                int oper;
                scanf("%d",&oper);
                memset(change,0,sizeof(change));
                //算法处理二：用change[]来标记需要处理的行/列
                //把要操作的数全部选出来
                for(int i = 0; i < oper; i++)
                {
                    //memset(change,0,sizeof(change));
                    int cur;
                    // int r1,c1,r2,c2;
                    scanf("%d",&cur);
                    change[cur] = 1;
                }
                //将change标记预先选出来

                if(cmd[0] == 'D')
                {
                    //change[cur] = 1;
                    del(cmd[1]);
                }
                if(cmd[0] == 'I')
                {
                    //change[cur] = 1;
                    insert(cmd[1]);
                }
                // printsheet();
                // printsheet();
            }
        }

        memset(ans,0,sizeof(ans));
        //这是一个好习惯！
        //所有全局变量在赋值之前需要初始化
        for(int i = 0; i <= row; i++)
        {
            for(int j = 0; j <= col; j++)
            {
                ans[sh[i][j]/BIG][sh[i][j]%BIG] = i*BIG+j;
                //算法处理三：ans相当于一个hash map
                //将原来的坐标ans[sh[r]/BIG][sh[c]%BIG] --> newr*BIG+newc
                //这样最后查询(qr,qc),直接用ans[qr][qc]就可以了
                //ans[qr][qc]/BIG   ---    ans[qr][qc]%BIG就是最后的结论
            }
        }

        if(sit > 0)
            printf("\n");
        printf("Spreadsheet #%d\n",++sit);

        int query;
        int rq,cq;
        scanf("%d",&query);
        while(query--)
        {
            if(scanf("%d%d",&rq,&cq) == 2 && rq)
            {
                printf("Cell data in (%d,%d) ",rq,cq);
                int data = ans[rq][cq];
                if(data == 0)
                    printf("GONE\n");
                else
                    printf("moved to (%d,%d)\n",data/BIG,data%BIG);
            }
        }
    }
}