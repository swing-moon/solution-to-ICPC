#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>

using namespace std;

typedef vector<int> IntVec;
typedef set<int> IntSet;
IntSet emptySet;

struct Doc{
    IntSet lines;
    map<string,IntSet> words;

    void addline(const string& s, int l){
        lines.insert(l);
        string w;
        // w is temp!
        //words[w].insert(l) --> words[w]=l

        for(int i = 0; i < s.size(); i++){
            char c = s[i];

            if(isalpha(c)){
                w.push_back(tolower(c));
            }else if(!w.empty()){
                words[w].insert(l);
                w.clear();
            }
        }
        if(!w.empty()){
            words[w].insert(l);
        }
    }
    //l from 0 to size()-1

    const IntSet& findword(const string& w){
        if(!words.count(w))
            return emptySet;
        return words[w];
    }
};


//if find words
//use:  stringstream ss --> ss >> doc.findword(w);

//if not find
//use:  stringstream ss --> ss >> doc.lines;

vector<string> Lines;
vector<Doc> articles;

//cout << Doc& d --> d.word[i]
ostream& operator << (ostream& os, const IntSet& lines){
    for(IntSet::const_iterator it = lines.begin(); it != lines.end(); it++){
        os << Lines[*it] << endl;
    }
    return os;
}



void GetQuery(const string& q, vector<string>& qWord){
    qWord.clear();
    stringstream ss(q);

    string w;
    while(ss >> w)
        qWord.push_back(w);
}

void query(const vector<string>& qWord){
    const string& A = qWord.front();
    const string& B = qWord.back();

    bool match, first = true;
    stringstream ss;

    if(qWord.size() == 1){
        for(int i = 0; i < articles.size(); i++){
            Doc& dc = articles[i];
            const IntSet& ans = dc.findword(A);
            match = !ans.empty();

            if(!match)
                continue;

            if(first)   first = false;
            else{
                ss << "----------" << endl;
            }
            ss << ans;
        }
    }

    if(qWord.size() == 2){
        for(int i = 0; i < articles.size(); i++){
            Doc& dc = articles[i];
            const IntSet& ans = dc.findword(B);
            match = ans.empty();

            if(!match)
                continue;

            if(first)   first = false;
            else{
                ss << "----------" << endl;
            }

            ss << dc.lines;
        }
    }

    if(qWord.size() == 3){
        for(int i = 0; i < articles.size(); i++){
            Doc& dc = articles[i];
            const IntSet& ansA = dc.findword(A);
            const IntSet& ansB = dc.findword(B);

            if(qWord[1] == "AND"){
                match = ( (!ansA.empty()) && (!ansB.empty()) );
            }else if(qWord[1] == "OR"){
                match = ( (!ansA.empty()) || (!ansB.empty()) );
            }

            if(!match)
                continue;

            IntVec ans(ansA.size()+ansB.size());
            IntVec::iterator last = set_union(ansA.begin(), ansA.end(), ansB.begin(), ansB.end(), ans.begin());
            //set_union return the last element



            if(first)   first = false;
            else{
                ss << "----------" << endl;
            }

            // output!
            for(IntVec::iterator it = ans.begin(); it != last; it++)
                ss << Lines[*it] << endl;
        }
    }

    const string& res = ss.str();
    if(res.empty())     cout << "Sorry, I found nothing." << endl;

    cout << res << "==========" << endl;
}

int main(){
    ios::sync_with_stdio(false);
    int N,M;
    string line;

    // get articles
    cin >> N;   getline(cin,line);
    articles.resize(N);

    for(int i = 0; i < N; i++){
        Doc& dc = articles[i];
        while(true){
            getline(cin,line);
            if(line == "**********") break;

            Lines.push_back(line);
            dc.addline(line,Lines.size()-1);
        }
    }

    cin >> M;   getline(cin,line);
    //fresh cin
    vector<string> qword;
    for(int i = 0; i < M; i++){
        getline(cin,line);
        GetQuery(line,qword);
        query(qword);
    }
}