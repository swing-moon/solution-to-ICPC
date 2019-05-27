#include <iostream>
#include "cmake-build-debug/NFA.h"

int main() {
    freopen("input.txt", "r", stdin);
    string regexp, txt;
    cin >> regexp >> txt;

    NFA nfa(regexp);
    if(nfa.recognizes(txt)) cout << "matched!" << endl;
    else cout << "failed!" << endl;
}