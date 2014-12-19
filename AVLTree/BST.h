//
//  BST.h
//  AVLTree
//
//  Created by RogerChen on 14/12/18.
//  Copyright (c) 2014年 RogerChen. All rights reserved.
//

#ifndef AVLTree_BST_h
#define AVLTree_BST_h

class BST {
    using key_type   = int;
    using value_type = int;
    
    struct Node {
        Node *parent = nullptr;
        Node *left   = nullptr;
        Node *right  = nullptr;
        key_type key;
        value_type value;
        
        Node(key_type k, value_type val) :
        key(k),
        value(val) { }
    };
    Node *root = nullptr;
    
    Node * search(Node *x, key_type key) {
        if (x == nullptr) {
            return nullptr;
        }
        if (key > x -> key) {
            return search(x -> right, key);
        }
        else if (key < x -> key) {
            return search(x -> left, key);
        }
        else {
            return x;
        }
    }
    
    void insert(Node *&x, key_type key, value_type value) {
        if (x == nullptr) {
            x = new Node(key, value);
        }
        else if (key > x -> key) {
            return insert(x -> right, key, value);
        }
        else {
            return insert(x -> left, key, value);
        }
    }
    
    Node * findMin(Node *x) {
        if (x == nullptr) {
            return nullptr;
        }
        while (x -> left != nullptr) {
            x = x -> left;
        }
        return x;
    }
    
    void remove(Node *&x, key_type key) {
        if (x == nullptr) {
            return;
        }
        if (key > x -> key) {
            return remove(x -> right, key);
        }
        else if (key < x -> key) {
            return remove(x -> left, key);
        }
        else {
            if (x -> left == nullptr) {
                Node *temp = x;
                x = x -> right;
                delete temp;
            }
            else if (x -> right == nullptr) {
                Node *temp = x;
                x = x -> left;
                delete temp;
            }
            else {
                Node *temp = x;
                x = findMin(x);
                delete temp;
            }
        }
    }
    
public:
    void insert(key_type key, value_type value) {
        insert(root, key, value);
    }
    
    void remove(key_type key) {
        remove(root, key);
    }
    
    value_type search(key_type key) {
        return search(root, key) -> value;
    }
};

#endif
