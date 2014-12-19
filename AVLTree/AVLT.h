//
//  AVLT.h
//  AVLTree
//
//  Created by RogerChen on 14/12/18.
//  Copyright (c) 2014年 RogerChen. All rights reserved.
//

#ifndef AVLTree_AVLT_h
#define AVLTree_AVLT_h

#include <algorithm>

class AVLT {
    using key_type   = int;
    using value_type = int;
    
    struct Node {
        Node *left   = nullptr;
        Node *right  = nullptr;
        int height = 0;
        key_type key;
        value_type value;
        
        Node(key_type k, key_type val) :
            key(k),
            value(val) { }
    };
    Node *root = nullptr;
    constexpr static int ALLOWED_IMBALANCE = 1;
    
    //this is not a case of tail recursion
    void insert(Node *&x, key_type key, value_type value) {
        if (x == nullptr) {
            x = new Node(key, value);
        }
        else if (key > x -> key) {
            insert(x -> right, key, value);
        }
        else {
            insert(x -> left, key, value);
        }
        balance(x);
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

    //this is not a case of tail recursion
    void remove(Node *&x, key_type key) {
        if (x == nullptr) {
            return;
        }
        if (key > x -> key) {
            remove(x -> right, key);
        }
        else if (key < x -> key) {
            remove(x -> left, key);
        }
        else {
            if (x -> left != nullptr && x -> right != nullptr) {
                Node *suc = findMin(x -> right);
                x -> key = suc -> key;
                x -> value = suc -> value;
                remove(x -> right, suc -> key);
            }
            else {
                Node *temp = x;
                x = x -> left == nullptr ? x -> right : x -> left;
                delete temp;
            }
        }
        balance(x);
    }
    
    int height(Node *x) {
        return x == nullptr ? -1 : x -> height;
    }
    
    void balance(Node *&x) {
        if (x == nullptr) {
            return;
        }
        if (height(x -> left) - height(x ->right) > ALLOWED_IMBALANCE) {
            if (height(x -> left -> left) > height(x -> left -> right)) {
                rotateWithLeft(x);
            }
            else {
                doubleRotateWithLeft(x);
            }
        }
        else if (height(x -> right) - height(x -> left) > ALLOWED_IMBALANCE) {
            if (height(x -> right -> right) > height(x -> right -> left)) {
                rotateWithRight(x);
            }
            else {
                doubleRotateWithRight(x);
            }
        }
        x -> height = std::max(height(x -> left), height(x -> right)) + 1;
    }

    void rotateWithLeft(Node *&x) {
        Node *lchild = x -> left;
        x -> left = lchild -> right;
        lchild -> right = x;
        x -> height = std::max(height(x -> left), height(x -> right)) + 1;
        lchild -> height = std::max(height(lchild -> left), height(lchild -> right)) + 1;
        x = lchild;
    }
    
    void rotateWithRight(Node *&x) {
        Node *rchild = x -> right;
        x -> right = rchild -> left;
        rchild -> left = x;
        x -> height = std::max(height(x -> left), height(x -> right)) + 1;
        rchild -> height = std::max(height(rchild -> left), x -> height) + 1;
        x = rchild;
    }
    
    void doubleRotateWithLeft(Node *&x) {
        rotateWithRight(x -> left);
        rotateWithLeft(x);
    }
    
    void doubleRotateWithRight(Node *&x) {
        rotateWithLeft(x -> right);
        rotateWithRight(x);
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
