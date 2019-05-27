#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct book{
    string title, author;
    book(const string& t, const string& a):title(t),author(a) {}

    bool operator< (const book& rhs) const {
        return author < rhs.author || (author == rhs.author && title < rhs.title);
    }
};

vector<book> Allbooks;
struct cmp{
    bool operator () (const int& lhs, const int& rhs) const{
        return Allbooks[lhs] < Allbooks[rhs];
    }
};
set<int,cmp> shelf,lib;
map<string,int> bookindex;

void borrow(const string& b){
    int idx = bookindex[b];
    if(lib.count(idx))
        lib.erase(idx);
    else
        shelf.erase(idx);
}

void retbook(const string& b){
    int idx = bookindex[b];
    shelf.insert(idx);
}

void shelved(){
    for(set<int>::iterator it = shelf.begin(); it != shelf.end(); it++){
        int idx = *it;
        set<int>::iterator pit = lib.insert(idx).first;

        if(pit == lib.begin())
            cout << "Put " << Allbooks[idx].title << " first" << endl;
        else{
            pit--;
            cout << "Put " << Allbooks[idx].title << " after " << Allbooks[*pit].title << endl;
        }
    }

    shelf.clear();
    cout << "END" << endl;
}

int main(){
    string buf;
    while(true){
        getline(cin,buf);
        if(buf == "END") break;
        int pos = buf.find(" by ");
        string title = buf.substr(0,pos);
        string author = buf.substr(pos+4);

        int idx = Allbooks.size();
        bookindex[title] = idx;
        Allbooks.push_back(book(title,author));
    }
    for(int i = 0; i < Allbooks.size(); i++){
        lib.insert(i);
    }

    string cmd, title;
    while(true){
        getline(cin,buf);
        if(buf == "END")    break;
        cmd = buf.substr(0,6);
        if(cmd[0] == 'S')   shelved();
        else{
            title = buf.substr(cmd.size()+1);
            if(cmd[0] == 'B')   borrow(title);
            else{
                retbook(title);
            }
        }
    }
}