#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int d,s,b,w;
const int maxn = 6800;
char data[7][maxn];
bool parity;

bool read(){
    scanf("%d%d%d",&d,&s,&b);

    if(!d)
        return false;
    memset(data, 0, sizeof(data));
    parity = getchar()=='0';
    w = s*b;

    for(int i = 0; i < d; i++)
        scanf("%s",data[i]);

    return true;
}

bool fix(){
    w = s*b;

    for(int i = 0; i < w; i++){
        int sum = 0;
        int bro_cnt, mark_bro;
        for(int j = 0; j < d; j++){
            if(data[j][i] == '1')   sum++;
            if(data[j][i] == 'x'){
                bro_cnt++;
                mark_bro = j;
            }
        }

        sum %= 2;
        if(bro_cnt >= 2)
            return false;
        else if(bro_cnt == 1){
            if(sum){
                //odd
                if(parity == 'E')
                    data[mark_bro][i] = '1';
                else
                    data[mark_bro][i] = '0';

            }else{
                if(parity == 'E')
                    data[mark_bro][i] = '0';
                else
                    data[mark_bro][i] = '1';
            }
        }else if(bro_cnt == 0){
            if(parity == 'E' && sum == 1)
                return false;
            if(parity == 'O' && sum == 0)
                return false;
        }
    }
    return true;
}

int main(){
    int kase = 0;
    while(read()){
        //
    }
}