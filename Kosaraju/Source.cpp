#include<iostream>
#include<fstream>
#include<list>
#include<vector>
#include<stack>
#include <map> //for pair
#include <string>
#include <cstdio>
#include <ctime>
#include <unordered_map>
#include <unordered_set>
#include <chrono>

using namespace std;

const string FILE_PATH = "twitter_combined.txt";
const int MAX_NODES = 81306;
//const string FILE_PATH = "smallExample.txt";
//const int MAX_NODES = 8;

struct vertex{
	vertex(){visited=false;assigned=-1;}
	bool visited;
	int assigned;
	vector<int> children, parents;
};

unordered_map<int,vertex> buildGraph(string sourceFile){
	unordered_map<int,vertex> nodes;
	fstream fin(sourceFile,ios::in);
	int s,d;
	while(fin>>s>>d){
		nodes[s].children.push_back(d);
		nodes[d].parents.push_back(s);
	}
	fin.close();
	return nodes;
}


unordered_map<int,vertex>  buildGraph(unordered_map<int,vertex> sourceNodes, unordered_set<int> legalNodes){
	unordered_map<int,vertex> nodes;
	for(int node : legalNodes){
		for(int child : sourceNodes[node].children)
			if(legalNodes.count(child)==1)
				nodes[node].children.push_back(child);
		for(int parent : sourceNodes[node].parents)
			if(legalNodes.count(parent)==1)
				nodes[node].parents.push_back(parent);
	}
	return nodes;
}

unordered_set<int> getSetOfNodes(unordered_map<int,vertex> sourceNodes, int numNodes){
	numNodes = min(numNodes,(int)sourceNodes.size());
	unordered_set<int> res;
	stack<int> stk;
	while(res.size()<numNodes){
		stk.push(rand()%MAX_NODES);
		while(!stk.empty() && res.size()<numNodes){
			int curr = stk.top(); stk.pop();
			if(res.count(curr)==0){
				res.insert(curr);
				for(int child : sourceNodes[curr].children){
					stk.push(child);
				}
			}
		}
	}
	return res;

}

void visit(unordered_map<int,vertex> & nodes,int i, list<int>& l){
	
	if(!nodes[i].visited){
		nodes[i].visited=true;
		for(int child : nodes[i].children){
			visit(nodes,child,l);
		}
		l.push_front(i);
	}

}

void assign(unordered_map<int,vertex> & nodes, int u, int root){
	if(nodes[u].assigned==-1){
		nodes[u].assigned=root;
		for(int parent : nodes[u].parents)
			assign(nodes,parent,root);
	}
}

int main(){
	
	//srand(time(0));
	fstream fout("results.txt",ios::out);
	cout<<"Started:";
	unordered_map<int,vertex> root = buildGraph(FILE_PATH);
	cout<<"Built Root"<<endl;
	for(int size = 10; size <= MAX_NODES; size*=10){
		for(int i=0;i<10;i++){
			unordered_set<int> legalNodes = getSetOfNodes(root,size);
			unordered_map<int,vertex> nodes = buildGraph(root, legalNodes);

			auto start = std::chrono::high_resolution_clock::now();

			list<int> l;
			for(int nodeIndex : legalNodes){			
				visit(nodes,nodeIndex,l);
			}
			for(int u : l){
				assign(nodes,u,u);
			}

			auto finish = std::chrono::high_resolution_clock::now();
			auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(finish-start).count();
		
			unordered_set<int> s;
			for(int nodeIndex : legalNodes){
				s.insert(nodes[nodeIndex].assigned);
			}
			cout<<"Nodes:"<<size<<"\tGroups:"<<s.size()<<"\tTime:"<<duration<<endl;
			fout<<"Nodes:"<<size<<"\tGroups:"<<s.size()<<"\tTime:"<<duration<<endl;
		}
	}
			
	
	fout.close();
	
	return 0;
}