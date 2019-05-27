#include <iostream>
#include <cstring>
#include <string.h>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

typedef struct points
{
    int row;
    int col;
    points(int row = 0, int col = 0):row(row),col(col) {}
}pos;

bool operator< (const pos& A,const pos& B) {return (A.row<B.row) || (A.row==B.row && A.col<B.col);}
bool operator== (const pos& A,const pos& B) {return (A.row==B.row) && (A.col==B.col);}
bool operator!= (const pos& A,const pos& B) {return (A.row!=B.row) || (A.col!=B.col);}
pos operator+ (const pos& A,const pos& B) {return pos(A.row+B.row,A.col+B.col);}
pos operator- (const pos& A,const pos& B) {return pos(A.row-B.row,A.col-B.col);}

char board[16][16];
bool mark[16][16];
char player;

pos dr1[4] = {pos(-1,0),pos(-1,1),pos(0,1),pos(1,1)};
pos dr2[4] = {pos(1,0),pos(1,-1),pos(0,-1),pos(-1,-1)};
pos walk[8] = {pos(-1,0),pos(-1,1),pos(0,1),pos(1,1),pos(1,0),pos(1,-1),pos(0,-1),pos(-1,-1)};

set<pos> res;
map<pos,int> dir;
//remember clear()!

bool valid(const pos& p)
{
    bool flag1 = p.row >= 1 && p.row <= 8;
    bool flag2 = p.col >= 1 && p.col <= 8;
    return flag1 && flag2;
}

bool empty(const pos& p){
    return board[p.row][p.col] == '-';
}

char getboard(){
    for(int i = 1; i <= 8; i++){
        for(int j = 1; j <= 8; j++){
            cin >> board[i][j];
        }
    }
    cin >> player;
    return player;
}

void printboard(int kase)
{
    for(int i = 1; i <= 8; i++){
        for(int j = 1; j <= 8; j++){
            cout << board[i][j];
        }
        cout << endl;
    }
    if(kase)
        cout << endl;
}

void checkdisk(char opp,char curp){
    for(int i = 1; i <= 8; i++){
        for(int j = 1; j <= 8; j++){
            if(board[i][j] == opp){
                pos cur(i,j);
//                pos up = cur, down = cur;

                for(int k = 0; k < 4; k++){
                    pos up = cur, down = cur;
                    do{
                        up = up + dr1[k];
                        if(!valid(up))
                            break;
                    }while(board[up.row][up.col] == opp);

                    do{
                        down = down + dr2[k];
                        if(!valid(down))
                            break;
                    }while(board[down.row][down.col] == opp);

                    if(!valid(up) || !valid(down))
                        continue;

                    char flag1 = board[up.row][up.col];
                    char flag2 = board[down.row][down.col];

                    if(flag1 == '-' && flag2 == curp){
                        res.insert(up);
                        dir[up] = k;
                    }
                    if(flag1 == curp && flag2 == '-'){
                        res.insert(down);
                        dir[down] = k;
                    }
                }
            }
        }
    }
}

void printpos()
{
    set<pos>::iterator it;
    int cnt = 0;
    if(!res.size()){
        printf("No legal move.");
    } else{
        for(it = res.begin(); it != res.end(); it++){
            cnt++;
            printf("(%d,%d)",(*it).row,(*it).col);
            if(cnt!=res.size())
                printf(" ");
        }
    }
    printf("\n");
}

void change(const pos& p, char opp, char curp)
{
    pos start = p;
    mark[start.row][start.col] = 1;

    for(int i = 0; i < 8; i++){
        pos next = p + walk[i];

        if(empty(next))
            continue;

        while(board[next.row][next.col] == opp){
            next = next + walk[i];
        }

        if(board[next.row][next.col] == curp){
            for(next = next-walk[i]; next!=start; next = next-walk[i]){
                if(!mark[next.row][next.col]){
                    mark[next.row][next.col] = 1;
                }
            }
        }
    }

    for(int i = 1; i <= 8; i++){
        for(int j = 1; j <= 8; j++){
            if(mark[i][j] == 1){
                board[i][j] = curp;
            }
        }
    }
}

pos getmove(){
    int row,col;
    cin >> row >> col;
    return pos(row,col);
}

void list(){
    int w = 0,b = 0;
    for(int i = 1; i <= 8; i++){
        for(int j = 1; j <= 8; j++){
            if(board[i][j] == 'W')
                w++;
            if(board[i][j] == 'B')
                b++;
        }
    }
    printf("Black - %2d White - %2d\n",b,w);
}


int main()
{
    /*char curp = getboard();
    char opp;
    if(curp == 'B')
        opp = 'W';
    if(curp == 'W')
        opp = 'B';

    checkdisk(opp,curp);
//    printdir();
    printpos();

    pos disk = getmove();
    change(disk,opp,curp);
    printboard();

//    char cmd;
//    cin >> cmd;
//
//    if(cmd == 'L')
//        printpos();*/

    int kase;
    scanf("%d",&kase);

    while(kase--){
        memset(board,0, sizeof(board));
        memset(mark,0, sizeof(mark));
        res.clear();
        dir.clear();

        char gamer[2];
        gamer[0] = getboard();//cur

        if(gamer[0] == 'B')
            gamer[1] = 'W'; //another
        if(gamer[0] == 'W')
            gamer[1] = 'B';

        int flag = 0;

        char cmd[5];
        for(;;){
            scanf("%s",cmd);

            if(cmd[0] == 'Q'){
                printboard(kase);
                break;
            }
            if(cmd[0] == 'L'){
                checkdisk(gamer[1-flag],gamer[flag]);
                printpos();

                if(!res.size()){
//                    memset(mark,0, sizeof(mark));
                    flag = 1-flag;
                    checkdisk(gamer[1-flag],gamer[flag]);
                }
                res.clear();
            }
            if(cmd[0] == 'M'){
                int x = cmd[1]-'0';
                int y = cmd[2]-'0';
                pos move = pos(x,y);
                memset(mark,0,sizeof(mark));

                change(move,gamer[1-flag],gamer[flag]);
                list();

//                printboard();

                flag = 1-flag;
            }


//            flag = 1-flag;
        }
    }


}