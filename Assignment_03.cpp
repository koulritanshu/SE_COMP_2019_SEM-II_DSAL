#include <iostream>
using namespace std;

class Node{
    int data;
    Node*left;
    Node*right;
    bool rflag;
    bool lflag;
public:
    Node(int x){
        data = x;
        lflag = true;
        rflag = true;
        left = NULL;
        right = NULL;
    }    
    friend class TBST;
};

class TBST{
    Node* dummy;
    Node* root;
public:
    TBST(){
        dummy->data = -1;
        root = NULL;
        dummy->left = root;
        dummy->lflag = false;
        dummy->right = dummy;
    }
    void insert(int x){
        Node* newNode = new Node(x);
        if(root == NULL){
            root = newNode;
            root->left = dummy;
            root->right = dummy;
            return;
        }
        Node* curr = root;
        while(true){
            if(curr->data > x){
                if(curr->lflag == false){
                    curr = curr->left;
                }
                else break;
            }
            else if(curr->data < x){
                if(curr->rflag == false){
                    curr = curr->right;
                }
                else break;
            }
            else{
                cout << "Node is already present." << endl;
                return;
            }
        }   
        if(curr->data < x){
            // insert to right of curr
            newNode->left = curr;
            newNode->right = curr->right;
            curr->rflag = false;
            curr->right = newNode;
        }
        else if(curr->data > x){
            // insert to left of curr
            newNode->right = curr;
            newNode->left = curr->left;
            curr->lflag = false;
            curr->left = newNode;
        }
    }
    void inorder(){
        Node* curr = root;
        if(!curr){
            return;
        }
        while(curr != dummy){
            while(curr->lflag == false){
                curr = curr->left;
            }
            cout << curr->data << " ";
            while(curr->rflag){
                curr = curr->right;
                if(curr == dummy){
                    return;
                }
                cout << curr->data << " ";
            }
            curr = curr->right;
        }
    }
    void preorder(){
        Node* curr = root;
        if(!curr){
            return;
        }
        while(curr != dummy){
            while(curr->lflag == false){
                cout << curr->data << " ";
                curr = curr->left;
            }
            cout << curr->data << " ";
            while(curr->rflag){
                curr = curr->right;
                if(curr == dummy){
                    return;
                }
            }
            curr = curr->right;
        }
    }
    void del(int x){
        Node*curr = root;
        Node*parent;
        while(curr && curr->data != x){
            parent = curr;
            if(curr->data > x){
                if(curr->lflag){
                    cout << "Element not present in TBST." << endl;
                    return;
                }
                else curr = curr->left;
            }
            else if(curr->data < x){
                if(curr->rflag){
                    cout << "Element not present in TBST." << endl;
                    return;
                }
                else curr = curr->right;
            }
        }
        if(curr->lflag == true && curr->rflag == true){
            if(curr == root){
                root = NULL;
                delete(curr);
            }
            else if(parent->left == curr){
                parent->left = curr->left;
                parent->lflag = true;
                curr->right = NULL;
                curr->left = NULL;
                delete(curr);
            }
            else if(parent->right == curr){
                parent->right = curr->right;
                curr->left = NULL;
                curr->right = NULL;
                parent->rflag = true;
                delete(curr);
            }
        }
        else if(curr->rflag){
            if(root == curr){
                dummy->left = root->left;
                root = dummy->left;
                if(root->rflag){
                    root->right = dummy;
                }
                if(root->lflag){
                    root->left = dummy;
                }
                delete(curr);
            }
            else{
                if(parent->left == curr){
                    curr->left->right = parent;
                    parent->left = curr->left;
                    curr->left = curr->right = NULL;
                    delete(curr);
                }
                else if(parent->right == curr){
                    parent->right = curr->left;
                    if(curr->left->rflag){
                        curr->left->right = dummy;
                    }
                    delete(curr);
                }
            }
        }
        else if(curr->lflag){
            if(root == curr){
                dummy->left = curr->right;
                root = curr->right;
                if(root->rflag){
                    root->right = dummy;
                }
                if(root->lflag){
                    root->left = dummy;
                }
                delete(curr);
            }
            else if(parent->left == curr){
                parent->left = curr->right;
                if(curr->right->lflag){
                    curr->right->left = dummy;
                }
                delete(curr);
            }
            else if(parent->right == curr){
                curr->right->left = parent;
                parent->right = curr->right;
                delete(curr);
            }
        }
        else if(curr->rflag == false && curr->lflag == false){
            // find inorder successor and save that in temp variable
            // delete inordersuccessor value
            // replace node to delete by the value of inorder successor
            Node* temp = curr->right;
            while(temp->lflag == false){
                temp = temp->left;
            }
            int temp_value = temp->data;
            del(temp_value);
            curr->data = temp_value;
        }
    }
};

int main()
{
    TBST obj;
    while(true){
        cout << "1. Insert an element." << endl;
        cout << "2. Inorder Traversal." << endl;
        cout << "3. Preorder Traversal." << endl;
        cout << "4. Delete an element." << endl;
        cout << "0. Exit" << endl;
        int ch;
        cout << "Make choice: ";
        cin >> ch;
        if(ch == 1){
            int x;
            cout << "Enter value to insert: ";
            cin >> x;
            obj.insert(x);
        }
        else if(ch == 2){
            cout << "----------------------------" << endl;
            obj.inorder();
            cout << endl;
            cout << "----------------------------" << endl;
        }
        else if(ch == 3){
            cout << "----------------------------" << endl;
            obj.preorder();
            cout << endl;
            cout << "----------------------------" << endl;
        }
        else if(ch == 4){
            int x;
            cout << "Enter value you wish to delete: ";
            cin >> x;
            obj.del(x);
        }
        else if(ch == 0){
            cout << "OK!" << endl;
            break;
        }
    }
    return 0;
}