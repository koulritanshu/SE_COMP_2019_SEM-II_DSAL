#include <iostream>
using namespace std;

class Node{
    string data;
    Node* next;
    Node* down;
public:
    Node(string x){
        data = x;
        next = NULL;
        down = NULL;
    }
    friend class Graph;
};

class Graph{
    Node* head;
public:
    Graph(){
        head = NULL;
    }
    void addNode(string d, string x){
        Node* newNode = new Node(d);
        Node* newNode2 = new Node(x);
        if(head == NULL){
            newNode->next = newNode2;
            head = newNode;
            return;
        }
        else{
            Node* curr = head;
            while(curr->down != NULL || curr->data != d){
                curr = curr->down;
            }
            if(curr->data == d){
                while(curr->next != NULL){
                    curr = curr->next;
                }
                curr->next = newNode2;
            }
            else{
                newNode->next = newNode2;
                curr->down = newNode;
            }
        }
    }
    void add(string d,string x){
        addNode(d,x);
        cout << "completed first\n";
        addNode(x,d);
    }
    void display(){
        Node*curr = head;
        while(curr){
            Node* insidecurr = curr;
            while(insidecurr){
                cout << insidecurr->data << " -> ";
                insidecurr = insidecurr->next;
            }
            curr = curr->down;
            cout << endl;
        }
    }
};

int main()
{
    Graph obj;
    cout << "Adding edges\n";
    obj.add("PICT","BVP");
    cout << "First done\n";
    obj.add("PICT","Richie");
    obj.add("PICT","Durga");
    obj.add("Richie","Durga");
    cout << "Added all edges";
    obj.display();
}
