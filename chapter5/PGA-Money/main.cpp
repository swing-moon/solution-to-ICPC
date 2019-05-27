#include <algorithm>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <sstream>
#include <iomanip>

using namespace std;
const int maxn = 145;
const int n_cut = 70;
double sum,pri[maxn];
int n,pos;

struct player{
    string name;
    double prize;
    bool amateur,t;
    int rnd[4];
    int pre,tot;
    int dq;
    int rank;
}p[maxn];

bool cmp1(const player& a, const player& b){
    if(a.dq > -3 && b.dq > -3)
        return a.pre < b.pre;
    return a.dq > b.dq;
}

bool cmp2(const player& a, const player& b){
    if(a.dq != b.dq)
        return a.dq > b.dq;
    if(a.tot != b.tot)
        return a.tot < b.tot;
    return a.name < b.name;
}

void init_pri(){
    memset(p,0, sizeof(p));
    scanf("%lf",&sum);

    for(int i = 0; i < 70; i++){
        scanf("%lf",&pri[i]);
        pri[i] = pri[i]/100.0*sum;
    }
}

int str2num(const string& str){
    int val = 0;
    for(string::const_iterator it = str.begin(); it != str.end(); it++){
        val = val*10 + (*it-'0');
    }
    return val;
}

void init(){
    scanf("%d",&n);
    string s;
    getline(cin,s);

    for(int i = 0; i < n; i++){
        getline(cin,s);

        p[i].name = s.substr(0,20);
        s = s.substr(20);

        if(p[i].name.find('*') != string::npos){
            p[i].amateur = true;
        }

        istringstream is(s);
        for(int j = 0; j < 4; j++){
            is >> s;

            if(s == "DQ"){
                p[i].dq = j-4;
                break;
            }else{
                p[i].rnd[j] = str2num(s);
            }

            if(j < 2)
                p[i].pre += str2num(s);
            p[i].tot += str2num(s);
        }
    }
}

void print(){
    for(int i = 0; i < n; i++){
        cout << p[i].name << " ";
        for(int j = 0; j < 4; j++)
            cout << p[i].rnd[j] << " ";

        cout << p[i].dq << " " << p[i].amateur << " ";
        cout << p[i].pre << " " << p[i].tot << " ";

        cout << endl;
    }
}

void solve(){
    sort(p,p+n,cmp1);
    pos = 0;

    while(pos < min(70,n) && p[pos].dq > -3)    ++pos;
    while(p[pos].dq > -3 && p[pos].pre == p[pos-1].pre) pos++;

    sort(p,p+pos,cmp2);

    //get money!
    int k = 0, rank = 0, pro_rk = 0;
    while(k < pos){
        if(p[k].dq)
            break;

        //[k...cur) are the same score!
        int cur = k, cnt = 0;
        double sum = 0.0;
        while(!p[cur].dq && p[cur].tot == p[k].tot){
            if(!p[cur].amateur){
                sum += pri[pro_rk+cnt];
                cnt++;
            }
            cur++,rank++;
        }
        sum /= cnt;

        //now, p[cur].rank = rank;

        for(int i = k; i < cur; i++){
            p[i].rank = rank-(cur-k)+1;
            if(pro_rk > 69){
                p[i].amateur = true;
                p[i].t = false;
            }
            // No.1 include 70 people, all amateur!
            if(!p[i].amateur){
                p[i].prize = sum;
                p[i].t = cnt > 1;
            }
        }

        k = cur - 1, k++;
        pro_rk += cnt;
    }
}

void print_ans(){
    printf("Player Name          Place     RD1  RD2  RD3  RD4  TOTAL     Money Won\n");
    printf("-----------------------------------------------------------------------\n");

    for(int i = 0; i < pos; i++){
        printf("%-21s",p[i].name.c_str());
        //%-21s左对齐
//        cout.setf(ios::left);
//        cout << setw(21)<< p[i].name;
        if(p[i].dq)
            printf("          ");
        else{
            char t[5];
            sprintf(t,"%d%c",p[i].rank, p[i].t?'T':' ');
            printf("%-10s",t);
        }

        for(int j = -4; j < p[i].dq; j++)   printf("%-5d",p[i].rnd[j+4]);
        for(int j = p[i].dq; j < 0; j++)    printf("     ");

        if(p[i].dq)
            printf("%s","DQ");
        else if(!p[i].amateur)
            printf("%-10d",p[i].tot);
        else
            printf("%d",p[i].tot);

        if(p[i].dq || p[i].amateur){
            printf("\n");
            continue;
        }
        printf("$%9.2lf\n",p[i].prize);
    }
}

int main(){
    int kase;
    scanf("%d",&kase);
    while(kase--){
        init_pri();
        init();
        solve();
        print_ans();
        if(kase)    printf("\n");
    }
    return 0;
}