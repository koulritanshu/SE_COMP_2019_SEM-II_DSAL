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
    void post();
};

void BinaryTree::post(){
    stack<Node*> st;
    stack<Node*> ans;
    Node* curr = root;
    if(curr==nullptr) return;
    st.push(curr);
    while(!st.empty()){
        curr = st.top();
        st.pop();
        ans.push(curr);
        if(curr->left){
            st.push(curr->left);
        }
        if(curr->right){
            st.push(curr->right);
        }
    }
    while(!ans.empty()){
        curr = ans.top();
        cout << curr->data << " ";
        ans.pop();
    }
}

int main() {
	BinaryTree bst;
	bst.addNode(50);
	bst.addNode(17);
	bst.addNode(72);
	bst.addNode(12);
	bst.addNode(23);
	bst.addNode(54);
	bst.addNode(76);
	bst.addNode(9);
	bst.addNode(14);
	bst.addNode(19);
	bst.addNode(67);
    bst.post();
	return 0;
}