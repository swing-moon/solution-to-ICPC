#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <set>
#include <algorithm>
#include <map>

using namespace std;

struct Array{
    int len;
    map<int,int> value;

    Array(){    remove();   }
    void remove(){
        len = -1;
        value.clear();
    }

    void init(int sz){
        len = sz;
        value.clear();
    }

    bool exist(){
        return len >= 0;
    }

    bool idxExist(int idx){
        if(value.count(idx)){
            return true;
        }
        return false;
    }
    bool setValue(int idx, int v){
        if(idx >= len)
            return false;
        value[idx] = v;
        return true;
    }
};

const int MAXA = 128;
Array arr[MAXA];
string buf;



int getidx(string s,int p, int& flag){
    int v;
    char alpha;

    if(isdigit(s[p])){
        v = 0;
        while(isdigit(s[p])){
            v = v*10 + s[p] - '0';
            p++;
        }
        return v;
    }else if(isalpha(s[p])){
        alpha = s[p];
        p += 2;

        Array& ar = arr[alpha];

        v = getidx(s,p,flag);
        if(ar.exist()){
            if(v < ar.len && ar.idxExist(v))
                return ar.value[v];
            else
                flag = 0;
        }else{
            flag = 0;
        }
    }
    return 0;
}

int main(){
    int linenum = 0, bugnum = 0;

    while(getline(cin,buf)){
//        cout << buf << endl;
        int len = buf.length();
        if(buf[0] == '.'){
            if(linenum)
                printf("%d\n",bugnum);
            for(int i = 0; i < MAXA; i++)   arr[i].remove();
            linenum = 0;
            bugnum = 0;
            continue;
        }
        if(bugnum > 0)
            continue;

        int pos = buf.find('=');
        if(pos != string::npos){
            int flag = 1;
            int rv = getidx(buf,pos+1,flag);

            string ls = buf.substr(0,pos);
            char a = ls[0];
            int idx = getidx(ls,2,flag);

            Array& ar = arr[a];
            if(ar.exist() && flag && ar.setValue(idx,rv)){
                linenum++;
            }else{
                bugnum = linenum+1;
            }

        }else{
            char name;  int sz;
            sscanf(buf.c_str(),"%c[%d]",&name,&sz);
            arr[name].init(sz);
            linenum++;
        }
    }
}