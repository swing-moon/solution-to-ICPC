#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 6500;
char data[8][maxn];
bool parity;
int d,s,b,w;
char type;


bool fix(){
    w = s*b;

    for(int i = 0; i < w; i++){
        int sum = 0;
        int bro_cnt = 0, bro_id = 0;

        for(int j = 0; j < d; j++){
            if(data[j][i] == '1'){
                sum++;
            }
            if(data[j][i] == 'x'){
                bro_cnt++;
                bro_id = j;
            }
        }

        sum %= 2;

        if(bro_cnt >= 2)
            return false;
        else if(bro_cnt == 1){
            if(sum){
                if(parity)
                    data[bro_id][i] = '0';
                else
                    data[bro_id][i] = '1';
            }else{
                if(parity)
                    data[bro_id][i] = '1';
                else
                    data[bro_id][i] = '0';
            }
        }else if(bro_cnt == 0){
            if(parity == 0 && sum == 1)
                return false;
            if(parity == 1 && sum == 0)
                return false;
        }
    }
    return true;
}

void printdata(){
    int sum = 0;
    int bit_cnt = 0;
    for(int i = 0; i < b; i++){
        int except = i % d;
        for(int j = 0; j < d; j++){
            if(j == except)
                continue;

            for(int k = i*s; k < i*s+s; k++){
                bit_cnt = (bit_cnt+1) % 4;

                if(data[j][k] == '0')
                    sum = sum << 1;
                if(data[j][k] == '1')
                    sum = (sum << 1)  + 1;

                if(bit_cnt == 0){
                    // bit finish!
                    printf("%X",sum);
                    sum = 0;
                }

            }
        }
    }
    if(bit_cnt){
        // complete 0
        int add_0 = 4 - bit_cnt;
        sum = sum << add_0;
        printf("%X",sum);
    }
    printf("\n");
}

int main(){
    int kase = 0;
    while(cin >> d && d){
        memset(data, 0, sizeof(data));
        cin >> s >> b >> type;
        parity = type == 'O';

        for(int i = 0; i < d; i++)
            cin >> data[i];

        if(!fix())
            printf("Disk set %d is invalid.\n",++kase);
        else{
            printf("Disk set %d is valid, contents are: ",++kase);
            printdata();
        }

    }


    return 0;
}