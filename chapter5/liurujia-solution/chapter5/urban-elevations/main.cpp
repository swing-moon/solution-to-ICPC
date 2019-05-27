#include <iostream>
#include <cstdio>
#include <algorithm>

using namespace std;

const int maxn = 105;

struct building{
    int id;
    double x,y,w,d,h;
    bool operator < (const building& b) const{
        return x < b.x || (x == b.x && y < b.y);
    }
}bud[maxn];

double range[maxn*2];
int n;

bool cover(int i, double r){
    return bud[i].x <= r && bud[i].x+bud[i].w >= r;
}
//b[i] cover r
//true!

bool visible(int i, double r){
    //judge i is visible?
    if(!cover(i,r))
        return false;

    for(int k = 0; k < n; k++){
        if(cover(k,r) && bud[k].y < bud[i].y && bud[k].h >= bud[i].h)
            return false;
    }
    return true;
}


int main(){
    int kase = 0;
    while(scanf("%d",&n) == 1 && n) {
        for(int i = 0; i < n; i++){
            scanf("%lf%lf%lf%lf%lf",&bud[i].x,&bud[i].y,&bud[i].w,&bud[i].d,&bud[i].h);
            range[i*2] = bud[i].x;  range[i*2+1] = bud[i].x+bud[i].w;
            bud[i].id = i+1;
        }

        sort(bud,bud+n);
        sort(range,range+2*n);
        int m = unique(range,range+2*n) - range;

        if(kase++)  printf("\n");
        printf("For map #%d, the visible buildings are numbered as follows:\n%d",kase,bud[0].id);

        for(int i = 1; i < n; i++){
            bool vis = false;
            for(int j = 0; j < m -1; j++){
                if(visible(i, (range[j]+range[j+1])/2 )){
                    vis = true;
                    break;
                }
            }

            if(vis)
                printf(" %d",bud[i].id);
        }
        printf("\n");
    }
}