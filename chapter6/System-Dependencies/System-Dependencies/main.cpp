//
//  main.cpp
//  System-Dependencies
//
//  Created by zhangmin chen on 2018/8/12.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <map>
#include <sstream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 10000;
int status[maxn];
vector<int> depend[maxn];
vector<int> father[maxn];
// father is a mark! mark the dependencies before item

map<string, int> name2id;
string name[maxn];
vector<int> installed;
int cnt = 0;

void list() {
    for(int i = 0; i < installed.size(); i++)
        cout << "   " << name[installed[i]] << "\n";
}

int ID(const string& item) {
    if(!name2id.count(item)) {
        name[++cnt] = item;
        name2id[item] = cnt;
    }
    return name2id[item];
    // item 0 indicates none item! / status[0] means NIL!
}

void install(int item, bool category) {
    if(!status[item]) {
        for(int i = 0; i < depend[item].size(); i++)
            install(depend[item][i], false);
        
        cout << "   Installing " << name[item] << "\n";
        status[item] = category ? 1 : 2;
        // 1 means expicitly installed, 2 means implicitly installed
        installed.push_back(item);
    }
}

bool needed(int item) {
    for(int i = 0; i < father[item].size(); i++)
        if(status[father[item][i]])    return true;
    return false;
}

void cleanitem(int item, bool category) {
    if((category || status[item] == 2) && !needed(item)) {
        status[item] = 0;
        installed.erase(remove(installed.begin(), installed.end(), item), installed.end());
        cout << "   Removing " << name[item] << "\n";
        for(int i = 0; i < depend[item].size(); i++)
            // another way to clean
            cleanitem(depend[item][i], false);
    }
}

int main() {
    string line, cmd;
    memset(status, 0, sizeof(status));
    
    while(getline(cin, line)) {
        cout << line << "\n";
        stringstream ss(line);
        ss >> cmd;
        
        if(cmd[0] == 'E')   break;
        string item1, item2;
        if(cmd[0] == 'L')   list();
        else {
            ss >> item1;
            int i1 = ID(item1);
            if(cmd[0] == 'D') {
                while(ss >> item2) {
                    int i2 = ID(item2);
                    depend[i1].push_back(i2);
                    father[i2].push_back(i1);
                }
            }
            else if(cmd[0] == 'I') {
                if(status[i1])  cout << "   " << item1 << " is already installed.\n";
                else install(i1, true);
            }
            else {
                // removed!
                if(!status[i1])  cout << "   " << item1 << " is not installed.\n";
                else if(needed(i1))  cout << "   " << item1 << " is still needed.\n";
                else cleanitem(i1, true);
            }
        }
    }
}

/*
 note: usage:
 #include <algorithm>
 #include <string>
 #include <iostream>
 #include <cctype>
 
 int main()
 {
    std::string str1 = "Text with some   spaces";
    str1.erase(std::remove(str1.begin(), str1.end(), ' '), str1.end());
    std::cout << str1 << '\n';
 
    std::string str2 = "Text\n with\tsome \t  whitespaces\n\n";
    str2.erase(std::remove_if(str2.begin(), str2.end(), [](unsigned char x){return std::isspace(x);}),str2.end());
    std::cout << str2 << '\n';
 
 }

 output: Textwithsomespaces
         Textwithsomewhitespaces

 */
