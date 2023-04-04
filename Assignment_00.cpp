#include <iostream>
using namespace std;

class Node{
    int data;
    Node* next;
public:
    Node(int x){
        data = x;
        next = NULL;
    }
    friend class LL;
};

class LL{
    Node*start;
public:
    LL(){
        start = NULL;
    }
    void push_front(int x);
    void push_back(int x);
    void pop_front();
    void pop_back();
    void display();
    void insertafter(int p, int x);
};

void LL::insertafter(int p, int x){
	Node*temp = start;
	while(temp!=NULL && temp->data != p){
		temp = temp->next;
	}
	if(temp==NULL){
		cout << ">> Node not present in the list.\n";
	}
	else{
		Node* newNode = new Node(x);
		newNode->next= temp->next;
		temp->next = newNode;
	}
}

void LL::display(){
    Node*temp = start;
    while(temp!=NULL){
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

void LL::push_front(int x){
    Node*temp = new Node(x);
    temp->next = start;
    start = temp;
}

void LL::push_back(int x){
    if(start == NULL){
        push_front(x);
    }
    else{
        Node* temp = start;
        Node* newNode = new Node(x);
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void LL::pop_front(){
    if(start == NULL){
        cout << ">> Linked List is empty.\n";
    }
    else{
        start = start->next;
    }
}

void LL::pop_back(){
    if(start == NULL){
        cout << ">> Linked List is empty.\n";
    }
    else{
        if(start->next == NULL){
            start=start->next;
        }
        else{
            Node*temp = start;
            while(temp->next->next != NULL){
                temp = temp->next;
            }
            temp->next = NULL;
        }
    }
}

int main()
{
    LL obj;
    while(true){
        cout << "1. Insert start\n";
        cout << "2. Insert end.\n";
        cout << "3. Delete start.\n";
        cout << "4. Delete end.\n";
        cout << "5. Display\n";
        cout << "6. Insert after\n";
        cout << "0. Exit.\n";
        int choice;
        cout << "Make choice: ";
        cin >> choice;
        if(choice == 1){
            int x;
            cout << "Enter value to insert: ";
            cin >> x;
            obj.push_front(x);
            obj.display();
        }
        else if(choice == 6){
        	int valuebefore,value;
        	cout << "Enter value after you wish to enter and the value respectively: ";
        	cin >> valuebefore >> value;
        	obj.insertafter(valuebefore,value);
        	obj.display();
        }
        else if(choice == 2){
            int x;
            cout << "Enter value to insert: ";
            cin >> x;
            obj.push_back(x);
            obj.display();
        }
        else if(choice == 3){
            obj.pop_front();
            obj.display();
        }
        else if(choice == 4){
            obj.pop_back();
            obj.display();
        }
        else if(choice == 5){
            obj.display();
        }
        else if(choice == 0){
            cout << "GoodBye!\n";
            break;
        }
        else{
            cout << "Incorrect Option.\n";
        }
    }
}
