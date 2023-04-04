//============================================================================
// Name        : Assignment_02.cpp
// Author      : Ritanshu Koul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
Perform inorder, preorder and post order traversal
*/


#include <iostream>
using namespace std;

template<class T>
class Stack{
	T arr[100];
	int top;
public:
	Stack(){
		top = -1;
	}
	void push(T val){
		if(top == 99){
			cout << ">> Stack is full." << endl;
		}
		else{
			top++;
			arr[top] = val;
		}
	}
	T pop(){
		T x = arr[top];
		top--;
		return x;
	}
	bool isFull() { return (top == 99); }
	bool isEmpty() { return (top == -1); }
	T topEl() { return arr[top]; }
};


class Node{
	int data;
	Node*left,*right;
public:
	Node(int x){
		data = x;
		left = right = NULL;
	}
	friend class BST;
};

class BST{
	Node* root;
	int leaves;
	int internal;
public:
	BST(){
		root = NULL;
		leaves = 0;
		internal = 0;
	}
	void insert(int x);
	Node* insertRecursive(Node* root, int x);
	void inorderRecursive(Node*root);

	void operator = (BST &obj){
		obj.root = root;
	}
	void preorderRecursive(Node* root){
		if(root){
			cout << root->data << " ";
			preorderRecursive(root->left);
			preorderRecursive(root->right);
		}
		else return;
	}
	void postorderRecursive(Node* root){
		if(root){
			postorderRecursive(root->left);
			postorderRecursive(root->right);
			cout << root->data << " ";
		}
		else return;
	}
	Node* getRoot(){ return root; }
	void inorder();
	void preorder();
	void postorder();
	int getHeight(Node* root){
		if(root){
			int l = getHeight(root->left);
			int r = getHeight(root->right);
			if(l>r){
				return l+1;
			}
			else{
				return r+1;
			}
		}
		else return 0;
	}
	void height(){
		int ans = getHeight(root);
		cout << ">> The height of the tree is " << ans << endl;
	}
	void swap(Node*root){
		if(root){
			Node*temp = root->left;
			root->left = root->right;
			root->right = temp;
			swap(root->left);
			swap(root->right);
		}
		else return;
	}
	void countLeafNodes(Node* root){
		if(!root){
			return;
		}
		if(!root->left && !root->right){
			leaves++;
			return;
		}
		else{
			if(root->left) countLeafNodes(root->left);
			if(root->right) countLeafNodes(root->right);
		}
	}
	void countInternalNodes(Node*root){
		if(!root){
			return;
		}
		if(root->left || root->right){
			internal++;
			countInternalNodes(root->left);
			countInternalNodes(root->right);
		}
		else{
			return;
		}
	}
	void count(){
		leaves = 0;
		internal = 0;
		countLeafNodes(root);
		countInternalNodes(root);
		cout << ">> Count of leaves = " << leaves << endl;
		cout << ">> Count of internal nodes = " << internal << endl;
	}
	void deleteTree(Node* curr){
		if(!curr){
			return;
		}
		else{
			deleteTree(curr->left);
			deleteTree(curr->right);
			delete curr;
		}
		root = NULL;
	}
};

void BST::inorderRecursive(Node* root){
	if(root){
		inorderRecursive(root->left);
		cout << root->data << " ";
		inorderRecursive(root->right);
	}
	else return;
}

Node* BST::insertRecursive(Node* curr, int x){
	if(root == NULL){
		root = new Node(x);
		return root;
	}
	if(curr == NULL){
		curr = new Node(x);
		return curr;
	}
	cout << ">> The current node is " << curr->data << endl;
	cout << ">> Do you want to go to the left of this node or right? (l/r)" << endl;
	char choice;
	cout << ">> Make choice: ";
	cin >> choice;
	if(choice == 'r'){
		curr->right = insertRecursive(curr->right,x);
	}
	else if(choice == 'l'){
		curr->left = insertRecursive(curr->left,x);
	}
	return curr;
}

void BST::insert(int x){
	Node* newNode = new Node(x);
	Node*curr = root;
	if(curr == NULL){
		root = newNode;
	}
	else{
		Node*curr = root;
		while(true){
			cout << ">> The current node is " << curr->data << endl;
			cout << ">> Do you want to the left of this node or right? (l/r)" << endl;
			char choice;
			cout << ">> Make choice: ";
			cin >> choice;
			if(choice == 'r' && curr->right){
				curr = curr->right;
			}
			else if(choice == 'r'){
				curr->right = newNode;
				break;
			}
			else if(choice == 'l' && curr->left){
				curr = curr->left;
			}
			else if(choice == 'l'){
				curr->left = newNode;
				break;
			}
		}
	}
}

