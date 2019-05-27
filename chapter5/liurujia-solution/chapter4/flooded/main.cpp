#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;
#define MAXH 100000

int main(){
    vector<int> H;
    int m,n;
    double vol;
    double walen;
    double last;

    for(int kase = 1; scanf("%d%d",&m,&n)==2 && m && n; kase++){
        n *= m;
        H.clear();

        int data;
        for(int i = 0; i < n; i++){
            cin >> data;
            H.push_back(data);
        }
        H.push_back(MAXH);

        sort(H.begin(), H.end());
        scanf("%lf",&vol);
        vol /= 100;

        last = (double)(H.size()-1);
        for(int i = 1; i <= n; i++){
            vol += H[i-1];
            walen = (double)(vol / i);

            if(walen < H[i]){
                last = (double)i;
                break;
            }
        }

        printf("Region %d\n",kase);
        printf("Water level is %.2lf meters.\n",walen);
        printf("%.2lf percent of the region is under water.\n\n",last/(H.size()-1)*100);
    }
}