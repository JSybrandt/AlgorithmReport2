#include<iostream>
#include<fstream>
#include<list>
#include<vector>
#include<stack>
#include<set>
#include <map> //for pair
#include <string>
#include <cstdio>
#include <ctime>

using namespace std;


struct vertex{
	vertex(){visited=false;assigned=-1;}
	bool visited;
	int assigned;
	vector<int> children, parents;
};

void buildGraph(vertex * nodes, string sourceFile){
	fstream fin(sourceFile,ios::in);
	int s,d;
	while(fin>>s>>d){
		nodes[s].children.push_back(d);
		nodes[d].parents.push_back(s);
	}
	fin.close();
}

void visit(vertex * nodes,int i, list<int>& l){

	if(!nodes[i].visited){
		nodes[i].visited=true;
		for(int c = 0; c < nodes[i].children.size(); c++){
			visit(nodes,nodes[i].children[c],l);
		}
		l.push_front(i);
	}

}

void assign(vertex * nodes, int u, int root){
	if(nodes[u].assigned==-1){
		nodes[u].assigned=root;
		for(int parent : nodes[u].parents)
			assign(nodes,parent,root);
	}
}

typedef pair<string,int> DataPair;

int main(){

		
		vector<DataPair> data;
		data.push_back(DataPair("7587_soc-Epinions1.txt",7587));
		data.push_back(DataPair("15174_soc-Epinions1.txt",15174));
		data.push_back(DataPair("22761_soc-Epinions1.txt",22761));
		data.push_back(DataPair("30348_soc-Epinions1.txt",30348));
		data.push_back(DataPair("37935_soc-Epinions1.txt",37935));
		data.push_back(DataPair("45522_soc-Epinions1.txt",45522));
		data.push_back(DataPair("53109_soc-Epinions1.txt",53109));
		data.push_back(DataPair("60696_soc-Epinions1.txt",60696));
		data.push_back(DataPair("68283_soc-Epinions1.txt",68283));
		data.push_back(DataPair("75879_soc-Epinions1.txt",75879));

		for(DataPair d : data){

			int numVertices =  d.second;
			string file = d.first;

			vertex * nodes = new vertex[numVertices];
			buildGraph(nodes,file);
			
			std::clock_t start;
			double duration;
			start = std::clock();

			for(int i=0; i<numVertices; i++){
				//cout<<"Checking Node:"<<i<<endl;
				list<int> l;
				visit(nodes,i,l);
				for(int u : l){
					assign(nodes,u,u);
				}
			}

			duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	
			set<int> s;
			for(int i=0; i<numVertices; i++){
				//cout<<i<<":"<<nodes[i].assigned<<endl;
				s.insert(nodes[i].assigned);
			}
			cout<<"Nodes:"<<numVertices<<"\tGroups:"<<s.size()<<"\tTime:"<<duration<<endl;

			delete [] nodes;

		}

	return 0;
}