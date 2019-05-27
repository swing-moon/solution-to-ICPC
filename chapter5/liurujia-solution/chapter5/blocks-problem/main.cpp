#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 30;
int n;
vector<int> pile[maxn];

void FindBlock(int val, int& p, int& h){
    for(p = 0; p < n; p++){
        for(h = 0; h < pile[p].size(); h++){
            if(pile[p][h] == val)
                return;
        }
    }
}

void ClearAbove(int p, int h){
    //exclude h
    for(int i = h+1; i < pile[p].size(); i++){
        int curp = pile[p][i];
        pile[curp].push_back(curp);
    }
    pile[p].resize(h+1);
}

void MoveOnto(int p, int h, int p2){
    //include h
    for(int i = h; i < pile[p].size(); i++){
        pile[p2].push_back(pile[p][i]);
    }
    pile[p].resize(h);
}

void print(){
    for(int i = 0; i < n; i++){
        printf("%d:",i);

        for(int j = 0; j < pile[i].size(); j++){
            printf(" %d",pile[i][j]);
        }
        printf("\n");
    }
}

int main(){
    int a,b;
    cin >> n;
    string s1,s2;
    for(int i = 0; i < n; i++)
        pile[i].push_back(i);

    while((cin >> s1 >> a >> s2 >> b) && s1!="quit"){
        int pa,ha,pb,hb;
        FindBlock(a,pa,ha);
        FindBlock(b,pb,hb);

        if(pa == pb)
            continue;

        if(s2 == "onto")
            ClearAbove(pb,hb);
        if(s1 == "move")
            ClearAbove(pa,ha);

        MoveOnto(pa,ha, pb);
    }
    print();
}