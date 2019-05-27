#include <iostream>
#include <cstring>
#include <cstdio>
#include <set>
#include <algorithm>

using namespace std;

int main(){
    set<string> words;
    string word, left, right;

    while(cin >> word ){
        words.insert(word);
    }

    for(const auto& s : words){
        for(int len = 1; len < s.size(); len++){
            left.assign(s,0,len);
            if(words.count(left)){
                right.assign(s,len,s.size()-len);
                if(words.count(right)){
                    cout << s << endl;
                    break;
                }
            }
        }
    }
}