//============================================================================
// Name        : Assignment_05.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;


class Node{
	string keyword;
	string meaning;
	Node* next;
public:
	Node(string k, string m){
		keyword = k;
		meaning = m;
		next = NULL;
	}
	friend class Dictionary;
};

class Dictionary{
	Node* arr[26];
	string a = "11";
public:
	void createDictionary(){
		for(int i=0;i<26;i++){
			Node* newNode = new Node(a,a);
			arr[i] = newNode;
			a += "1";
		}
	}
	void push_back(string k, string m){
		int ind;
		if(k[0] >= 'A' && k[0] <= 'Z'){
			ind = k[0] - 'A';
		}
		else{
			ind = k[0] - 'a';
		}
		Node* newNode = new Node(k,m);
		Node* curr = arr[ind];
		while(curr->next != NULL){
			curr = curr->next;
		}
		curr->next = newNode;
	}
	void displayLL(Node* o){
		Node* obj = o;
		obj = obj->next;
		while(obj != NULL){
			cout << "{keyword: " << obj->keyword << ", meaning: " << obj->meaning << "}";
			obj = obj->next;
			if(obj){
				cout << "-> ";
			}
		}
	}
	void display(){
		char a = 'A';
		for(int i=0;i<26;i++){
			cout << ">> " << i << ". [" << a << "]" << "->";
			displayLL(arr[i]);
			a++;
			cout << endl;
		}
	}
	void search(string k){
		int ind;
		if(k[0] >= 'a' && k[0] <= 'z'){
			ind = k[0] - 'a';
		}
		else{
			ind = k[0] - 'A';
		}
		Node* obj = arr[ind];
		while(obj!=NULL){
			if(obj->keyword == k){
				cout << ">> Keyword present at index: " << ind << endl;
				cout << ">> Keyword = " << k << endl;
				cout << ">> Meaning = " << obj->meaning << endl;
				return;
			}
			obj = obj->next;
		}
		cout << ">> Keyword not found." << endl;
		return;
	}
	void del(string k){
		int ind;
		if(k[0] >= 'a' && k[0] <= 'z'){
			ind = k[0] - 'a';
		}
		else{
			ind = k[0] - 'A';
		}
		Node*pre;
		Node* obj = arr[ind];
		while(obj!=NULL){
			if(obj->keyword == k){
				pre->next = obj->next;
				return;
			}
			pre = obj;
			obj = obj->next;
		}
		cout << ">> Keyword not found." << endl;
		return;
	}
};


int main() {
	Dictionary obj;
	obj.createDictionary();
	while(true){
		cout << "0. Exit." << endl;
		cout << "1. Add data to dictionary." << endl;
		cout << "2. Display dictionary data." << endl;
		cout << "3. Search a keyword." << endl;
		cout << "4. Delete a keyword." << endl;
		int choice;
		cout << ">> Make your choice: " << endl;
		cin >> choice;
		cout << "-----------------------------------------------------------" << endl;
		if(choice == 0){
			cout << ">> GoodBye!" << endl;
			break;
		}
		else if(choice == 1){
			cin.ignore();
			cout << ">> Enter the keyword: " << endl;
			string k,m;
			getline(cin,k);
			cout << ">> Enter the meaning: " << endl;
			getline(cin,m);
			obj.push_back(k,m);
		}
		else if(choice == 2){
			obj.display();
		}
		else if(choice == 3){
			cin.ignore();
			string k;
			cout << ">> Enter the keyword: ";
			getline(cin,k);
			obj.search(k);
		}
		else if(choice == 4){
			cin.ignore();
			string k;
			cout << ">> Enter the keyword: ";
			getline(cin,k);
			obj.del(k);
		}
		cout << "-----------------------------------------------------------" << endl;
	}
	return 0;
}
