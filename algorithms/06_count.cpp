//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Ritanshu Koul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
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
	Node*getRoot(){
		return root;
	}
    int numberofNodes(Node* root);
    int leaves(Node*);
	int height(Node* root){
		if(!root) return 0;
		int l = height(root->left);
		int r = height(root->right);
		if(l>r) return l+1;
		else return r+1;
	}
	void swap(Node* root){
		if(root){
			Node*temp = root->left;
			root->left = root->right;
			root->right = temp;
			swap(root->left);
			swap(root->right);
		}
	}
	void in(Node* root){
		if(root){
			in(root->left);
			cout << root->data << " ";
			in(root->right);
		}
	}
};

int BinaryTree::leaves(Node*root){
	if(!root) return 0;
	else if(!root->left && !root->right) return 1;
	else return leaves(root->left) + leaves(root->right);
}


int BinaryTree::numberofNodes(Node* root){
    if(root){
        return 1+numberofNodes(root->left)+numberofNodes(root->right);
    }
    else{
        return 0;
    }
}

int main() {
	BinaryTree bst;
    bst.addNode(10);
    bst.addNode(5);
    bst.addNode(12);
    bst.addNode(4);
    bst.addNode(8);
    bst.addNode(6);
    bst.addNode(9);
    cout << bst.numberofNodes(bst.getRoot()) << endl;
    cout << bst.leaves(bst.getRoot()) << endl;
	cout << bst.height(bst.getRoot()) << endl;
	bst.in(bst.getRoot());
	cout << endl;
	bst.swap(bst.getRoot());
	bst.in(bst.getRoot());
	cout << endl;
	bst.swap(bst.getRoot());
	bst.in(bst.getRoot());
	cout << endl;
	bst.swap(bst.getRoot());
	bst.in(bst.getRoot());
	cout << endl;
	bst.swap(bst.getRoot());
	return 0;
}