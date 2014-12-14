//
//  main.cpp
//  AVLTree
//
//  Created by RogerChen on 14/12/13.
//  Copyright (c) 2014年 RogerChen. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <vector>
#include <random>
#include <map>
#include "AVLTree.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    AVLTree avltree;
    map<int, int> mp;
    vector<int> test1;
    vector<int> test2;
    for (int i = 0; i < 1000000; ++i) {
        test1.push_back(i);
        test2.push_back(i);
    }
    shuffle(test1.begin(), test1.end(), mt19937_64(clock()));
    shuffle(test2.begin(), test2.end(), mt19937_64(clock()));
    
    
    auto begin = clock();
    for (int i : test1) {
        avltree.insert(i, i);
    }
    
    for (int i : test2) {
        avltree.remove(i);
    }
    
    auto end = clock();
    
    
    cout << double(end - begin) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    return 0;
}
