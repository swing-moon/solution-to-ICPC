//
//  main.cpp
//  helloworld
//
//  Created by zhangmin chen on 2018/11/1.
//  Copyright © 2018 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;
// float tmp;

const float& fn2(float r) {
    float tmp = r*r*3.14;
    return tmp;
}


int main() {
    float c = fn2(5.0);
    printf("%lf\n", c);
    
    float* d = &c;
    printf("%lf\n", *d);
}
