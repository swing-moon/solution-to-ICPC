#include <iostream>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <vector>
#include <cstring>
#include <string.h>
#include <algorithm>

using namespace std;

unordered_map<char, string> morse;
unordered_map<string, vector<string> > context;

bool isprefix(const string& A, const string& B){
    return A.size() < B.size() && B.compare(0,A.size(),A) == 0;
}

void solve(const string& m){
    if(context.count(m)){
        const auto& word_v = context[m];
        cout << word_v.front();

        if(word_v.size() > 1){
            cout << "!";
        }
        cout << endl;
        return;
    }

    map<int, string> ans;

    for(const auto& it: context){
        const string& m_ext = it.first;

        if(isprefix(m, m_ext))
            ans[m_ext.size()-m.size()] = it.second.front();
        else if(isprefix(m_ext, m))
            ans[m.size()-m_ext.size()] = it.second.front();
    }
    cout << ans.begin() -> second << "?" << endl;
}


int main(){
    string alpha,M;

    while(cin >> alpha && alpha != "*"){
        cin >> M;
        morse[alpha[0]] = M;
    }
    while(cin >> alpha && alpha != "*"){
        M.clear();
        for(auto p : alpha){
            M += morse[p];
        }
        context[M].push_back(alpha);
    }
    while(cin >> M && M != "*"){
        solve(M);
    }
    return 0;
}