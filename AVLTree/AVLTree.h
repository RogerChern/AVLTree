//
//  AVLTree.h
//  AVLTree
//
//  Created by RogerChen on 14/12/13.
//  Copyright (c) 2014年 RogerChen. All rights reserved.
//

#ifndef AVLTree_AVLTree_h
#define AVLTree_AVLTree_h

class AVLTree {
private:
    struct Node {
        Node *parent = nullptr;
        Node *left   = nullptr;
        Node *right  = nullptr;
        int height   = 0;
        int key;
        int value;
        
        Node(int k, int val) :
            key(k),
            value(val) { }
    };
    Node *_root = nullptr;
    static constexpr int ALLOWED_IMBALANCE = 1;
    
private:
    Node * search(int key) {
        Node *x = _root;
        while (x != nullptr) {
            if (key > x -> key) {
                x = x -> right;
            }
            else if (key < x -> key) {
                x = x -> left;
            }
            else {
                return x;
            }
        }
        return x;
    }
    void insert(Node *n) {
        if (_root == nullptr) {
            _root = n;
            return;
        }
        Node *iter = _root;
        Node *pos  = _root;
        while (iter != nullptr) {
            pos = iter;
            if (n -> value >= iter -> value) {
                iter = iter -> right;
            }
            else {
                iter = iter -> left;
            }
        }
        if (pos -> value >= n -> value) {
            pos -> left = n;
        }
        else {
            pos -> right = n;
        }
        n -> parent = pos;
        balance(n -> parent);
    }
    
    void remove(Node *n) {
        if (n -> left == nullptr) {
            transplant(n, n -> right);
            balance(n -> parent);
        }
        else if (n -> right == nullptr) {
            transplant(n, n -> left);
            balance(n -> parent);
        }
        else {
            Node *suc = findMin(n -> right);
            if (suc == n -> right) {
                transplant(n, suc);
                suc -> left = n -> left;
                suc -> left -> parent = suc;
                balance(suc);
            }
            else {
                Node *x = suc -> parent;
                transplant(suc, suc -> right);
                transplant(n, suc);
                suc -> left = n -> left;
                suc -> left -> parent = suc;
                suc -> right = n -> right;
                suc -> right -> parent = suc;
                balance(x);
            }
        }
    }
    
    Node * findMin(Node *n) {
        Node *x = n;
        Node *px = n;
        while (x != nullptr) {
            px = x;
            x = x -> left;
        }
        return px;
    }
    
    void transplant(Node *x, Node *y) {
        if (x -> parent == nullptr) {
            _root = y;
        }
        else if (x == x -> parent -> left) {
            x -> parent -> left = y;
        }
        else {
            x -> parent -> right = y;
        }
        if (y != nullptr) {
            y -> parent = x -> parent;
        }
    }
    
    int height(Node *n) {
        return (n == nullptr) ? -1 : n -> height;
    }
    
    void balance(Node *n) {
        while (n != nullptr) {
            if (height(n -> left) - height(n -> right) > ALLOWED_IMBALANCE) {
                if (height(n -> left -> left) > height(n -> left -> right))
                    rotateWithLeft(n);
                else
                    doubleRotateWithLeft(n);
            }
            else if (height(n -> right) - height(n -> left) > ALLOWED_IMBALANCE) {
                if (height(n -> right -> right) > height(n -> right -> left))
                    rotateWithRight(n);
                else
                    doubleRotateWithRight(n);
            }
            n -> height = std::max(height(n -> left), height(n -> right)) + 1;
            n = n -> parent;
        }
    }
    
    void rotateWithLeft(Node *n) {
        Node *lchild = n -> left;
        if (n -> parent == nullptr) {
            _root = lchild;
        }
        else if (n == n -> parent -> left) {
            n -> parent -> left = lchild;
        }
        else {
            n -> parent -> right = lchild;
        }
        lchild -> parent = n -> parent;
        n -> left = lchild -> right;
        if (n -> left != nullptr) {
            n -> left -> parent = n;
        }
        lchild -> right = n;
        n -> parent = lchild;
    }
    
    void rotateWithRight(Node *n) {
        Node *rchild = n -> right;
        if (n -> parent == nullptr) {
            _root = rchild;
        }
        else if (n == n -> parent -> left) {
            n -> parent -> left = rchild;
        }
        else {
            n -> parent -> right = rchild;
        }
        rchild -> parent = n -> parent;
        n -> right = rchild -> left;
        if (n -> right != nullptr) {
            n -> right -> parent = n;
        }
        rchild -> left = n;
        n -> parent = rchild;
    }
    
    void doubleRotateWithLeft(Node *n) {
        --n -> left -> height;
        rotateWithRight(n -> left);
        rotateWithLeft(n);
    }
    
    void doubleRotateWithRight(Node *n) {
        --n -> right -> height;
        rotateWithLeft(n -> right);
        rotateWithRight(n);
    }
public:
    void insert(int k, int v) {
        Node *n = new Node(k, v);
        insert(n);
    }
    
    void remove(int k) {
        Node *x = search(k);
        if (x != nullptr) {
            remove(x);
        }
    }
};

#endif
