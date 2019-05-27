//
// Created by zhangmin chen on 2019/2/12.
//

#ifndef TRIEST_TRIEST_H
#define TRIEST_TRIEST_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stdexcept>
#include <cassert>
#include <algorithm>

using namespace std;

class TrieST {
private:
    class Node {
    public:
        Node() : next(256, nullptr), val(0), flag(false) {}
        ~Node() {
            for(int i = 0; i < R; i++) if(next[i])
                delete(next[i]);
        }

        int val;
        bool flag;
        vector<Node *> next;
    };

public:
    // int main() to create!
    TrieST() : n(0), root(nullptr) {}
    ~TrieST() { delete(root); }

    int get(string key) {
        if(key.empty()) throw invalid_argument("argument to get() is null");
        Node* x = get(root, key, 0);
        if(x == nullptr) throw runtime_error("Without this key");
        return x->val;
    }

    void put(string key, int val) {
        if(key.empty()) throw invalid_argument("first argument to put() is null");
        else root = put(this->root, key, val, 0);
    }

    string longestPrefixOf(string query) {
        if(query.empty()) throw invalid_argument("argument to longestPrefixOf() is null");
        int length = longestPrefixOf(root, query, 0, -1);
        if(length == -1) return "";
        else return query.substr(0, length);
    }

    queue<string> keysWithPrefix(string pre) {
        queue<string> res;
        Node* x = get(root, pre, 0);
        collect(x, pre, res);
        return res;
    }

    queue<string> keysMatch(string pat) {
        queue<string> res;
        collect(root, "", pat, res);
        return res;
    }

    void delete_(string key) {
        if(key.empty()) throw invalid_argument("argument to delete() is null");
        root = delete_(root, key, 0);
    }

    int size() { return n; }
    bool isempty() { return size() == 0; }
    queue<string> keys() {
        return keysWithPrefix("");
    }
    bool contains(string key) {
        if(key.empty()) throw invalid_argument("argument to contains() is null");
        return get(root, key, 0) != nullptr;
    }


private:
    Node* get(Node* x, string key, int d) {
        if(x == nullptr) return nullptr;
        if(d == key.length()) return x;
        char c = key[d];
        return get(x->next[c], key, d+1);

        // c = key[0] begin searching
        // start:  get(key[0], key, 1)
        // root is just a node without message
    }

    Node* put(Node* x, string key, int val, int d) {
        if(x == nullptr) x = new Node();
        if(d == key.length()) {
            x->val = val;  x->flag = true;
            return x;
        }
        char c = key[d];
        x->next[c] = put(x->next[c], key, val, d+1);
        return x;
    }

    void collect(Node* x, string pre, queue<string>& res) {
        if(x == nullptr) return;
        if(x->flag) res.push(pre);

        for(unsigned char c = 0; ; c++) {
            pre.push_back(c);
            collect(x->next[c], pre, res);
            pre.pop_back();
            if(c == R-1) break;
        }
    }
    void collect(Node* x, string pre, string pat, queue<string>& res) {
        if(x == nullptr) return;
        int d = pre.length();
        if(d == pat.length() && x->flag) res.push(pre);
        // 遇到x->flag, 进队列
        if(d == pat.length()) return;

        char c = pat[d];
        if(c == '.') {
            //
            for(unsigned char ch = 0; ; ch++) {
                pre.push_back(ch);
                collect(x->next[ch], pre, pat, res);
                pre.pop_back();

                if(ch == R-1) break;
            }
        } else {
            pre.push_back(c);
            collect(x->next[c], pre, pat, res);
            pre.pop_back();
        }
    }

    int longestPrefixOf(Node* x, string query, int d, int length) {
        if(x == nullptr) return length;
        if(x->flag) length = d;
        if(d == query.length()) return length;

        char c = query[d];
        return longestPrefixOf(x->next[c], query, d+1, length);
    }

    Node* delete_(Node* x, string key, int d) {
        if(x == nullptr) return nullptr;
        if(d == key.length()) {
            if(x->flag) n--;
            x->flag = false;
        } else {
            char c = key[d];
            x->next[c] = delete_(x->next[c], key, d+1);
        }

        // remove subtrie rooted at x if it is completely empty
        if(x->flag) return x;
        for(int c = 0; c < R; c++) if(x->next[c] != nullptr)
            return x;
        return nullptr;

        // in recur, x->next[c] = nullptr, fix the bug of Leaking memory
    }

private:
    static const int R;
    Node* root;     // root of trie
    int n;          // number of keys in trie
};

const int TrieST::R = 256;

#endif //TRIEST_TRIEST_H
