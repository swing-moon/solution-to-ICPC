#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int main() {
    int k;
    while(scanf("%d",&k) == 1 && k) {
        vector<int> X, Y;
        for(int y = k+1; y <= 2*k; y++) {
            if(k*y % (y-k) == 0) {
                X.push_back(k*y / (y-k));
                Y.push_back(y);
            }
        }

        printf("%d\n",X.size());
        for(int i = 0; i < X.size(); i++)
            printf("1/%d = 1/%d + 1/%d\n", k, X[i], Y[i]);
    }
}