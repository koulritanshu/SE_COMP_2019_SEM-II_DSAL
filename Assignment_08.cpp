#include <iostream>
#include <string>
using namespace std;
#define MAX 50

class Node{
    int val;
    Node* left;
    Node* right;
public:
    Node(){
        val = 0;
        left = right = NULL;
    }
    friend class OBST;
};

class opti{
    int cost, weight, value;
    friend class OBST;
public:
    opti(){
        cost = weight = value = 0;
    }
};

class OBST{
    int key[MAX],p[MAX],q[MAX],cost,n;
    opti arr[MAX][MAX];
public:
    OBST(){
        for(int i=0;i<MAX;i++){
            n = 0;
            key[i] = 0;
            p[i] = 0;
            q[i] = 0;
        }
    }
    void input(){
        cin >> n;
        cin >> q[0];
        for(int i=1;i<n;i++){
            cin >> key[i] >> p[i] >> q[i];
        }
    }
    int w(int i, int j){
        if(i==j) return q[i];
        return arr[i][j-1].weight + p[j] + q[j];
    }   
    int c(int i, int j){
        if(i == j) return 0;
        int mini = 214552;
        for(int l=i+1;l<=j;l++){
            mini = min(mini,arr[l][j].cost + arr[i][l-1].cost);
        }
        return mini + w(i,j);
    }
    void create(){
        for(int c1=0;c1<n;c1++)
        for(int i=0,j=c1;i<n && j<n; i++,j++){
            arr[i][j].cost = c(i,j);
            arr[i][j].weight = w(i,j);
        }
        cout<<"Cost: "<<arr[0][n-1].cost<<endl;
    }
};

int main()
{
    OBST obj;
    obj.input();
    obj.create();
    return 0;
}