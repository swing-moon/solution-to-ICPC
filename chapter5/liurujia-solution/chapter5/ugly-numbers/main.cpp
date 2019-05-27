#include <iostream>
#include <cstdio>
#include <queue>
#include <vector>
#include <set>

using namespace std;
typedef long long llong;
const int factor[3] = {2,3,5};

int main(){
    priority_queue<llong, vector<llong>, greater<llong> > pq;
    set<llong> val;
    pq.push(1);
    val.insert(1);

    for(int i = 1; ; i++){
        llong x = pq.top();
        pq.pop();

        if(i == 1500){
            cout << "The 1500'th ugly number is " << x << ".\n";
            break;
        }

        for(int j = 0; j < 3; j++){
            llong tmp = x*factor[j];
            if(!val.count(tmp)){
                val.insert(tmp);
                pq.push(tmp);
            }
        }
    }
}