#ifndef _BST_H_
#define _BST_H_

#include <iostream>
using namespace std;

class Node {
    public:
        Node() { left = right = NULL;}
        Node(int val) { 
            left = right = NULL;
            data = val;
        }
        Node *left;
        Node *right;
        int data;
};

class BST {

    public:
        BST() { root = NULL; }

        ~BST() 
        {
            if (root != NULL)
                release(root);
        }
        void postorder() const {
            if (root == NULL) 
                return;
            postorder(root);
            cout << endl;
        }
        void inorder() const {
            if (root == NULL) 
                return;
            inorder(root);
            cout << endl;
        }
    
        void insert(int val) {
            if (root == NULL) 
                root = new Node(val);
            else
                insert(root, val);
        }

        /*BONUS: DELETE FUNCION*/
        void erase(int val) {
        
            if(val == root->data)
            {
                if(root->right == NULL && root->left == NULL){
                    delete root;
                    root = NULL;
                    return;
                }
                if(root->right == NULL){
                    Node* tmp = root;
                    tmp = tmp->left;
                    delete root;
                    root = tmp;
                    return;
                }
                else if(root->left == NULL){ //for 1-degree nodes
                    Node* tmp = root;
                    tmp = tmp->right;
                    delete root;
                    root = tmp;
                    return;
                }
            }
            Node* target = root;
            Node* parent = root;
            bool left_child; // no need to init; if the target is parent's left child(true)
            
            //while loop binary search, find target's address
            while(true)
            {
                if(val == target->data)
                    break;
                parent = target;
                if(val < target->data)
                {
                    if(target->left == NULL)
                    {
                        cerr << "ERROR: target not found." << endl;
                        return;                  
                    }
                    target = target->left;
                    left_child = true;
                }
                else
                {
                    if(target->right == NULL)
                    {
                        cerr << "ERROR: target not found." << endl;
                        return;                  
                    }
                    target = target->right;
                    left_child = false;
                }
            }
            if(target->left == NULL && target->right == NULL) //case: leaf node
            {
                if(left_child) parent->left = NULL;
                else parent->right = NULL;
                
                delete target;
                return;
            }
            if(target->right == NULL) //case: 1-degree node
            {
                if(left_child)parent->left = target->left;
                else parent->right = target->left;
            }
            else if(target->left == NULL) //case: 1-degree node
            {
                if(left_child)parent->left = target->right;
                else parent->right = target->right;
            }
            else    
            {   // replacing with its "successor" for 2-degree nodes
                // e.g.the minimum node of the right subtree (keep going left).
                Node* _root = target;
                parent = target;
                target = target->right;
                if(target->left == NULL)
                { 
                    swap(_root->data, target->data);
                    parent->right = (target->right == NULL) ? NULL : target->right;
                }
                else
                {
                    while(target->left != NULL)
                    {
                        parent = target;
                        target = target->left;
                    }
                    swap(_root->data, target->data);
                    parent->left = (target->right == NULL) ? NULL : target->right; 
                }
            }
            delete target;
            return;
        }
    protected:
        
        Node *root;
        // p cannot be NULL
        void release(Node* p) {
            if (p->left != NULL)
                release(p->left);
            if (p->right != NULL)
                release(p->right);
            delete p;
        }

        void postorder(Node* p) const {
            if (p->left != NULL)
                postorder(p->left);
            if (p->right != NULL)
                postorder(p->right);
            cout << p->data << " ";
        }
    
        // p cannot be NULL
        void inorder(Node* p) const {
            if (p->left != NULL)
                inorder(p->left);
            cout << p->data << " ";
            if (p->right != NULL)
                inorder(p->right);
        }

        // p cannot be NULL
        void insert(Node* p, int val) {

            if (p->data > val) {
                // left
                if (p->left == NULL) 
                    p->left = new Node(val);
                else 
                    insert(p->left, val);
            }
            else {
                //right
                if (p->right == NULL) 
                    p->right = new Node(val);
                else 
                    insert(p->right, val);
            }
        }

};

#endif
