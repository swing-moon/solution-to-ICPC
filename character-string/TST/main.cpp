#include "./cmake-build-debug/TST.h"

#include <fstream>

int main() {
    freopen("input.txt", "r", stdin);

    string tmp;
    int cnt = 0;
    TST tst;
    while(cin >> tmp) {
        //
        tst.put(tmp, cnt++);
    }

    if(tst.size() < 100) {
        cout << "keys(\"\"):" << endl;
        auto res = tst.keys();
        while(!res.empty()) {
            cout << res.front() << endl;
            res.pop();
        }
        cout << endl;
    }

    cout << "longestPrefixOf(\"shellsort\"):" << endl;
    cout << tst.longestPrefixOf("shellsort") << endl;
    cout << endl;

    cout << "longestPrefixOf(\"quicksort\"):" << endl;
    cout << tst.longestPrefixOf("quicksort") << endl;
    cout << endl;

    cout << "keysWithPrefix(\"shor\"):" << endl;
    auto res = tst.keysWithPrefix("shor");
    while(!res.empty()) {
        cout << res.front() << endl;
        res.pop();
    }
    cout << endl;

    cout << "keysThatMatch(\".he.l.\"):" << endl;
    auto res2 = tst.keysThatMatch(".he.l.");
    while(!res2.empty()) {
        cout << res2.front() << endl;
        res2.pop();
    }
    cout << endl;
}