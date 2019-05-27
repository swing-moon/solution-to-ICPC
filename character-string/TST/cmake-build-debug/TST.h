//
// Created by zhangmin chen on 2019/2/13.
//

#ifndef TST_TST_H
#define TST_TST_H

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <queue>

using namespace std;

class TST {
private:
    class Node {
    public:
        // construction
        Node() : left(nullptr), mid(nullptr), right(nullptr), isString(false) {}
        ~Node() {
            if(left) delete(left);
            if(right) delete(right);
            if(mid) delete(mid);
        }

        unsigned char c;
        bool isString;
        Node *left, *mid, *right;
        int val;
    };

public:
    // construction
    TST() : n(0), root(nullptr) {}
    ~TST() { delete(root); }

    int size() { return n; }
    bool contains(string key) {
        if(key.empty()) {
            throw invalid_argument("argument to contains() is null!");
        }
        return get(root, key, 0) != nullptr;
    }

    int get(string key) {
        if(key.empty()) throw invalid_argument("calls get() with null argument");
        Node *x = get(root, key, 0);
        if(x == nullptr) throw runtime_error("This key not int this table");
        return x->val;
    }

    void put(string key, int val) {
        if(key.empty()) throw invalid_argument("calls put() with null key");
        if(!contains(key)) n++;
        root = put(root, key, val, 0);
    }

    string longestPrefixOf(string query) {
        if(query.length() == 0) return "";
        int len = 0;
        Node* x = root;

        int i = 0;
        while(i < query.length() && x != nullptr) {
            char ch = query[i];
            if(ch < x->c) x = x->left;
            else if(ch > x->c) x = x->right;
            else {
                i++;
                if(x->isString) len = i;
                x = x->mid;
            }
        }

        return query.substr(0, len);
    }

    queue<string> keys() {
        queue<string> que1;
        string tmp = "";
        collect(root, tmp, que1);
        return que1;
    }

    queue<string> keysWithPrefix(string pre) {
        if(pre.empty()) throw invalid_argument("calls keysWithPrefix() with null argumemnt");

        queue<string> que2;
        Node *x = get(root, pre, 0);

        if(x == nullptr) return que2;
        if(x->isString) que2.push(pre);
        collect(x->mid, pre, que2);
        return que2;
    }

    queue<string> keysThatMatch(string pat) {
        queue<string> que;
        string pre = "";
        collect(root, pre, 0, pat, que);
        return que;
    }

private:
    Node *get(Node *x, string key, int d) {
        if(x == nullptr) return nullptr;
        if(key.length() == 0) throw invalid_argument("key must have length >= 1");
        unsigned char ch = key[d];

        if(ch < x->c) return get(x->left, key, d);
        else if(ch > x->c) return get(x->right, key, d);
        else if (d < key.length()-1) return get(x->mid, key, d+1);
        else return x;
    }

    Node *put(Node *x, string key, int val, int d) {
        char ch = key[d];
        if(x == nullptr) {
            x = new Node(); x->c = ch;
        }

        if(ch < x->c) x->left = put(x->left, key, val, d);
        else if(ch > x->c) x->right = put(x->right, key, val, d);
        else if(d < key.length()-1) x->mid = put(x->mid, key, val, d+1);
        else {
            x->val = val; x->isString = true;
        }
        return x;
    }

    void collect(Node *x, string& pre, queue<string>& res) {
        if(x == nullptr) return;
        collect(x->left, pre, res);
        if(x->isString) {
            pre.push_back(x->c); res.push(pre); pre.pop_back();
            // find prefix
        }

        pre.push_back(x->c);
        collect(x->mid, pre, res);
        pre.pop_back();

        collect(x->right, pre, res);
    }

    void collect(Node *x, string& pre, int d, const string& pat, queue<string>& res) {
        if(x == nullptr) return;
        char ch = pat[d];

        if(ch == '.' || ch < x->c) collect(x->left, pre, d, pat, res);
        if(ch == '.' || ch == x->c) {
            if(d == pat.length()-1 && x->isString) {
                pre.push_back(x->c);
                res.push(pre);
            }
            if(d < pat.length()-1) {
                pre.push_back(x->c);
                collect(x->mid, pre, d+1, pat, res);
                pre.pop_back();
            }
        }
        if(ch == '.' || ch > x->c) collect(x->right, pre, d, pat, res);
    }


private:
    int n;
    Node* root;
};

#endif //TST_TST_H
