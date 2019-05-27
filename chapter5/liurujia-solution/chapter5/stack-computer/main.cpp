#include <iostream>
#include <set>
#include <algorithm>
#include <map>
#include <vector>
#include <stack>
#include <cstring>
#include <cstdlib>
#include <iterator>


using namespace std;

typedef set<int> Set;
map<Set,int> IDcache;
vector<Set> Setbuffer;

#define ALL(x) x.begin(),x.end()
#define INS(x) inserter(x,x.begin())

int ID(Set x){
    if(IDcache.count(x))
        return IDcache[x];

    Setbuffer.push_back(x);
    IDcache[x] = Setbuffer.size()-1;
    return IDcache[x];
}

void solve(){
    stack<int> s;
    int n;
    cin >> n;

    for(int i = 0; i < n; i++){
        string cmd;
        cin >> cmd;

        if(cmd[0] == 'P')
            s.push(ID(Set()));
        else if(cmd[0] == 'D')
            s.push(s.top());
        else{
            Set x1 = Setbuffer[s.top()]; s.pop();
            Set x2 = Setbuffer[s.top()]; s.pop();
            Set x;

            if(cmd[0] == 'U')
                set_union(ALL(x1),ALL(x2),INS(x));
            if(cmd[0] == 'I')
                set_intersection(ALL(x1),ALL(x2),INS(x));
            if(cmd[0] == 'A'){
                x = x2;
                x.insert(ID(x1));
            }
            s.push(ID(x));
        }

        cout << Setbuffer[s.top()].size() << endl;
    }
}

int main(){
    int kase;
    cin >> kase;
    while(kase--){
        solve();
        printf("***\n");
    }
}