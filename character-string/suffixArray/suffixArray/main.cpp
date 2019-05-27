//
//  main.cpp
//  suffixArray
//
//  Created by zhangmin chen on 2019/2/14.
//  Copyright © 2019 zhangmin chen. All rights reserved.

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cassert>
#include <stdexcept>

using namespace std;

/* string sort test:
int main() {
    freopen("input.txt", "r", stdin);
    string tmp;
    vector<string> ans;
    while(getline(cin, tmp)) {
        ans.push_back(tmp);
    }
    
    sort(ans.begin(), ans.end());
    for(auto& i : ans)
        cout << i << endl;
}
*/

class suffixArray {
private:
    string* str;
    int N;
    
    int lcp(string s, string t) {
        int len = (int) min(s.length(), t.length());
        for(int i = 0; i < len; i++) if(s[i] != t[i])
            return i;
        return len;
    }
    
public:
    suffixArray(string text) {
        //
        N = (int)text.length();
        str = new string[N+1];
        for(int i = 0; i < N; i++)
            str[i] = text.substr(i);
        sort(str, str+N);
    }
    ~suffixArray() { delete[] str; }
    
    int length() { return N; }
    string select(int i) { return str[i]; }
    int index(int i) { return (int) (N - str[i].length()); }
    
    int lcp(int i) { return lcp(str[i], str[i-1]); }
    
    int rank(string key) {
        int lo = 0, hi = N-1;
        while(lo <= hi) {
            int mid = lo + (hi-lo)/2;
            int cmp = strcmp(key.c_str(), str[mid].c_str());
            if(cmp < 0) hi = mid-1;
            else if(cmp > 0) lo = mid+1;
            else return mid;
        }
        return lo;
    }
};

int main() {
    freopen("input.txt", "r", stdin);
    string tmp;
    cin >> tmp;
    suffixArray sa(tmp);
    
    printf("  i ind lcp rnk select\n");
    printf("---------------------------\n");
    
    for(int i = 0; i < tmp.length(); i++) {
        int idx = sa.index(i);
        string ith = "\"" + tmp.substr(idx) + "\"";
        assert(tmp.substr(idx) == sa.select(i));
        // most important!
        
        int rk = sa.rank(tmp.substr(idx));
        if(i == 0)
            printf("%3d %3d %3s %3d %s\n", i, idx, "-", rk, ith.c_str());
        else {
            int lcp = sa.lcp(i);
            printf("%3d %3d %3d %3d %s\n", i, idx, lcp, rk, ith.c_str());
        }
    }
    
}
