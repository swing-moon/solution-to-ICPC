#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

const int R = 256;
const int maxl = 200;

int dfa[R+1][maxl];

void init_DFA(const string& pat) {
    // calculate failure function
    memset(dfa, 0, sizeof(dfa));
    dfa[pat[0]][0] = 1;
    for(int i = 1, state = 0; i < pat.length(); i++) {
        for(int c = 0; c < R; c++)
            dfa[c][i] = dfa[c][state];

        dfa[pat[i]][i] = i+1;
        state = dfa[pat[i]][state];
    }
}

int kmp(const string& txt, const string& pat) {
    int i, j;
    init_DFA(pat);
    for(i = 0, j = 0; i < txt.length() && j < pat.length(); i++) {
        j = dfa[txt[i]][j];
    }

    if(j == pat.length()) return i - pat.length();
    else return txt.length();
}

int main() {
    freopen("input.txt", "r", stdin);
    string txt, pat;
    cin >> txt >> pat;
    printf("指针的位置在: ");
    cout << kmp(txt, pat) << endl;
}