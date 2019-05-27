#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <sstream>
#include <math.h>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;

struct order{
    string cmd;
    int size, price;

    order(string str, int s = 0, int p = 0) : cmd(str), size(s), price(p) {}
};

map<int, set<int> > buypq, sellpq;
map<int, int> buytab, selltab;
vector<order> R;

void trade(int flag){
    while(!buypq.empty() && !sellpq.empty()){
        if(buypq.rbegin()->first >= sellpq.begin()->first){
            set<int>& buy_s = buypq.rbegin()->second;
            set<int>& sell_s = sellpq.begin()->second;
            int bid = *buy_s.begin(); int sid = *sell_s.begin();

            int cur = min(R[bid].size, R[sid].size);
            printf("TRADE %d %d\n", cur, flag ? R[bid].price : R[sid].price);
            R[bid].size -= cur; R[sid].size -= cur;
            //first!

            buytab[R[bid].price] -= cur; selltab[R[sid].price] -= cur;
            //second!

            if(R[bid].size == 0)    buy_s.erase(bid);
            if(R[sid].size == 0)    sell_s.erase(sid);
            if(buy_s.size() == 0)   buypq.erase(R[bid].price);
            if(sell_s.size() == 0)  sellpq.erase(R[sid].price);
            //third: 1、delete set  2、 check if set.size()==0? yes! delete price

        } else {
            return;
        }
    }
}

void print(){
    while(buytab.size() && buytab.rbegin()->second <= 0){
        buytab.erase(buytab.rbegin()->first);
    }
    while(selltab.size() && selltab.begin()->second <= 0){
        selltab.erase(selltab.begin()->first);
    }

    printf("QUOTE ");

    if(buytab.size()){
        printf("%d %d", buytab.rbegin()->second, buytab.rbegin()->first);
    } else {
        printf("0 0");
    }
    cout << " - ";

    if(selltab.size()){
        printf("%d %d", selltab.begin()->second, selltab.begin()->first);
    } else {
        printf("0 99999");
    }

    cout << endl;
}

int main(){
    int n, kase = 0;
    string cmd;

    while(scanf("%d", &n) == 1){
        if(kase++)  cout << endl;
        buypq.clear();  sellpq.clear();
        buytab.clear(); selltab.clear();
        R.clear();

        int size, price, id;
        for(int i = 0; i < n; i++){
            cin >> cmd;
            if(cmd == "BUY"){
                cin >> size >> price;
                R.push_back(order("BUY", size, price));

                buypq[price].insert(i);
                buytab[price] += size;
                trade(0);

            } else if (cmd == "SELL") {
                cin >> size >> price;
                R.push_back(order("SELL", size, price));

                sellpq[price].insert(i);
                selltab[price] += size;
                trade(1);

            } else if (cmd == "CANCEL") {
                cin >> id;  id--;
                R.push_back(order("CANCEL", id, 0));

                if(R[id].cmd == "BUY"){
                    buypq[R[id].price].erase(id);
                    if(buypq[R[id].price].size() == 0){
                        buypq.erase(R[id].price);
                    }

                    buytab[R[id].price] -= R[id].size;

                    R[id].size = 0;

                } else if (R[id].cmd == "SELL"){
                    sellpq[R[id].price].erase(id);
                    if(sellpq[R[id].price].size() == 0){
                        sellpq.erase(R[id].price);
                    }

                    selltab[R[id].price] -= R[id].size;

                    R[id].size = 0;
                }
            }

            print();
        }
    }
}