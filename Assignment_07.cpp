//============================================================================
// Name        : Assignment_07.cpp
// Author      : Ritanshu Koul
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <bits/stdc++.h>
using namespace std;

class Graph{
	int graph[7][7];
	int mst[7][7];
	int krus[7][7];
public:
	Graph(){
		for(int i=0;i<7;i++){
			for(int j=0;j<7;j++){
				graph[i][j] = 0;
				mst[i][j] = 0;
				krus[i][j] = 0;
			}
		}
	}
	void add(int f, int s, int w){
		graph[f][s] = w;
		graph[s][f] = w;
	}
	void display(){
		for(int i=0;i<7;i++){
			cout << i << " --> ";
			for(int j=0;j<7;j++){
				cout << graph[i][j] << " ";
			}
			cout << endl;
		}
	}
	bool over(int selected[]){
		for(int i=0;i<7;i++){
			if(selected[i] == 0){
				return false;
			}
		}
		return true;
	}
	void minspan(int start){
		// create a selected vertices list
		int selected[7];
		for(int i=0;i<7;i++){
			selected[i] = 0;
		}
		selected[start] = 1;
		while(not over(selected)){
			int min_i = -1;
			int min_j = -1;
			int mini = 100000;
			for(int i=0;i<7;i++){
				if(selected[i]){
					for(int j=0;j<7;j++){
						if(!selected[j] && graph[i][j] && !mst[i][j]){
							if(graph[i][j] < mini){
								mini = graph[i][j];
								min_i = i;
								min_j = j;
							}
						}
					}
				}
			}
			if(min_i != -1 && min_j != -1 && selected[min_j] == 0){
				mst[min_i][min_j] = mini;
				mst[min_j][min_i] = mini;
				selected[min_j] = 1;
			}
		}
	}
	void disp(){
		for(int i=0;i<7;i++){
			cout << i << " --> ";
			for(int j=0;j<7;j++){
				cout << mst[i][j] << " ";
			}
			cout << endl;
		}
	}
	bool dfs(int element = 0){
		int temp_graph[7][7];
		for(int i=0;i<7;i++){
			for(int j=0;j<7;j++){
				temp_graph[i][j] = 0;
			}
		}
		for(int i=0;i<7;i++){
			for(int j=0;j<7;j++){
				if(krus[i][j] && !temp_graph[j][i]){
					temp_graph[i][j] = krus[i][j];
				}
			}
		}
		stack<int> st;
		map<int,bool> mp;
		st.push(element);
		while(!st.empty()){
			int tp = st.top();
			if(mp[tp] == true){
				return true;
			}
			else{
				mp[tp] = true;
				st.pop();
				for(int i=0;i<7;i++){
					if(temp_graph[tp][i]){
						st.push(i);
					}
				}
			}
		}
		return false;
	}
	void kruskal(){
		vector<int> edges;
		map<int,pair<int,int> > vec;
		for(int i=0;i<7;i++){
			for(int j=i+1;j<7;j++){
				if(graph[i][j]){
					edges.push_back(graph[i][j]);
				}
			}
		}
		for(int i=0;i<7;i++){
			for(int j=i+1;j<7;j++){
				if(graph[i][j]){
					vec[graph[i][j]] = {i,j};
				}
			}
		}
		sort(edges.begin(),edges.end());
		int taken = 0;
		for(int i=0;(i<edges.size()) && (taken < 6);i++){
			pair<int,int> verx = vec[edges[i]];
			int first = verx.first;
			int second = verx.second;
			krus[first][second] = edges[i];
			krus[second][first] = edges[i];
			if(dfs()){
				edges[i] = INT_MAX;
				krus[first][second] = 0;
				krus[second][first] = 0;
			}
			else{
				taken++;
			}
		}
		for(int i=0;i<7;i++){
			cout << i << " --> ";
			for(int j=0;j<7;j++){
				cout << krus[i][j] << " ";
			}
			cout << endl;
		}
	}
	void cost(){
		int co = 0;
		for(int i=0;i<7;i++){
			for(int j=0;j<7;j++){
				co += mst[i][j];
			}
		}
		cout << "Minimum Cost = " << co/2 << endl;
	}
};


int main() {
	cout << "-------------CREATING GRAPH-------------" << endl;
	Graph obj;
	obj.add(1,0,55);
	obj.add(0,2,180);
	obj.add(2,4,350);
	obj.add(4,6,101);
	obj.add(6,5,90);
	obj.add(6,3,501);
	obj.add(6,0,57);
	obj.add(5,3,21);
	obj.add(3,1,100);
	obj.add(3,2,550);
	cout << "-------------CREATED GRAPH--------------" << endl;
	cout << endl;
	cout << "-------------DISPLAYING GRAPH-----------" << endl;
	obj.display();
	cout << endl;
	cout << "-------------PRIM ALGORITHM-----------" << endl;
	obj.minspan(0);
	obj.disp();
	cout << "-------------KRUSKAL ALGORITHM-----------" << endl;
	obj.kruskal();
	cout << "-------------MINIMUM COST-----------" << endl;
	obj.cost();
	cout << endl;
	return 0;
}
