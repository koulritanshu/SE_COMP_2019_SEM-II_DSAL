#include <iostream>
using namespace std;

class Node{
    int data;
    Node*left=NULL,*right=NULL;
public:
    Node(int x){
        data = x;
    }
    friend class bst;
};

class bst{
    Node *root;
public:
    bst(){
        root = NULL;
    }
    void insert(int x){
        Node* newNode = new Node(x);
        if(!root){
            root = newNode;
            return;
        }
        Node* curr = root;
        while(true){
            if(curr->data < x){
                // go to right of curr
                if(curr->right){
                    curr = curr->right;
                }
                else{
                    curr->right = newNode;
                    return;
                }
            }
            else if(curr->data > x){
                // go to left of curr
                if(curr->left){
                    curr = curr->left;
                }
                else{
                    curr->left = newNode;
                    return;
                }
            }
            else if(curr->data == x){
                return;
            }
        }
    }
    void inorder(Node*curr){
        if(curr){
            inorder(curr->left);
            cout << curr->data << " ";
            inorder(curr->right);
        }
    }
    Node*getRoot(){
        return root;
    }
};

int main(){
    bst obj;
    obj.insert(50);
    obj.insert(51);
    obj.insert(52);
    obj.insert(40);
    obj.insert(45);
    obj.insert(23);
    obj.insert(100);
    obj.inorder(obj.getRoot());
}

