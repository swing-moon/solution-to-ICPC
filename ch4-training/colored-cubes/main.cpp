#include <iostream>
#include <cstdio>
#include <cstring>

int left[] = {4,0,2,3,5,1};
int up[] = {2,1,5,0,4,3};

int rot(int* way, int* cur){
    int chan[6];
    memcpy(chan,cur, sizeof(chan));
    for(int i = 0; i < 6; i++)
        cur[i] = way[chan[i]];
}

void enumerate(){
    int start[6] = {0,1,2,3,4,5};
    printf("int posture[24][6] = {\n");

    for(int i = 0; i < 6; i++){
        int cur[6];
        memcpy(cur,start, sizeof(cur));

        if(i == 0)
            rot(up,cur);
        if(i == 1){
            rot(left,cur);
            rot(up,cur);
        }
        if(i == 3){
            rot(up,cur); rot(up,cur);
        }
        if(i == 4){
            rot(left,cur); rot(left,cur); rot(left,cur);
            rot(up,cur);
        }
        if(i == 5){
            rot(left,cur); rot(left,cur);
            rot(up,cur);
        }

        for(int k = 0; k < 4; k++){
            printf("{%d, %d, %d, %d, %d, %d}\n",cur[0],cur[1],cur[2],cur[3],cur[4],cur[5]);
            rot(left,cur);
        }
    }

    printf("};\n");
}

int main(){
    enumerate();
    return 0;
}