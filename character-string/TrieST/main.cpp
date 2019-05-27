#include "./cmake-build-debug/TrieST.h"
#include <fstream>

int main() {
    freopen("input.txt", "r", stdin);
    string tmp;
    int cnt = 0;
    TrieST st;

    while(cin >> tmp) {
        // cout << tmp << endl;
        st.put(tmp, cnt++);
    }

    if(st.size() < 100) {
        cout << "keys(\"\"):" << endl;
        auto res = st.keys();
        while(!res.empty()) {
            cout << res.front() << " " << st.get(res.front()) << endl;
            res.pop();
        }
        cout << endl;
    }

    cout << "longestPrefixOf(\"shellsort\"):" << endl;
    cout << st.longestPrefixOf("shellsort") << endl;
    cout << endl;

    cout << "longestPrefixOf(\"quicksort\"):" << endl;
    cout << st.longestPrefixOf("quicksort") << endl;
    cout << endl;

    cout << "keyWithPrefix(\"shor\"):" << endl;
    auto res = st.keysWithPrefix("shor");
    while(!res.empty()) {
        cout << res.front() << endl;
        res.pop();
    }
    cout << endl;

    cout << "keysThatMatch(\".he.l.\"):" << endl;
    auto res2 = st.keysMatch(".he.l.");
    while(!res2.empty()) {
        cout << res2.front() << endl;
        res2.pop();
    }
    cout << endl;
}