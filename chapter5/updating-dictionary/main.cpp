#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;
typedef map<string,string> Dicmap;

ostream& operator<< (ostream& os, const vector<string>& s){
    bool first = true;
    for(int i = 0; i < s.size(); i++){
        if(first)   first = false;
        else
            os << ",";

        os << s[i];
    }
    return os;
}

ostream& operator<< (ostream& os, Dicmap& m){
    os << "[";
    for(Dicmap::iterator it = m.begin(); it != m.end(); it++)
        os << "(" << it->first << ":" << it->second << ")";
    os << "]";
    return os;
}

void getval(Dicmap& m, const string& s){
    m.clear();
    bool flag = true;

    string key,val;

    for(int i = 0; i < s.size(); i++){
        char c = s[i];
        if(c == '{') continue;
        else if(c == ':')   flag = false;
        else if(c == ',' || c == '}'){
            if(key.empty()) continue;

            m[key] = val;
            key.clear();
            val.clear();
            flag = true;
        }else{
            if(flag)    key.push_back(c);
            else    val.push_back(c);
        }
    }
//    cout << "init: " << s << "---->" << m << endl;
}

int main(){
    Dicmap m1,m2;
    string line1, line2;
    vector<string> added, changed, del;

    int kase;
    cin >> kase;

    while(kase--){
        cin >> line1 >> line2;
        added.clear();
        del.clear();
        changed.clear();

        getval(m1,line1);
        getval(m2,line2);

        for(Dicmap::iterator it = m1.begin(); it != m1.end(); it++){
            const string& cur = it->first;
            if(m2.count(cur)){
                if(it->second != m2[cur])
                    changed.push_back(cur);
            }else{
                del.push_back(cur);
            }
        }

        for(Dicmap::iterator it = m2.begin(); it != m2.end(); it++){
            const string& cur = it->first;
            if(!m1.count(cur))
                added.push_back(cur);
        }

        if(added.empty() && del.empty() && changed.empty()){
            cout << "No changes\n" << endl;
            continue;
        }

        sort(added.begin(),added.end());
        sort(del.begin(),del.end());
        sort(changed.begin(),changed.end());

        if(!added.empty())
            cout << "+" << added << endl;
        if(!del.empty())
            cout << "-" << del << endl;
        if(!changed.empty())
            cout << "*" << changed << endl;

        cout << endl;
    }
}
