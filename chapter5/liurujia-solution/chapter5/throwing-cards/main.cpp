#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>

using namespace std;

int main(){
    int n;
    while(scanf("%d",&n) == 1 && n){
        queue<int> q;
        for(int i = 1; i <= n; i++)
            q.push(i);
        printf("Discarded cards:");

        bool first = true;
        while(q.size() >= 2){
            if(first){
                first = false;
                printf(" %d",q.front());
            }else{
                printf(", %d",q.front());
            }

            q.pop();
            q.push(q.front());
            q.pop();
        }
        printf("\nRemaining card: %d\n",q.front());
    }
}