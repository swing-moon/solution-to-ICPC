#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int readInt(){
    int x;
    scanf("%d",&x);
    return x;
}

int main(){
    int kase = readInt();
    vector<int> seq, zeroseq;
    set<vector<int> > ans;

    while(kase--){
        int n = readInt();
        seq.clear();    zeroseq.resize(n);

        for(int i = 0; i < n; i++){
            seq.push_back(readInt());
        }


        bool zero = false, loop = false;
        ans.clear();

        ans.insert(seq);
        do{
            if(seq == zeroseq){
                puts("ZERO");
                break;
            }

            int a0 = seq[0];
            for(int i = 0; i < n; i++){
                if(i == n-1)
                    seq[i] = abs(seq[i]-a0);
                else{
                    seq[i] = abs(seq[i]-seq[i+1]);
                }
            }

            if(!ans.count(seq))
                ans.insert(seq);
            else{
                puts("LOOP");
                break;
            }
        }while (true);
    }
}