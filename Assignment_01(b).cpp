//============================================================================
// Name        : Assignment_01_part2.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
A Dictionary stores keywords & its meanings. Provide facility for adding new keywords,
deleting keywords, updating values of any entry. Provide facility to display whole data
sorted in ascending/ Descending order. Also find how many maximum comparisons may
require for finding any keyword. Use Binary Search Tree for implementation.
*/

#include <iostream>
using namespace std;

class Node{
	string keyword;
	string meaning;
	Node*left;
	Node*right;
public:
	Node(){}
	Node(string key,string mean){
		keyword = key;
		meaning = mean;
		left = NULL;
		right = NULL;
	}
	friend class BST;
};

class BST{
	Node*root;
public:
	BST(){
		root = NULL;
	}
	void displayDescending(Node* root){
		if(!root){
			return;
		}
		displayDescending(root->right);
		cout << root->keyword << ": " << root->meaning << endl;
		displayDescending(root->left);
	}
	void insert(string key, string mean){
		Node*curr = root;
		Node*pre = NULL;
		Node*newNode = new Node(key,mean);
		if(root == NULL){
			root = newNode;
		}
		else{
			while(true){
				if(curr == NULL && pre->keyword < key){
					pre->right = newNode;
					break;
				}
				else if(curr == NULL && pre->keyword > key){
					pre->left = newNode;
					break;
				}
				else{
					if(curr->keyword < key){
						pre = curr;
						curr=curr->right;
					}
					else{
						pre = curr;
						curr=curr->left;
					}
				}
			}
		}
	}
	void Inorder(Node* root){
		if(root){
			Inorder(root->left);
			cout << "-------------------------------------" << endl;
			cout << root->keyword << ":  " << root->meaning << endl;
			cout << "-------------------------------------" << endl;
			Inorder(root->right);
		}
	}
	Node*getRoot(){
		return root;
	}
	void update(string key, string newmeaning){
		Node*curr = root;
		while(curr){
			if(curr->keyword < key){
				curr = curr->right;
			}
			else if(curr->keyword>key){
				curr = curr->left;
			}
			else if(curr->keyword==key){
				break;
			}
		}
		if(curr==NULL){
			cout << ">> The keyword is not present in the dictionary." << endl;
		}
		else{
			curr->meaning = newmeaning;
		}
	}
	void deleteNode(string key, Node* root){
		Node*parent = nullptr;
		Node*curr = root;
		while(curr && curr->keyword != key){
			if(curr->keyword < key){
				parent = curr;
				curr = curr->right;
			}
			else if(curr->keyword > key){
				parent = curr;
				curr = curr->left;
			}
		}
		if(curr == NULL){
			cout << ">> The keyword can't be found." << endl;
			return;
		}
		if(curr->left == NULL && curr->right == NULL){
			if(parent == NULL){
				this->root = NULL;
				return;
			}
			else if(parent->left == curr){
				parent->left = NULL;
			}
			else{
				parent->right = NULL;
			}
			delete(curr);
		}
		else if(curr->left == NULL){
			if(parent == NULL){
				this->root = this->root->right;
				return;
			}
			else if(parent->left == curr){
				parent->left = curr->right;
			}
			else{
				parent->right = curr->right;
			}
			delete(curr);
		}
		else if(curr->right == NULL){
			if(parent == NULL){
				this->root = this->root->left;
				return;
			}
			else if(parent->left == curr){
				parent->left = curr->left;
			}
			else{
				parent->right = curr->left;
			}
			delete(curr);
		}
		else if(curr->right && curr->left){
			Node*minSuccessor = minValueNode(curr->right);
			string value = minSuccessor->keyword;
			string mean = minSuccessor->meaning;
			deleteNode(value,root);
			curr->keyword = value;
			curr->meaning = mean;
		}
	}
	Node* minValueNode(Node*cur){
		while(cur && cur->left){
			cur = cur->left;
		}
		return cur;
	}
};

int main() {
	BST bst;
	while(true){
		cout << "1. Enter '1' to add data to dictionary." << endl;
		cout << "2. Enter '2' to perform inorder traversal." << endl;
		cout << "3. Enter '3' to update the meaning of a keyword." << endl;
		cout << "4. Enter '4' to delete a particular keyword." << endl;
		int choice;
		cout << ">> Enter your choice: ";
		cin >> choice;
		cin.ignore();
		if(choice == 1){
			string keyword;
			string meaning;
			cout << ">> Enter the keyword: ";
			cin >> keyword;
			cin.ignore();
			cout << ">> Enter the meaning: ";
			getline(cin,meaning);
			bst.insert(keyword,meaning);
		}
		else if(choice == 2){
			bst.Inorder(bst.getRoot());
		}
		else if(choice == 3){
			string keyword,newmeaning;
			cout << ">> Enter the keyword: ";
			cin >> keyword;
			cin.ignore();
			cout << ">> Enter the new meaning: ";
			getline(cin,newmeaning);
			bst.update(keyword,newmeaning);
		}
		else if(choice == 4){
			string keyword;
			cout << ">> Enter the keyword you wish to delete: ";
			cin >> keyword;
			bst.deleteNode(keyword,bst.getRoot());
		}
		else if(choice == 0){
			cout << ">> GoodBye!" << endl;
			break;
		}
	}
	return 0;
}