void BST::inorder(){
	if(root == NULL) return;
	Stack<Node*> st;
	Node* curr = root;
	while(curr->left){
		st.push(curr);
		curr = curr->left;
	}
	while(curr){
		cout << curr->data << " ";
		if(curr->right){
			curr = curr->right;
			while(curr->left){
				st.push(curr);
				curr = curr->left;
			}
		}
		else{
			if(st.isEmpty()){
				return;
			}
			curr = st.topEl();
			st.pop();
		}
	}
}

void BST::preorder(){
	if(root == NULL) return;
	Stack<Node*> st;
	Node* curr = root;
	st.push(root);
	while(!st.isEmpty()){
		Node* pre = st.topEl();
		st.pop();
		cout << pre->data << " ";
		if(pre->right){
			st.push(pre->right);
		}
		if(pre->left){
			st.push(pre->left);
		}
	}
}

void BST::postorder(){
	if(root == NULL) return;
	Stack<Node*> st;
	Stack<Node*> st2;
	st.push(root);
	while(!st.isEmpty()){
		Node*curr = st.topEl();
		st.pop();
		st2.push(curr);
		if(curr->left){
			st.push(curr->left);
		}
		if(curr->right){
			st.push(curr->right);
		}
	}
	while(!st2.isEmpty()){
		Node* curr = st2.topEl();
		st2.pop();
		cout << curr->data << " ";
	}
}

int main() {
	BST obj;
	while(true){
		cout << endl;
		cout << "0. EXIT." << endl;
		cout << "1. Recursive insertion." << endl;
		cout << "2. Iterative insertion." << endl;
		cout << "3. Recursive inorder traversal." << endl;
		cout << "4. Iterative inorder traversal." << endl;
		cout << "5. Recursive preorder traversal." << endl;
		cout << "6. Recursive postorder traversal." << endl;
		cout << "7. Height." << endl;
		cout << "8. Number of leaf nodes and internal nodes." << endl;
		cout << "9. Swap the binary tree." << endl;
		cout << "10. Delete the tree." << endl;
		cout << "11. Create copy of the tree." << endl;
		cout << "12. Iterative preorder traversal." << endl;
		cout << "13. Iterative postorder traversal." << endl;
		int ch;
		cin >> ch;
		if(ch == 1){
			int x;
			cin >> x;
			obj.insertRecursive(obj.getRoot(),x);
		}
		else if(ch == 11){
			BST obj2 = obj;
			obj2.inorderRecursive(obj2.getRoot());
		}
		else if(ch == 10){
			obj.deleteTree(obj.getRoot());
		}
		else if(ch == 9){
			obj.swap(obj.getRoot());
		}
		else if(ch == 2){
			int x;
			cin >> x;
			obj.insert(x);
		}
		else if(ch == 3){
			cout << "----------------------------" << endl;
			obj.inorderRecursive(obj.getRoot());
			cout << endl;
			cout << "----------------------------" << endl;
		}
		else if(ch == 5){
			cout << "----------------------------" << endl;
			obj.preorderRecursive(obj.getRoot());
			cout << endl;
			cout << "----------------------------" << endl;
		}
		else if(ch == 6){
			cout << "----------------------------" << endl;
			obj.postorderRecursive(obj.getRoot());
			cout << endl;
			cout << "----------------------------" << endl;
		}
		else if(ch == 4){
			cout << "----------------------------" << endl;
			obj.inorder();
			cout << endl;
			cout << "----------------------------" << endl;
		}
		else if(ch == 12){
			cout << "----------------------------" << endl;
			obj.preorder();
			cout << endl;
			cout << "----------------------------" << endl;
		}
		else if(ch == 13){
			cout << "----------------------------" << endl;
			obj.postorder();
			cout << endl;
			cout << "----------------------------" << endl;
		}
		else if(ch == 7){
			obj.height();
		}
		else if(ch == 8){
			obj.count();
		}
		else if(ch == 0){
			break;
		}
		cout << "----------------------------" << endl;
	}
	return 0;
}
