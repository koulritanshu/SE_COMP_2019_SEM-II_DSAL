#include <iostream>
#define MAX 30
using namespace std;

class Node{
    int data;
    Node*left;
    Node*right;
public:
    Node(){
        data = 0;
        left = NULL;
        right = NULL;
    }
    friend class OBST;
};

class OBST{
    int p[MAX],q[MAX];
    int cost[MAX][MAX],weight[MAX][MAX],root[MAX][MAX];
    int keys[MAX];
    int n;
    Node*head;
public:
    OBST(){
        head = NULL;
        for(int i=0;i<MAX;i++){
            p[i] = 0;
            q[i] = 0;
            keys[i] = 0;
            for(int j=0;j<MAX;j++){
                cost[i][j] = 0;
                weight[i][j] = 0;
                root[i][j] = 0;
            }
        }
    }
    void input(){
        cout << "Enter the number of keys: ";
        cin >> n;
        for(int i=1;i<=n;i++){
            cout << "Enter key at index " << i << ": ";
            cin >> keys[i];
            cout << "Enter the successful probability: ";
            cin >> p[i];
        }
        for(int i=0;i<=n;i++){
            cout << "Enter the unsuccessful probability " << i << ": ";
            cin >> q[i];
        }
    }
    int w(int i, int j){
        if(i==j){
            return q[i];
        }
        return weight[i][j-1] + p[j] + q[j];
    }   
    int getcost(int i,int j){
        if(i==j){
            return 0;
        }
        else{
            int mini = 10000;
            int root_val;
            for(int k=i+1;k<=j;k++){
                int current = cost[i][k-1] + cost[k][j];
                if(mini > current){
                    mini = current;
                    root_val = k;
                }
            }
            root[i][j] = root_val;
            return mini + weight[i][j];    
        }
    }
    void min_cost(){
        for(int c=0;c<=n;c++){
            for(int i=0,j=c;i<=n&&j<=n;i++,j++){
                weight[i][j] = w(i,j);
                cost[i][j] = getcost(i,j);
            }
        }
        cout << "Minimum Cost: " << cost[0][n]/weight[0][n] << endl;
    }
    Node* buildTree(Node* node, int i, int j){
        if(i >= j){
            return NULL;
        }
        else{
            node = new Node();
            node->data = keys[root[i][j]];
            node->left = buildTree(node->left,i,root[i][j]-1);
            node->right = buildTree(node->right,root[i][j],j);
            return node;
        }
    }
    void create(){
        head = buildTree(head,0,n);
    }
    void inorderhelper(Node* curr){
        if(curr){
            inorderhelper(curr->left);
            cout << curr->data << " ";
            inorderhelper(curr->right);
        }
    }
    void inorder(){
        cout << "------------------------" << endl;
        inorderhelper(head);
        cout << endl;
        cout << "------------------------" << endl;
    }
};

int main()
{
    OBST obj;
    while(true){
        cout << "0. Exit" << endl;
        cout << "1. Input." << endl;
        cout << "2. Minimum Cost." << endl;
        cout << "3. Create Tree" << endl;
        int ch;
        cout << "Make choice: ";
        cin >> ch;
        if(ch == 0){
            cout << "OK!" << endl;
            break;
        }
        else if(ch == 1){
            obj.input();
        }
        else if(ch == 2){
            obj.min_cost();
        }
        else if(ch == 3){
            obj.create();
            obj.inorder();
        }
    }
    return 0;
}