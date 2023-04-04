//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class Node{
	int data;
	Node*left;
	Node*right;
public:
	Node(int x){
		data = x;
		left = NULL;
		right = NULL;
	}
	friend class BinaryTree;
};

class BinaryTree{
	Node*root;
public:
	BinaryTree(){
		root = NULL;
	}
	void addNode(int dat){
		Node* newNode = new Node(dat);
		if(root == NULL){
			root = newNode;
			return;
		}
		else{
			Node* curr = root;
			Node*pre;
			while(true){
				pre = curr;
				if((curr -> data) < dat){
					curr = curr->right;
					if(curr == NULL){
						pre->right = newNode;
						break;
					}
				}
				else{
					curr = curr->left;
					if(curr == NULL){
						pre->left = newNode;
						break;
					}
				}
			}
		}
	}
	void preorderTraversal(Node* root){
		if(root != NULL){
			cout << root->data << " ";
			preorderTraversal(root->left);
			preorderTraversal(root->right);
		}
	}
	Node*getRoot(){
		return root;
	}
	int getMax(){
		Node*curr = root;
		while(curr->right != NULL){
			curr=curr->right;
		}
		return curr->data;
	}
	int getMin(){
		Node*curr = root;
		while(curr->left != NULL){
			curr = curr->left;
		}
		return curr->data;
	}
	void search(int element){
		Node*curr = root;
		while(curr != NULL && curr->data != element){
			if(curr->data < element){
				curr = curr->right;
			}
			else{
				curr = curr->left;
			}
		}
		if(curr != NULL){
			cout << ">> Element is present inside the Tree." << endl;
		}
		else{
			cout << ">> Element is not present inside the Tree." << endl;
		}
	}
	int getMaxNodes(Node* root){
		if(root == NULL){
			return 0;
		}
		else{
			int depthleft = getMaxNodes(root->left);
			int depthright = getMaxNodes(root->right);
			if(depthleft > depthright){
				return depthleft + 1;
			}
			else{
				return depthright + 1;
			}
		}
	}
	void swap(Node* root){
		if(root == NULL){
			return;
		}
		Node*temp = root->left;
		root->left = root->right;
		root->right = temp;
		swap(root->left);
		swap(root->right);
	}
};

int main() {
	BinaryTree bst;
	while(true){
		cout << "1. Enter a new node." << endl;
		cout << "2. Perform pre-order Traversal."  << endl;
		cout << "3. Find maximum value present in the Tree." << endl;
		cout << "4. Find minimum value present in the Tree." << endl;
		cout << "5. Search an element in the Tree." << endl;
		cout << "6. Get maximum number of nodes." << endl;
		cout << "7. Swap the nodes." << endl;
		cout << "0. Exit." << endl;
		int choice;
		cout << ">> Enter your choice: ";
		cin >> choice;
		if(choice == 1){
			int x;
			cout << ">> Enter data to store: ";
			cin >> x;
			bst.addNode(x);
		}
		else if(choice == 2){
			bst.preorderTraversal(bst.getRoot());
			cout << endl;
		}
		else if(choice == 3){
			cout << ">> The maximum value in the tree is: " << bst.getMax() << endl;
		}
		else if(choice == 4){
			cout << ">> The minimum value in the tree is: " << bst.getMin() << endl;
		}
		else if(choice == 5){
			int element;
			cout << ">> Enter the element which you wish to search in the tree: " << endl;
			cin >> element;
			bst.search(element);
		}
		else if(choice == 6){
			cout << ">> The maximum number of nodes are: " << bst.getMaxNodes(bst.getRoot()) << endl;
		}
		else if(choice == 0){
			cout << ">> GoodBye!" << endl;
			break;
		}
		else if(choice == 7){
			bst.swap(bst.getRoot());
		}
		else{
			cout << ">> Give input again." << endl;
		}
		cout << endl;
	}
	return 0;
}
