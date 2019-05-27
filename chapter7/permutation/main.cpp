#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

int A[101];

void permutation(int n, int* A, int cur) {
    if(cur == n) {
        for(int i = 0; i < n; i++)  printf("%d ", A[i]);
        printf("\n");
    } else {
        for(int v = 1; v <= n; v++) {
            bool ok = 1;

            for(int j = 0; j < cur; j++) {
                if(A[j] == v)   ok = 0;
            }

            if(ok) {
                A[cur] = v;
                permutation(n, A, cur+1);
            }
        }
    }
}

int main() {
    int n;
    scanf("%d",&n);
    permutation(n, A, 0);
    return 0;
}