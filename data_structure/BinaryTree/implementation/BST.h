//
// Created by speit on 18-11-13.
//
#ifndef BST_H_
#define BST_H_

#include <iostream>
#include <cassert>

#include "BTPN.h"

using namespace std;

template <typename Key, typename E>
class BinarySearchTree: public BinaryTreeNode<Key, E> {
private:
    BinaryTreeNode<Key, E>* root;
    int num_of_nodes;

    void private_clear(BinaryTreeNode<Key, E>* root){
        if(root == NULL) return;
        this->clear(this->get_left_node_ptr());
        this->clear(this->get_right_node_ptr());
        delete root;
        this->num_of_nodes -= 1;
        assert(this->num_of_nodes >= 0);
    }

    BinaryTreeNode<Key, E>* private_find(BinaryTreeNode<Key, E>* root, Key& key) const {
        if(root == NULL) {
            cout << "Record with key \"" << key <<  "\" Not Found." << endl;
            return root;
        }
        else if(root->get_key() > key) this->private_find(root->get_left_node_ptr(), key);
        else if(root->get_key() < key) this->private_find(root->get_right_node_ptr(), key);
        else {
            cout << "Found " << key << " at address " << root << "." << endl;
            return root;
        }
    }

    void private_insert(BinaryTreeNode<Key, E>*& root, Key& key, E& value) {
        if(root == NULL) {
            root = new BinaryTreeNode<Key, E>;
            root->set_value(value);
            root->set_key(key);
            this->num_of_nodes += 1;
            return;
        }
        else if(key < root->get_key()) {
            if(root->get_left_node_ptr() == NULL) {
                BinaryTreeNode<Key, E>* left_node_ptr = new BinaryTreeNode<Key, E>;
                root->set_left_node_ptr(left_node_ptr);
                root->get_left_node_ptr()->set_key(key);
                root->get_left_node_ptr()->set_value(value);
                this->num_of_nodes += 1;
                return;
            }
            BinaryTreeNode<Key, E>* left_node_ptr = root->get_left_node_ptr();
            this->private_insert(left_node_ptr, key, value);
            return;
        }
        else if(key >= root->get_key()) {
            if(root->get_right_node_ptr() == NULL) {
                BinaryTreeNode<Key, E>* right_node_ptr = new BinaryTreeNode<Key, E>;
                root->set_right_node_ptr(right_node_ptr);
                root->get_right_node_ptr()->set_key(key);
                root->get_right_node_ptr()->set_value(value);
                this->num_of_nodes += 1;
                return;
            }
            BinaryTreeNode<Key, E>* right_node_ptr = root->get_right_node_ptr();
            this->private_insert(right_node_ptr, key, value);
            return;
        }
        // else if(key == root->get_key()) cout << "Record with key \"" << key << "\" already exist!" << endl;
    }
public:
    BinarySearchTree() {
        this->num_of_nodes = 0;
        this->root = NULL;
    }

    int get_nodes_number() { return this->num_of_nodes; }

    BinaryTreeNode<Key, E>* get_root() const { return this->root; }

    void clear(BinaryTreeNode<Key, E>* root) { this->private_clear(root); }

    BinaryTreeNode<Key, E>* find(Key& key) const { return this->private_find(this->root, key); }

    void insert(Key& key, E& value) { this->private_insert(this->root, key, value); }

    void remove(Key& key) {
        BinaryTreeNode<Key, E> node_found = this->find(key);
        if(node_found == NULL) cout << "Key \"" << key << "\" not found!" << endl;
        else {
            this->clear(node_found);
        }
    }

};

#endif