//
//  main.cpp
//  MTA
//
//  Created by zhangmin chen on 2019/4/30.
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

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

void getAddr(const string& str, string& user, string& mta) {
    int k = (int)str.find('@');
    user = str.substr(0, k);
    mta = str.substr(k+1);
}


int main() {
    freopen("input.txt", "r", stdin);
    string str;
    string mta;
    int k;
    string to;
    
    string mtaF, mtaT, userF, userT;
    
    set<string> emails;
    
    while(cin >> str && str[0] != '*') {
        cin >> mta >> k;
        // string to;
        while (k--) {
            // add all address
            cin >> to;
            emails.insert(to + "@" + mta);
        }
    }
    
    // then get all mta
    // for(auto& i : emails) cout << i << endl;
    // for(ssii i = emails.begin(); i != emails.end(); i++) cout << *i << endl;
    
    // we finished all mta input
    
    while(cin >> str && str != "*") {
        getAddr(str, userF, mtaF);
        
        set<string> vis;
        map<string, vector<string> > clents;
        // clents: clients[mtaT] = {usr1, usr2,...}
        
        vector<string> mtaWt;
        
        while(cin >> to && to != "*") {
            // get All mta
            // cout << "dbg: " << to << endl;
            
            //debugS(to);
            
            getAddr(to, userT, mtaT);
            if(vis.count(to)) continue;
            vis.insert(to);
            
            if(!clents.count(mtaT)) {
                mtaWt.push_back(mtaT);
                clents[mtaT] = vector<string>();
            }
            clents[mtaT].push_back(to);
        }
        
        // get all clients
        
        // connection between mtaF --> {mtaWt[0], mtaWt[1]...}
        
        getline(cin, to);
        
        string data;
        while (getline(cin, to) && to[0] != '*') {
            data += "     " + to + "\n";
            // cout << data << endl;
        }
        // cout << data;
        
        // msg finished!
        
        // send msg: mails from str
        // send to:
        // for all mtaWt
        //     vector<stirng> usr = clents[mtaWt[i]]
        //     str -> { usr[0], usr[1]...}
        
        for(int i = 0; i < mtaWt.size(); i++) {
            string mta2 = mtaWt[i];
            vector<string> usrs = clents[mta2];
            
            cout << "Connection between " << mtaF << " and " << mta2 << endl;
            cout << "     HELO " << mtaF << endl;
            cout << "     250\n";
            cout << "     MAIL FROM:<" << str << ">\n";
            cout << "     250\n";
            
            bool canSend = false;
            for(int j = 0; j < usrs.size(); j++) {
                cout << "     RCPT TO:<" << usrs[j] << ">\n";
                if(emails.count(usrs[j])) {
                    canSend = true;
                    cout << "     250\n";
                }
                else cout << "     550\n";
            }
            
            if(canSend) {
                //
                cout << "     DATA\n";
                cout << "     354\n";
                cout << data;
                cout << "     .\n";
                cout << "     250\n";
                
            }
            cout << "     QUIT\n";
            cout << "     221\n";
        }
        
        
        
    
        
        // we get all msg, then close connection
    }
}
