#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

struct act{
    int ass;
    int exe;

    act(int ass = 0, int exe = 0):ass(ass),exe(exe) {};

    bool operator < (const act& A) const{
        return exe > A.exe;
    }
};

int main(){
    int n;
    int ass,exe;
    int kase = 0;
    while(scanf("%d",&n) == 1 && n){
        vector<act> arange;

        for(int i = 0; i < n; i++){
            scanf("%d%d",&ass,&exe);
            arange.push_back(act(ass,exe));
        }
        sort(arange.begin(),arange.end());

        int ans = 0;
        int start = 0;
        for(int i = 0; i < n; i++) {
            start += arange[i].ass;
            ans = max(ans,start+arange[i].exe);
        }

        printf("Case %d: %d\n",++kase,ans);
    }
}