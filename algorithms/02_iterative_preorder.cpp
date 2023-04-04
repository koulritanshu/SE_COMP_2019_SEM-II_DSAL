//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : 
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
    void pre();
};

void BinaryTree::pre(){
    stack<Node*> st;
    Node* curr = root;
    if(!curr){
        cout << ">> Tree is empty\n";
        return;
    }
    while(true){
        if(curr){
            cout << curr->data << " ";
            st.push(curr);
            curr = curr->left;
        }
        else if(!st.empty()){
            Node* temp = st.top();
            st.pop();
            if(temp->right){
                curr = temp->right;
            }
        }
        else{
            return;
        }
    }
}

int main() {
	BinaryTree bst;
	bst.addNode(10);
	bst.addNode(11);
	bst.addNode(8);
	bst.addNode(7);
	bst.addNode(9);
    bst.pre();
	return 0;
}