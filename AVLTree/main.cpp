//
//  main.cpp
//  AVLTree
//
//  Created by RogerChen on 14/12/13.
//  Copyright (c) 2014年 RogerChen. All rights reserved.
//

#include <iostream>
#include <ctime>
#include "AVLTree.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    AVLTree avltree;
    auto begin = clock();
    for (int i = 0; i < 1000000; ++i) {
        avltree.insert(i, i);
    }
    auto end = clock();
    
    cout << double(end - begin) / CLOCKS_PER_SEC << "ms" << endl;
    return 0;
}
