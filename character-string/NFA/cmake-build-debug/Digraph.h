//
// Created by zhangmin chen on 2019/2/5.
//

#ifndef NFA_DIGRAPH_H
#define NFA_DIGRAPH_H

#include <forward_list>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <stack>
#include <sstream>
#include <cassert>

using namespace std;

class Digraph {
public:
    int V, E;
    vector<forward_list<int> > adj;
    vector<int> indegree;

    Digraph(int V) : V(V), E(0), adj(V), indegree(V) {
        if(V < 0) throw runtime_error("Number of vertices in a graph must be nonnegative");
    }

    void addEdge(int from, int to) {
        adj[from].push_front(to);
        indegree[from]++;
        E++;
    }

    forward_list<int> getadj(int v) const {
        //
        return adj[v];
    }
};

#endif //NFA_DIGRAPH_H
