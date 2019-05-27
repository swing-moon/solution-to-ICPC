#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

struct stu{
    int a;
    int b;
    int c;
};

#define MAX_TIME 1000000
int n;
istream& operator>> (istream& is, stu& s) { return is >> s.a >> s.b >> s.c;}

stu stus[10+5];

bool action(int kase,int t){
    int wake = 0, sleep = 0;

    for(int i = 0; i < n; i++){
        if(stus[i].c <= stus[i].a)  wake++;
    }
    sleep = n-wake;

    if(sleep == 0){
        cout << "Case " << kase << ": " << t << endl;
        return true;
    }

    for(int i = 0; i < n; i++){
        stu& s = stus[i];
        s.c++;

        if(s.c == s.a + s.b + 1)    s.c = 1;
        if(s.c == s.a + 1 && wake >= sleep) s.c = 1;
    }
    return false;

}

int main(){
    int kase = 1;
    while(scanf("%d",&n) && n){
        for(int i = 0; i < n; i++){
            cin >> stus[i];
        }

        int t;
        for(t = 1; t < MAX_TIME; t++){
            if(action(kase, t))
                break;
        }

        if(t == MAX_TIME)
            cout << "Case " << kase << ": " << "-1" << endl;

        kase++;
    }
}