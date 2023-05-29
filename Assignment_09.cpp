#include <iostream>
using namespace std;

class Node{
    int data;
    Node* left;
    Node* right;
    int ht;
public:
    Node(){
        data = 0;
        left = right = NULL;
        ht = 0;
    }
    friend class AVL;
};


class AVL{
    Node* root;
public:
    AVL(){
        root = NULL;
    }
    Node* rotateright(Node* p){
        Node* q = p->left;
        p->left = q->right;
        q->right = p;
        q->ht = height(q);
        p->ht = height(p);
        return q;
    }
    Node* rotateleft(Node* p){
        Node*q = p->right;
        p->right = q->left;
        q->left = p;
        q->ht = height(q);
        p->ht = height(p);
        return q;
    }
    Node* RR(Node *node){
        node = rotateleft(node);
        return node;
    }
    Node* LL(Node* node){
        node = rotateright(node);
        return node;
    }
    Node* RL(Node* node){
        node->right = rotateright(node->right);
        node = rotateleft(node);
        return node;
    }
    Node* LR(Node* node){
        node->left = rotateleft(node->left);
        node = rotateright(node);
        return node;
    }
    int height(Node* node){
        int lh,rh;
        if(node == NULL){
            return 0;
        }
        if(node->left == NULL){
            lh = 0;
        }
        else{
            lh = 1 + node->left->ht;
        }
        if(node->right == NULL){
            rh = 0;
        }
        else{
            rh = 1 + node->right->ht;
        }
        return max(lh,rh);
    }
    int balancefactor(Node* node){
        int lh,rh;
        if(node == NULL){
            return 0;
        }
        if(node->left == NULL){
            lh = 0;
        }
        else{
            lh = 1 + node->left->ht;
        }
        if(node->right == NULL){
            rh = 0;
        }
        else{
            rh = 1 + node->right->ht;
        }
        return lh - rh;
    }
    Node* inserthelper(int data, Node* node){
        if(node == NULL){
            node = new Node();
            node->data = data;
            return node;
        }
        else{   
            if(data > node->data){
                node->right = inserthelper(data,node->right);
                if(balancefactor(node) == -2){
                    if(data > node->right->data){
                        // rr case
                        node = RR(node);
                    }
                    else{
                        // rl case
                        node = RL(node);
                    }
                }
            }
            else{
                node->left = inserthelper(data,node->left);
                if(balancefactor(node) == 2){
                    if(data > node->left->data){
                        // lr case
                        node = LR(node);
                    }
                    else{
                        // ll case
                        node = LL(node);
                    }
                }
            }
        }
        node->ht = height(node);
        return node;
    }
    void inorderhelper(Node *tree)
    {
        if (tree == NULL)
        {
            return;
        }
        else
        {
            inorderhelper(tree->left);
            cout << tree->data << "\n";
            inorderhelper(tree->right);
        }
    }
    void inorder()
    {
        inorderhelper(root);
        // cout << endl;
    }
    void insert(){
        int n;
        cout << ">> Enter the number of entries: ";
        cin >> n;
        for(int i=0;i<n;i++){
            cout << ">> Enter the value " << i + 1 << ": ";
            int x;
            cin >> x;
            root = inserthelper(x,root);
        }
    }
    Node* getRoot(){
        return root;
    }
};

int main(){
    AVL obj;
    obj.insert();
    obj.inorder();
}