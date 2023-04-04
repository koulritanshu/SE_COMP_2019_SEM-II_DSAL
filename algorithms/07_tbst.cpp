#include <iostream>
using namespace std;

class Node
{
    int data;
    bool lflag = true, rflag = true;
    Node *left = NULL, *right = NULL;

public:
    Node(int x)
    {
        data = x;
    }
    friend class tbst;
};

class tbst
{
    Node *root;
    Node *dummy = new Node(-999);
public:
    tbst()
    {
        dummy->right = dummy;
        root = NULL;
    }
    void insert(int x)
    {
        Node *newNode = new Node(x);
        if (!root)
        {
            root = newNode;
            root->left = dummy;
            root->right = dummy;
            dummy->lflag = false;
            dummy->left = root;
            return;
        }
        Node *curr = root;
        while (true)
        {
            if (curr->data < x)
            {
                // go to right of curr
                if (curr->rflag == false)
                {
                    curr = curr->right;
                }
                else
                    break;
            }
            else if (curr->data > x)
            {
                // go to left of curr
                if (curr->lflag == false)
                {
                    curr = curr->left;
                }
                else
                    break;
            }
            else
            {
                cout << ">> Node already present.\n";
                return;
            }
        }
        if (curr->data > x)
        {
            // add new node to left of curr
            newNode->right = curr;
            newNode->left = curr->left;
            curr->lflag = false;
            curr->left = newNode;
        }
        else
        {
            // add new node to right of curr
            newNode->left = curr;
            newNode->right = curr->right;
            curr->rflag = false;
            curr->right = newNode;
        }
    }
    void inorder()
    {
        Node *temp = root;
        if (!root)
        {
            cout << ">> Tree is empty\n";
            return;
        }
        while (temp != dummy)
        {
            while (temp->lflag == false)
            {
                temp = temp->left;
            }
            cout << temp->data << " ";
            while (temp->rflag)
            {
                temp = temp->right;
                if(temp == dummy){
                    return;
                }
                cout << temp->data << " ";
            }
            temp = temp->right;
        }
    }
    void preorder(){
        Node* temp = root;
        if(!root){
            cout << ">> Tree is empty.\n";
            return;
        }
        while(temp!=dummy){
            while(temp->lflag == false){
                cout << temp->data << " ";
                temp = temp->left;
            }
            cout << temp->data << " ";
            while(temp->rflag){
                temp = temp->right;
                if(temp==dummy){
                    return;
                }
            } 
            temp = temp->right;
        }
    }
    void del(int x){
        Node*curr = root;
        Node*pre;
        while(curr->data != x){
            pre = curr;
            if(curr-> data < x){
                if(curr->rflag){
                    cout << ">> Value not present.\n";
                    return;
                }
                else curr = curr->right;
            }
            else if(curr->data > x){
                if(curr->lflag){
                    cout << ">> Value not present.\n";
                    return;
                }
                else curr = curr->left;
            }
        }
        if(curr->rflag == true && curr->lflag == true){
            Node* lef = curr->left;
            Node* rig = curr->right;
            if(lef->right == curr){
                lef->right = curr->right;
                lef->rflag = true;
                delete(curr);
            }
            else if(rig->left == curr){
                rig->lflag = true;
                rig->left = curr->left;
                delete(curr);
            }
        }
        else if(curr->rflag == false && curr->lflag == true){
            // right node of curr exists
            if(pre->left == curr){
                pre->left = curr->right;
                curr->right->right = pre;
                delete(curr);
            }
            else if(pre->right == curr){
                pre->right = curr->right;
                curr->right->left = pre;
                delete(curr);
            }
        }
        else if(curr->rflag == true && curr->lflag == false){
            // left node of curr exists
            if(pre->left == curr){
                pre->left = curr->left;
                curr->left->right = pre;
                delete(curr);
            }
            else if(pre->right == curr){
                pre->right = curr->left;
                curr->left->left = pre;
                delete(curr);
            }
        }
        else if(curr->lflag == false && curr->rflag == false){
            // both left and right nodes of curr exist
            int tem = 0;
            Node* temp = curr->right;
            while(temp->lflag == false){
                temp = temp->left;
            }
            tem = temp->data;
            del(tem);
            curr->data = tem;
        }
    }
};

int main()
{
    tbst obj;
    obj.insert(10);
    obj.insert(20);
    obj.insert(30);
    obj.insert(40);
    obj.insert(26);
    obj.insert(46);
    obj.insert(36);
    obj.insert(37);
    obj.insert(21);
    obj.insert(15);
    obj.insert(5);
    obj.insert(3);
    obj.insert(4);
    obj.insert(2);
    obj.insert(1);
    obj.inorder();
    cout << endl;
    obj.preorder();
    cout << endl;
    cout << "-------Deleted 15-------" << endl;
    obj.del(15);
    obj.inorder();
    cout << endl;
    obj.preorder();
    cout << endl;
    cout << "-------Deleted 15-------" << endl;
    cout << "-------Deleted 26-------" << endl;
    obj.del(26);
    obj.inorder();
    cout << endl;
    obj.preorder();
    cout << endl;
    cout << "-------Deleted 26-------" << endl;
    cout << "-------Deleted 30-------" << endl;
    obj.del(30);
    obj.inorder();
    cout << endl;
    obj.preorder();
    cout << endl;
    cout << "-------Deleted 30-------" << endl;
    cout << "-------Deleted 1-------" << endl;
    obj.del(1);
    obj.inorder();
    cout << endl;
    obj.preorder();
    cout << endl;
    cout << "-------Deleted 1-------" << endl;
}