//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Ritanshu Koul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
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
    void bfs();
};

void BinaryTree::bfs(){
    Node* curr = root;
    queue<Node*> q;
    q.push(curr);
    while(!q.empty()){
        curr = q.front();
        cout << curr->data << " ";
        if(curr->left){
            q.push(curr->left);
        }   
        if(curr->right){
            q.push(curr->right);
        }
        q.pop();
    }
}

int main() {
	BinaryTree bst;
	bst.addNode(10);
	bst.addNode(8);
	bst.addNode(12);
	bst.addNode(11);
	bst.addNode(13);
    bst.bfs();
	return 0;
}