#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <sstream>
#include <algorithm>
#include <iomanip>

using namespace std;

const int maxn = 1020;

vector<string> linewords[maxn];
size_t wordlen[maxn],linecnt;

int main(){
    string line,word;
    fill_n(wordlen,maxn,0);
    linecnt = 0;

    while(getline(cin,line)) {
        stringstream ss(line);
        size_t wi = 0;

        while(ss >> word){
            wordlen[wi] = max(wordlen[wi], word.size());
            wi++;
            linewords[linecnt].push_back(word);
        }
        linecnt++;
    }

    for(int i = 0; i < linecnt; i++){
        const auto& wd = linewords[i];
        for(int j = 0; j < wd.size(); j++){
            int k = 0;
            if(j < wd.size()-1)
                k = wordlen[j]+1;
            cout << left << setw(k) << wd[j];
        }
        cout << endl;
    }
}