//
//  main.cpp
//  AVLTree
//
//  Created by RogerChen on 14/12/13.
//  Copyright (c) 2014年 RogerChen. All rights reserved.
//

#include <iostream>
#include "AVLTree.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    AVLTree avltree;
    for (int i = 0; i < 100000; ++i) {
        avltree.insert(i, i);
    }
    return 0;
}
