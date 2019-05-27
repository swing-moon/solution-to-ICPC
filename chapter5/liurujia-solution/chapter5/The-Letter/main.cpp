#include <iostream>
#include <cstdio>
#include <cstring>
#include <map>
#include <vector>
#include <set>

using namespace std;

string s,mem;
string user1,mta1,user2,mta2;
set<string> addr;
int k;

void read_mta(){
    s.clear();
    mem.clear();
    addr.clear();

    while(cin >> s && s != "*"){
        cin >> s >> k;
        while(k--){
            cin >> mem;
            addr.insert(mem + "@" + s);
        }
    }
}


void read_address(const string& str, string& user, string& mta){
    int k = str.find('@');
    user = str.substr(0,k);
    mta = str.substr(k+1);
}


void read_rcpt(){
    while(cin >> s && s != "*"){
        read_address(s,user1,mta1);

        set<string> tmp;
        map<string, vector<string> > dest;
        vector<string> rcpt_mta;

        //rcpt_mta[i] = mta2
        //dest[mta2] = xxx@xxx

        while(cin >> mem && mem != "*"){
            read_address(mem,user2,mta2);
            if(tmp.count(mem)) continue;
            tmp.insert(mem);

            if(!dest.count(mta2)){
                rcpt_mta.push_back(mta2);
                dest[mta2] = vector<string>();
            }
            dest[mta2].push_back(mem);
        }

        //get data;
        getline(cin,mem);

        string data;
        while(getline(cin,mem) && mem[0] != '*'){
            data += "     "+mem+"\n";
        }

        for(int i = 0; i < rcpt_mta.size(); i++){
            string mta_rcp = rcpt_mta[i];
            vector<string> rcpt_users = dest[mta_rcp];

            cout << "Connection between " << mta1 << " and " << mta_rcp << endl;
            cout << "     HELO " << mta1 << "\n";
            cout << "     250\n";
            cout << "     MAIL FROM:<" << s << ">\n";
            cout << "     250\n";

            bool ok = false;
            for(int i = 0; i < rcpt_users.size(); i++){
                cout << "     RCPT TO:<" << rcpt_users[i] << ">\n";
                if(addr.count(rcpt_users[i])){
                    ok = true;
                    cout << "     250\n";
                }else{
                    cout << "     550\n";
                }
            }

            if(ok){
                cout << "     DATA\n";
                cout << "     354\n";
                cout << data;
                cout << "     .\n";
                cout << "     250\n";
            }
            cout << "     QUIT\n";
            cout << "     221\n";
        }
    }
}

int main(){
    read_mta();
    read_rcpt();
}