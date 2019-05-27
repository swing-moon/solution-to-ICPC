#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <assert.h>

using namespace std;

#define _for(i,a,b) for( int i = (a); i < (b); i++ )
#define _rep(i,a,b) for( int i = (a); i <= (b); i++ )

const int W = 8, IPW = 4*W;

bool inrange(int val, int a, int b){
    if(a > b)
        return inrange(val, b, a);
    return a <= val && val <= b;
}

void toBinary(int val, int* bin, int pos){
    assert(inrange(val,0,255));

    _for(i,0,W){
        bin[pos+W-1-i] = val % 2;
        val /= 2;
    }
}

void printip(const int* bin){

    bool first = true;

    for(int i = 0; i < 4; i++){
        int x = 0;
        for(int k = i*W; k < (i+1)*W; k++){
            x = (x << 1) | bin[k];
        }

        if(first)
            first = false;
        else
            printf(".");
        printf("%d",x);
    }
    puts("");
}

const int maxn = 1024;
int subip[maxn][IPW+5];

int main(){
    int subNet[IPW];
    int n, ip[4];

    while(scanf("%d",&n) == 1){
        _for(i,0,n){
            scanf("%d.%d.%d.%d",&ip[0],&ip[1],&ip[2],&ip[3]);
            _for(j,0,4){
                toBinary(ip[j],subip[i],j*W);
            }
        }
        //finished! Get ip binary presentation
        memset(subNet,0,sizeof(subNet));
        //enumerate
        int len;
        for(len = 0; len < IPW; len++){
            bool same = true;

            //erogodic
            for(int p = 1; p < n; p++){
                if(subip[p-1][len] != subip[p][len]){
                    same = false;
                    break;
                }
            }
            if(!same)
                break;
        }
        //len: position-> the first different element
        //len start from 0, it means the longest length

        fill_n(subNet,len,1);
        fill_n(subip[0]+len,IPW-len,0);

        printip(subip[0]);
        printip(subNet);

    }
}