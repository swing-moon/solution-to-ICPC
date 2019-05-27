#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

const int R = 256;

int Right[R+1];

void init(const string& pat) {
    //
    for(int c = 0; c < R; c++)
        Right[c] = -1;
    for(int i = 0; i < pat.length(); i++)
        Right[pat[i]] = i;
}

int boyerMoore(const string& txt, const string& pat) {
    init(pat);
    int len_t = txt.length(), len_p = pat.length();
    int skip;

    for(int i = 0; i <= len_t - len_p; i += skip) {
        skip = 0;
        for(int j = len_p-1; j >= 0; j--) {
            if(pat[j] != txt[i+j]) {
                skip = j - Right[txt[i+j]];
                if(skip < 1) skip = 1;
                break;
            }
        }

        if(skip == 0) return i;
    }
    return len_t;
}

int main() {
    freopen("input.txt", "r", stdin);
    string txt, pat;
    cin >> txt >> pat;

    int ans = boyerMoore(txt, pat);
    cout << "指针的位置在: " << ans << endl;
}