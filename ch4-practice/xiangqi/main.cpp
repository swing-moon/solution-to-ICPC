#include <iostream>
#include <cstdio>
#include <stdlib.h>
#include <string.h>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

typedef struct Points
{
    int x;
    int y;
    Points(int x = 0, int y = 0): x(x), y(y) {}
}points;


points operator+ (const points& A, const points& B) { return points(A.x+B.x,A.y+B.y); }
points operator- (const points& A, const points& B) { return points(A.x+B.x,A.y+B.y); }
points operator* (const points& A, int m) { return points(A.x*m,A.y*m); }
points operator/ (const points& A, int m) { return points(A.x/m,A.y/m); }
//运算符重载，判断马腿，容易写错
bool operator== (const points& A, const points& B) { return (A.x == B.x && A.y == B.y); }
bool operator< (const points& A, const points& B) { return (A.x < B.x) || (A.x == B.x && A.y < B.y) ; }

char grid[16][16] = {0};
points dirs[4] = {points(-1,0),points(0,1),points(1,0),points(0,-1)};
points hdirs[8] = {points(2,1),points(1,2),points(-1,2),points(-2,1),points(2,-1),points(1,-2),points(-1,-2),points(-2,-1)};

//红子吃掉黑子的情况要单独判断
//要把原来的那个位置放置什么类型的棋子给放到buffer中
//每判断一种情况后进行复原，再进行新一轮棋子的判断

points blackG, redG;
vector <points> redcheck;

bool valid(const points& p)
{
    bool flagx = (p.x>=1 && p.x<=3);
    bool flagy = (p.y>=4 && p.y<=6);
    return (flagx && flagy);
}

bool straight(const points& p1,const points& p2, int between)
// chariot and cannon
{
    int lx = min(p1.x,p2.x);
    int hx = max(p1.x,p2.x);
    int ly = min(p1.y,p2.y);
    int hy = max(p1.y,p2.y);

    int cnt = 0;
    if(p1.x == p2.x)
    {
        for(int y = ly+1; y < hy; y++)
        {
            if(grid[p1.x][y])
                cnt++;
            if(cnt > between)
                return false;
        }
        return cnt == between;
    }

    if(p1.y == p2.y)
    {
        for(int x = lx+1; x < hx; x++)
        {
            if(grid[x][p1.y])
                cnt++;
            if(cnt > between)
                return false;
        }
        return cnt == between;
    }
    return false;
}

bool checkmate(const points& r, const points& b)
{
    switch(grid[r.x][r.y])
    {
        case 'G':
            return r.y == b.y && straight(r,b,0);
        case 'R':
            return (r.y == b.y || r.x == b.x) && straight(r,b,0);
        case 'C':
            return (r.x == b.x || r.y == b.y) && straight(r,b,1);
        case 'H':
            for(int i = 0; i < 8; i++)
            {
                points hnext = r + hdirs[i];
                points leg = r + hdirs[i]/2;

                if(hnext == b && grid[leg.x][leg.y] == 0)
                    return true;
            }
            return false;

        default:
            return false;
    }
}
//将军的判断，是否完成了一次成功的将军

bool canwin()
{
    if(blackG.y == redG.y && straight(blackG,redG,0))
        return false;
//    bool live = true;

    for(int i = 0; i < 4; i++)
    {
        points bnext = blackG + dirs[i];
        bool live = true;

        if(!valid(bnext))
            continue;

        char buffer = grid[bnext.x][bnext.y];
        grid[bnext.x][bnext.y] = 0;

        //红子吃掉黑子的情况要单独判断
        //要把原来的那个位置放置什么类型的棋子给放到buffer中
        //每判断一种情况后进行复原，再进行新一轮棋子的判断
        //这里是特别需要注意的

        for(vector<points>::iterator it = redcheck.begin(); it != redcheck.end(); it++)
        {
            points rcur = *it;
            if(grid[rcur.x][rcur.y] && checkmate(rcur,bnext))
            {
                live = false;
                break;
            }
        }

        grid[bnext.x][bnext.y] = buffer;
        if(live)
            return false;
    }
    return true;
}

int main()
{
    int kase;
    while(scanf("%d%d%d",&kase,&(blackG.x),&(blackG.y))==3 && kase)
    {
        redcheck.clear();
        memset(grid,0,sizeof(grid));

        char type;
        int x,y;

        while(kase)
        {
//            cout << "kase: " << kase << endl;
            cin >> type >> x >> y;
            points p(x,y);
            redcheck.push_back(p);
            grid[p.x][p.y] = type;

            if(type == 'G')
                redG = p;
            kase--;
        }

        if(canwin())
            printf("YES\n");
        if(!canwin())
            printf("NO\n");
    }
}