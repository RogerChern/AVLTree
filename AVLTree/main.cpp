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
#include <algorithm>
#include <random>
#include <map>
#include "AVLTree.h"
#include "AVLT.h"
#include "BST.h"

using namespace std;

int main(int argc, const char * argv[]) {
    BST tree;
    map<int, int> mp;
    vector<int> test1;
    vector<int> test2;
    vector<int> result;
    for (int i = 0; i < 1000000; ++i) {
        test1.push_back(i);
        test2.push_back(i);
    }
    shuffle(test1.begin(), test1.end(), mt19937_64(clock()));
    shuffle(test2.begin(), test2.end(), mt19937_64(clock()));   
    
    for (int i : test1) {
        tree.insert(i, i);
    }
    
    auto begin = clock();
    
    for (int i : test2) {
        result.push_back(tree.search(i));
    }
    
    auto end = clock();
    
    for (int i : test2) {
        tree.remove(i);
    }
    
    cout << double(end - begin) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
    return 0;
}
