//
//  main.cpp
//  LA5169
//
//  Created by zhangmin chen on 2019/5/18.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;
typedef long long llong;
typedef set<string>::iterator ssii;
typedef set<int>::iterator si;


#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

class Book {
public:
    string title, author;
    Book(string title_ = "", string author_ = "") : title(title_), author(author_) {}
    
    bool operator< (const Book& rhs) const {
        return author < rhs.author || (author == rhs.author && title < rhs.title);
    }
};

map<string, int> idx;
vector<Book> books;

class Cmp {
public:
    bool operator() (const int& lhs, const int& rhs) const {
        return books[lhs] < books[rhs];
    }
};

set<int, Cmp> libs, pools;

void borrow(const string& bKName) {
    int id = idx[bKName];
    if(libs.count(id)) libs.erase(id);
    else pools.erase(id);
}
void retBook(const string& bkName) {
    int id = idx[bkName];
    pools.insert(id);
}

void shelve() {
    //
    for(si i = pools.begin(); i != pools.end(); i++) {
        //
        int id = *i;
        si p = libs.insert(id).first;
        if(p == libs.begin()) {
            // first
            cout << "Put " << books[id].title << " first" << endl;
        }
        else {
            p--;
            int pid = *p;
            cout << "Put " << books[id].title << " after " << books[pid].title << endl;
        }
    }
    pools.clear();
    cout << "END" << endl;
}

void init() {
    idx.clear();
    books.clear();
    pools.clear();
    libs.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    string line;
    init();
    while (true) {
        getline(cin, line);
        if(line == "END") break;
        int p = (int)line.find(" by ");
        string title = line.substr(0, p);
        string author = line.substr(p+4);
        
        int id = (int)books.size();
        idx[title] = id;
        books.push_back(Book(title, author));
    }
    
    // then we finished get all books
    _for(i, 0, books.size()) libs.insert(i);
    
    string cmd, title;
    while(true) {
        getline(cin, line);
        if(line == "END") break;
        
        cmd = line.substr(0, 6);
        if(cmd[0] == 'S') shelve();
        else {
            title = line.substr(cmd.size()+1);
            if(cmd[0] == 'B') borrow(title);
            else retBook(title);
        }
    }
}
