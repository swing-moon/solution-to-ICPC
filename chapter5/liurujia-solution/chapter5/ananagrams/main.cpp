#include <iostream>
#include <cstdio>
#include <map>
#include <set>
#include <vector>
#include <cstring>
#include <algorithm>

using namespace std;
map<string,int> cnt;
vector<string> words;

string rearr(const string& s){
    string ans = s;
    for(int i = 0; i < ans.length(); i++)
        ans[i] = tolower(ans[i]);

    sort(ans.begin(),ans.end());
    return ans;
}

int main(){
    string s;

    while(cin >> s){
        if(s[0] == '#')
            break;

        words.push_back(s);
        string tmp = rearr(s);

        if(cnt.count(tmp) == 0)
            cnt[tmp] = 0;
        cnt[tmp]++;
    }

    vector<string> ans;
    for(int i = 0; i < words.size(); i++){
        if(cnt[rearr(words[i])] == 1)
            ans.push_back(words[i]);
    }

    sort(ans.begin(),ans.end());

    for(int i = 0; i < ans.size(); i++)
        cout << ans[i] << "\n";
}