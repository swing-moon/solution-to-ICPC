#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <string>
#include <sstream>


using namespace std;
typedef pair<int,int> pii;

const int maxr = 10000+5;
const int maxc = 10+5;

int db[maxr][maxc], cnt = 0;
map<string,int> id;

int m,n;

int getid(const string& str){
    if(!id.count(str))
        id[str] = ++cnt;

    return id[str];
}

void find(){
    for(int c1 = 0; c1 < m; c1++){
        for(int c2 = c1+1; c2 < m; c2++){
            map<pii,int> group;
            for(int i = 0; i < n; i++){
                pii p = make_pair(db[i][c1],db[i][c2]);
                if(group.count(p)){
                    printf("NO\n");
                    printf("%d %d\n",group[p]+1, i+1);
                    printf("%d %d\n",c1+1,c2+1);
                    return;
                }
                group[p] = i;
            }
        }
    }
    printf("YES\n");
}

int main(){

    string s;
    while(getline(cin,s)){
        stringstream ss(s);
        if(!(ss >> n >> m))
            break;

        cnt = 0;
        id.clear();
        for(int i = 0; i < n; i++){
            getline(cin,s);
            int lastpos = -1;
            for(int j = 0; j < m; j++){
                int curp = s.find(',',lastpos+1);
                if(curp == string::npos)
                    curp = s.length();

                db[i][j] = getid(s.substr(lastpos+1,curp-1-lastpos));
                lastpos = curp;
            }
        }
        find();
    }
}