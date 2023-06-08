#include <iostream>
#include <string>
using namespace std;

class Node{
    string key;
    string meaning;
    Node*left;
    Node*right;
    int ht;
public:
    Node(){
        key = meaning = "";
        ht = 0;
        left = right = NULL;
    }
    friend class AVL;
};

class AVL{
    Node*root;
public:
    AVL(){
        root = NULL;
    }
    Node* rotateright(Node* p){
        Node*q = p->left;
        Node* temp = q->right;
        q->right = p;
        p->left = temp;
        p->ht = height(p);
        q->ht = height(q);
        return q;
    }
    Node* rotateleft(Node* p){
        Node*q = p->right;
        p->right = q->left;
        p->right = q;
        p->ht = height(p);
        q->ht = height(q);
        return q;
    }
    Node* LL(Node* p){
        return p = rotateright(p);
    }
    Node* RR(Node*p){
        return p = rotateleft(p);
    }
    Node* RL(Node* p){
        p->right = rotateright(p->right);
        return p = rotateleft(p);
    }
    Node* LR(Node* p){
        p->left = rotateleft(p->left);
        return p = rotateright(p);
    }
    int height(Node* curr){
        int lh,rh;
        if(!curr){
            return 0;
        }
        if(curr->left == nullptr){
            lh = 0;
        }
        else{
            lh = 1 + curr->left->ht;
        }
        if(curr->right == nullptr){
            rh = 0;
        }
        else{
            rh = 1 + curr->right->ht;
        }
        return max(lh,rh);
    }
    int balancefactor(Node* curr){
        int lh,rh;
        if(!curr) return 0;
        if(curr->left == nullptr){
            lh = 0;
        }
        else{
            lh = 1 + curr->left->ht;
        }
        if(curr->right == nullptr){
            rh = 0;
        }
        else{
            rh = 1 + curr->right->ht;
        }
        return lh-rh;
    }
    Node* inserthelper(Node* node, string key, string meaning){
        if(node == nullptr){
            node = new Node();
            node->key = key;
            node->meaning = meaning;
            return node;
        }
        else{
            if(node->key > key){
                node->left = inserthelper(node->left,key,meaning);
                if(balancefactor(node) == 2){
                    if(node->left->key > key){
                        node = LL(node);
                    }
                    else{
                        node = LR(node);
                    }
                }
            }
            else if(node->key < key){
                node->right = inserthelper(node->right,key,meaning);
                if(balancefactor(node) == -2){
                    if(node->right->key < key){
                        node = RR(node);
                    }
                    else{
                        node = RL(node);
                    }
                }
            }
        }
        node->ht = height(node);
        return node;
    }
    void insert(){
        string key,meaning;
        cout << "Enter the key you wish to add: ";
        cin >> key;
        cout << "Enter the meaninng of the word: ";
        cin >> meaning;
        root = inserthelper(root,key,meaning);
    }
    void inorderhelper(Node* root){
        if(root){
            inorderhelper(root->left);
            cout << "{ " << root->key << ": " << root->meaning << "} ";
            inorderhelper(root->right);
        }
    }
    void inorder(){
        cout << "---------------------" << endl;
        inorderhelper(root);
        cout << endl;
        cout << "---------------------" << endl;
    }
    void update(){
        cout << "Enter the keyword: ";
        string k;
        cin >> k;
        Node* curr = root;
        while(curr){
            if(curr->key > k){
                curr = curr->left;
            }
            else if(curr->key < k){
                curr = curr->right;
            }
            else if(curr->key == k){
                cout << "Old meaning: " << curr->meaning << endl;
                cout << "Enter the new meaning: ";
                string m;
                cin >> m;
                curr->meaning = m;
                inorder();
                return;
            }
        }
        cout << "Word not present" << endl;
    }
    void search(){
        cout << "Enter keyword you wish to search: ";
        string k;
        cin >> k;
        Node*curr = root;
        while(curr){
            if(curr->key > k){
                curr = curr->left;
            }
            else if(curr->key < k){
                curr = curr->right;
            }
            else{
                cout << "-----------------------------" << endl;
                cout << "Word found." << endl;
                cout << "Key: " << curr->key << endl;
                cout << "Meaning: " << curr->meaning << endl;
                cout << "-----------------------------" << endl;
                return;
            }
        }
        cout << "Word not found." << endl;
    }
    void del(){
        cout << "Enter the key you wish to delete: ";
        string k;
        cin >> k;
        root = deleteNode(root,k);
    }
    Node* minvalue(Node* curr){
        while(curr->left){
            curr = curr->left;
        }
        return curr;
    }
    Node* deleteNode(Node* node, string k){
        if(node == NULL){
            return NULL;
        }
        else if(node->key > k){
            node->left = deleteNode(node->left,k);
        }
        else if(node->key<k){
            node->right = deleteNode(node->right,k);
        }
        else{
            if(node->left==NULL&&node->right==NULL){
                node = NULL;
            }
            else if(node->left == NULL){
                node = node->right;
            }
            else if(node->right == NULL){
                node = node->left;
            }
            else{
                Node* temp = minvalue(node->right);
                node->key = temp->key;
                node->meaning = temp->meaning;
                node->right = deleteNode(node->right,temp->key);
            }
        }
        if(node == NULL){
            return node;
        }
        node->ht = height(node);
        int balance = balancefactor(node);
        if(balance>1 && balancefactor(node->left)>=0){
            node = LL(node);
        }
        else if(balance>1 && balancefactor(node->left)<0){
            node = LR(node);
        }
        else if(balance<-1 && balancefactor(node->right)>=0){
            node = RL(node);
        }
        else if(balance<-1 && balancefactor(node->right)<0){
            node = RR(node);
        }
        return node;
    }
};


int main()
{
    AVL obj;
    while(true){
        cout << "0. EXIT" << endl;
        cout << "1. Insert" << endl;
        cout << "2. Display" << endl;
        cout << "3. Search" << endl;
        cout << "4. Delete" << endl;
        int ch;
        cout << "Make your choice: ";
        cin >> ch;
        if(ch == 1){
            obj.insert();
        }
        else if(ch == 2){
            obj.inorder();
        }
        else if(ch == 3){
            obj.search();
        }
        else if(ch == 4){
            obj.del();
        }
        else if(ch == 0){
            cout << "OK!" << endl;
            break;
        }
    }
    return 0;
}