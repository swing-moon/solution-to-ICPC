#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <set>
#include <map>
#include <cmath>

using namespace std;
const double eps = 1e-7;

struct point{
    double x, y;
    point(double x = 0, double y = 0):x(x),y(y) {}
};

int dcmp(double x){
    if(fabs(x) < eps)
        return 0;
    return x < 0 ? -1 : 1;
}

int Minus(double x, double y){
    return dcmp(x-y);
}

point operator+ (const point& A, const point& B){
    return point(A.x+B.x, A.y+B.y);
}
point operator- (const point& A, const point& B){
    return point(A.x-B.x, A.y-B.y);
}
point operator* (const point& A, double p){
    return point(A.x*p, A.y*p);
}
istream& operator>> (istream& is, point& A){
    return is >> A.x >> A.y;
}

double dot(const point& A, const point& B){
    return A.x*B.x + A.y*B.y;
}
double dist(const point& A, const point& B){
    return dot(A-B, A-B);
}
double length(const point& A){
    return sqrt(dot(A, A));
}

bool inRange(double x, double l, double r){
    if(Minus(l, r) > 0)
        return inRange(x, r, l);
    return Minus(l, x) <= 0 && Minus(x, r) <= 0;
}

bool inArea(const point& p, const point& l, const point& r){
    return inRange(p.x, l.x, r.x) && inRange(p.y, r.y, l.y);
}

struct graph{
    string name;
    point corner1, corner2, center, lowright;
    double height, width, area, minx, ratio;

    void init(){
        center = (corner1 + corner2) * .5;
        width = fabs(corner1.x - corner2.x);
        height = fabs(corner1.y - corner2.y);
        ratio = fabs(height/width - 0.75);
        area = height * width;
        lowright.x = center.x + width/2;
        lowright.y = center.y - height/2;
        minx = center.x - width/2;
    }
};

vector<graph> allgraphs;
map<string, point> gIndex;

struct graphCmp{
    point loc;

    bool operator() (int i1, int i2){
        const graph& g1 = allgraphs[i1];
        const graph& g2 = allgraphs[i2];

        int d;

        d = Minus(g1.area, g2.area);
        if(d > 0)   return true;
        if(d < 0)   return false;

        d = Minus(dist(loc, g1.center), dist(loc, g2.center));
        if(d > 0)   return true;
        if(d < 0)   return false;

        d = Minus(g1.ratio, g2.ratio);
        if(d > 0)   return true;
        if(d < 0)   return false;

        d = Minus(dist(loc, g1.lowright), dist(loc, g2.lowright));
        if(d < 0)   return true;
        if(d > 0)   return false;

        d = Minus(g1.minx, g2.minx);
        if(d > 0)   return true;
        if(d < 0)   return false;

    }
};

void getGraph(const point p, vector<int>& gID, vector<int>& level){
    gID.clear();
    graphCmp gc;
    gc.loc = p;

    for(int i = 0; i < allgraphs.size(); i++){
        const graph& g = allgraphs[i];
        if(inArea(p, g.corner1, g.corner2)){
            gID.push_back(i);
        }
//        cout << " IN Area: " << inArea(p, g.corner1, g.corner2) << " ";
    }

//    cout << " allgraphs size: " << allgraphs.size() << endl;

    sort(gID.begin(), gID.end(), gc);
//    cout << "gID size : "<< gID.size() << endl;
    level.clear();
    level.assign(gID.size(),1);
//    cout << " level size : " << gID.size() << endl;

    for(int i = 0; i < gID.size(); i++){
        if(i == 0)  continue;

        const graph& g = allgraphs[gID[i]];
        const graph& pg = allgraphs[gID[i-1]];

        int d = Minus(g.area, pg.area);
        level[i] = level[i-1];
        if(d < 0)   level[i]++;

//        cout << "name: " << g.name << " ,area: " << g.area << " , level: " << level[i] << endl;
    }
}

void doRequest(const string& name, int qlevel){
    cout << name << " at detail level " << qlevel;

    if(!gIndex.count(name)){
        cout << " unknown location" << endl;
        return;
    }

    vector<int> gID, levels;
    getGraph(gIndex[name], gID, levels);

    /*for(int i = 0; i < levels.size(); i++)
        cout << levels[i] << " ";
    cout << endl;*/

    if(gID.empty()){
        cout << " no map contains that location" << endl;
        return;
    }

    int maxlevel = levels.back();
    if(maxlevel < qlevel){
        cout << " no map at that detail level; using " << allgraphs[gID.back()].name << endl;
    }else{
        vector<int>::iterator it = upper_bound(levels.begin(), levels.end(), qlevel);
        int p = it-levels.begin();

        cout << " using " << allgraphs[gID[p-1]].name << endl;
    }
}

int main(){
    string buf;
    getline(cin, buf);
    while(true){
        graph g;
        cin >> g.name;
        if(g.name == "LOCATIONS")   break;
        cin >> g.corner1 >> g.corner2;

        g.init();
        allgraphs.push_back(g);
    }
    /*for(int i = 0; i < allgraphs.size(); i++){
        graph& g = allgraphs[i];
        cout << g.corner1.x  << "," << g.corner1.y << "  " << g.corner2.x << "," << g.corner2.y << endl;
        cout << g.center.x << "," << g.center.y << endl;
    }*/

    point loc;
    string name;
    while(true){
        cin >> name;
        if(name == "REQUESTS")  break;
        cin >> loc;
        gIndex[name] = loc;
    }

    while(true){
        cin >> name;
        if(name == "END")   break;
        int level;
        cin >> level;
        doRequest(name, level);
    }
    return 0;
}