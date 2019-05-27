#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <set>

using namespace std;
const int maxn = 1000+5;

struct point{
    double x;
    double y;
    point(double x = 0, double y = 0):x(x),y(y) {}
    bool operator< (const point& b) const{
        return x < b.x || (x == b.x && y < b.y);
    }
};

int main(){
    int kase;
    scanf("%d",&kase);
    while(kase--){
        int n;
        scanf("%d",&n);
        set<point> ans;

        double m = 0;
        for(int i = 0; i < n; i++){
            point p;
            cin >> p.x >> p.y;
            ans.insert(p);

            m += p.x;
        }
        m /= n;

        bool flag = true;
        for(const auto& s:ans){
            if(s.x == m)
                continue;
            double x2 = 2.0*m-s.x;
            if(!ans.count(point(x2,s.y))){
                flag = false;
                break;
            }
        }

        if(flag)
            printf("YES");
        else
            printf("NO");

        if(kase)
            printf("\n");
    }
}