//
// Created by zhangmin chen on 2019/2/5.
//

#ifndef NFA_DIRECTEDDFS_H
#define NFA_DIRECTEDDFS_H

#include "Digraph.h"

class DirectedDFS {
public:
    vector<bool> marked;
    int cnt;

    DirectedDFS(Digraph G, int s) : marked(G.V, false), cnt(0) {
        dfs(G, s);
    }

    DirectedDFS(Digraph& G, vector<int>& src) : marked(G.V, false), cnt(0) {
        for(int w : src) {
            if(!marked[w]) dfs(G, w);
        }
    }

    void dfs(Digraph& G, int v) {
        cnt++;
        marked[v] = true;

        for(int w : G.getadj(v)) {
            if(!marked[w]) dfs(G, w);
        }
    }

    bool getmarked(int v) {
        return marked[v];
    }
};

#endif //NFA_DIRECTEDDFS_H
