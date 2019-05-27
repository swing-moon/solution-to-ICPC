#include <iostream>
using namespace std;

int main() {
    int data[20], kase = 0, n;

    while(cin >> n && n) {
        for(int i = 0; i < n; i++)
            cin >> data[i];

        long long ans = 0;

        for(int i = 0; i < n; i++) {
            long long mul = 1;
            for(int j = i; j < n; j++) {
                mul *= data[j];
                if(mul > ans)   ans = mul;
            }
        }

        cout << "Case #" << ++kase << ": The maximum product is " << ans << ".\n\n";
    }
}