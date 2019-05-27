#include <iostream>
#include <cstdio>
#include <cstring>
#include <string.h>
#include <algorithm>
#include <cstdlib>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <sstream>

using namespace std;
typedef set<int> intSet;
vector<string> all;
intSet emptySet;

struct Doc {
    //
    map<string, intSet> index;
    intSet lineID;

    void addline(const string& str, int idx) {
        //
        string buf; lineID.insert(idx);
        for(int i = 0; i < str.size(); i++) {
            char c = str[i];

            if(isalpha(c)) {
                buf.push_back(tolower(c));
            } else if(!buf.empty()) {
                // index[tmp] = idx;

                index[buf].insert(idx);
                buf.clear();
            }
        }
        if(!buf.empty()) {
            index[buf].insert(idx); buf.clear();
        }
    }

    // when query: for(auto& id : index[buf]) cout << all[id] << endl;

    const intSet& findWord(const string& w) {
        if(!index.count(w)) return emptySet;
        return index[w];
    }
};


vector<Doc> article;

void getword(const string& str, vector<string>& qwords) {
    qwords.clear();
    stringstream ss(str);

    string tmp;
    while(ss >> tmp) {
        qwords.push_back(tmp);
    }
}

void printAns(const intSet& ans) {
    for(auto& p : ans) cout << all[p] << endl;
}

void query(const vector<string>& qwords) {
    //
    const string& one = qwords.front();
    const string& two = qwords.back();

    bool match, first = true;
    bool flag = true;

    if(qwords.size() == 1) {
        for(int i = 0; i < article.size(); i++) {
            Doc& atc = article[i];
            // check atc.index
            const intSet& bufID = atc.findWord(one);
            if(bufID.empty()) match = false;
            else match = true;

            if(!match) continue;

            if(first) first = false;
            else cout << "----------" << endl;

            printAns(bufID); flag = false;
        }
    }

    if(qwords.size() == 2) {
        for(int i = 0; i < article.size(); i++) {
            Doc& atc = article[i];
            const intSet& bufID = atc.findWord(two);
            if(bufID.empty()) match = true;
            else match = false;

            if(!match) continue;

            if(first) first = false;
            else cout << "----------" << endl;

            printAns(atc.lineID); flag = false;
        }
    }

    if(qwords.size() == 3) {
        for(int i = 0; i < article.size(); i++) {
            Doc& atc = article[i];
            const intSet& ans1 = atc.findWord(one);
            const intSet& ans2 = atc.findWord(two);

            if(qwords[1] == "AND") {
                //
                if(!ans1.empty() && !ans2.empty()) match = true;
                else match = false;

            } else if(qwords[1] == "OR") {
                //
                if(!ans1.empty() || !ans2.empty()) match = true;
                else match = false;
            }

            if(!match) continue;

            vector<int> ans(ans1.size() + ans2.size());
            vector<int>::iterator last = set_union(ans1.begin(), ans1.end(), ans2.begin(), ans2.end(), ans.begin());

            if(first) first = false;
            else cout << "----------" << endl;
            for(auto p = ans.begin(); p != last; p++) cout << all[*p] << endl; flag = false;
        }
    }

    if(flag) cout << "Sorry, I found nothing." << endl;
    cout << "==========" << endl;
}

int main() {
    int N, M;
    string line;

    cin >> N; getline(cin, line);
    article.resize(N);

    // fresh string
    cout << line;


    for(int i = 0; i < N; i++) {

        while(true) {
            Doc& atc = article[i];

            getline(cin, line);
            if(line == "**********") break;

            // atc.addline()
            all.push_back(line);
            atc.addline(line, all.size()-1);
        }
    }
    // get all articles

    /*
    for(int i = 0; i < N; i++) {
        Doc& atc = article[i];
        for(auto it = atc.index.begin(); it != atc.index.end(); it++) {
            cout << it->first << ": " << endl;
            for(auto p : it->second) cout << all[p] << endl;
        }
        cout << "---------" << endl;
    }
    */

    cin >> M; getline(cin, line);

    vector<string> qwords;
    for(int i = 0; i < M; i++) {
        getline(cin, line);
        getword(line, qwords);
        query(qwords);
    }
}