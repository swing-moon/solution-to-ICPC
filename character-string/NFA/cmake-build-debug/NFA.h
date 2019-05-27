//
// Created by zhangmin chen on 2019/2/5.
//

#ifndef NFA_NFA_H
#define NFA_NFA_H

#include <cassert>
#include "DirectedDFS.h"

class NFA {
public:
    //
    NFA(string regexp) : regexp(regexp), m(regexp.length()) {
        //
        graph = new Digraph(m+1);
        stack<int> stk;

        for(int i = 0; i < m; i++) {
            int lp = i;
            if(regexp[i] == '(' || regexp[i] == '|')
                stk.push(i);
            else if(regexp[i] == ')') {
                //
                int or_ = stk.top(); stk.pop();

                if(regexp[or_] == '|') {
                    //
                    lp = stk.top(); stk.pop();
                    graph->addEdge(lp, or_+1);
                    graph->addEdge(or_, i);

                }
                else lp = or_;
            }


            // single character, 1-char lookahead
            if(i < m-1 && regexp[i+1] == '*') {
                graph->addEdge(lp, i+1);
                graph->addEdge(i+1, lp);
            }
            if(regexp[i] == '(' || regexp[i] == ')' || regexp[i] == '*')
                graph->addEdge(i, i+1);
        }
        if(stk.size() != 0)
            throw invalid_argument("Invalid regular expression");
    }

    ~NFA() { delete(graph); }

    // return true if the text is matched by the regular expression
    bool recognizes(string txt) {
        DirectedDFS *dfs = new DirectedDFS(*graph, 0);
        forward_list<int> pc;
        for(int i = 0; i < graph->V; i++) {
            if(dfs->getmarked(i)) pc.push_front(i);
        }

        for(int i = 0; i < txt.length(); i++) {
            //
            if(txt[i] == '*' || txt[i] == '|' || txt[i] == '(' || txt[i] == ')')
                throw runtime_error("text contains the metacharacter '" + to_string(txt[i]) + "'");

            forward_list<int> match;
            for(int v : pc) {
                if(v == m) continue;
                if((txt[i] == regexp[v]) || regexp[v] == '.')
                    match.push_front(v+1);
            }


            auto tmp = dfs;
            vector<int> nxt(match.begin(), match.end());
            dfs = new DirectedDFS(*graph, nxt);
            delete (tmp);
            pc.clear();

            for(int v = 0; v < graph->V; v++) {
                if(dfs->getmarked(v)) pc.push_front(v);
            }

            if(distance(pc.begin(), pc.end()) == 0) return false;
        }

        for(int v : pc) if(v == m)
            return true;
        return false;
    }

private:
    Digraph *graph;
    string regexp;
    int m;
};

#endif //NFA_NFA_H
