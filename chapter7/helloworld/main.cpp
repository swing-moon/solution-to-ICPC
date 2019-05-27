#include <iostream>
#include <cstdio>
#include <cstring>
#include <sstream>

using namespace std;

int main() {
    istringstream is("12");
    int i;
    is >> i;
    cout << i << endl;
}