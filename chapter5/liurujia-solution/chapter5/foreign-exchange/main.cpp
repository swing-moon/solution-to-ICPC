#include <iostream>
#include <cstdio>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;
typedef pair<int,int> ipair;

int readInt(){
    int x;
    scanf("%d",&x);
    return x;
}

int main(){
    map<ipair,int> ex;
    int n;
    while(n = readInt()){
        bool ans = true;
        ex.clear();

        for(int i = 0; i < n; i++){
            int A = readInt();  int B = readInt();
            ex[make_pair(A,B)]++;
        }

        for(const auto& p : ex){
            ipair p2 = make_pair(p.first.second,p.first.first);

            if(ex[p2] != p.second){
                ans = false;
                break;
            }
        }

        puts(ans ? "YES" : "NO");
    }
}