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
    Node *root_ = nullptr;
    static constexpr int ALLOWED_IMBALANCE = 1;
    
private:
    Node * search(Node *t, int key) {
        Node *x = root_;
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
        if (root_ == nullptr) {
            root_ = n;
            return;
        }
        Node *x = root_;
        Node *px  = root_;
        while (x != nullptr) {
            px = x;
            if (n -> key >= x -> key) {
                x = x -> right;
            }
            else {
                x = x -> left;
            }
        }
        if (px -> key >= n -> key) {
            px -> left = n;
        }
        else {
            px -> right = n;
        }
        n -> parent = px;
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
    
    Node * findMin(Node *x) {
        if (x == nullptr) {
            return nullptr;
        }
        while (x -> left != nullptr) {
            x = x -> left;
        }
        return x;
    }
    
    void transplant(Node *x, Node *y) {
        if (x -> parent == nullptr) {
            root_ = y;
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
            root_ = lchild;
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
            root_ = rchild;
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
        Node *x = search(x, k);
        if (x != nullptr) {
            remove(x);
        }
    }
    int search(int key) {
        return search(root_, key) -> value;
    }

};

#endif
