#include <iostream>
#include <cstring>
#include <algorithm>
#include <string>

using namespace std;

const int maxn = 100+5;
const int maxcol = 60;
string filename[maxn];

void print(const string& s, int len, char extra){
    cout << s;
    for(int i = 0; i < len-s.length(); i++)
        cout << extra;
}

int main(){
    int n;
    while(cin >> n){
        int M = 0;
        for(int i = 0; i < n; i++){
            cin >> filename[i];
            M = max(M,(int)filename[i].length());
        }

        int cols = (maxcol-M) / (M+2) + 1;
        int rows = (n-1) / cols + 1;
        print("",60,'-');
        cout << "\n";

        sort(filename,filename+n);
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                int id = c*rows + r;
                if(id < n)
                    print(filename[id], c==cols-1?M:M+2, ' ');
            }
            cout << "\n";
        }
    }
}