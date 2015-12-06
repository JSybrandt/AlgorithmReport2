#include<fstream>
#include<string>

using namespace std;

const string FILE_PATH = "soc-Epinions1.txt";
const int MAX_SIZE = 75879;
const int NUM_SPLITS = 10;
const int ITERATION_SIZE = MAX_SIZE/NUM_SPLITS;

int main2(){
	
	for(int i=1; i<=NUM_SPLITS; i++){
		int maxNodeValue = ITERATION_SIZE*i;
		if(i==NUM_SPLITS)
			maxNodeValue=MAX_SIZE;
		

		fstream fin(FILE_PATH,ios::in);
		fstream fout(std::to_string(maxNodeValue)+"_"+FILE_PATH,ios::out);

		int a,b;
		while(fin>>a>>b)
			if(max(a,b)<maxNodeValue)
				fout<<a<<" "<<b<<endl;

		fout.close();
		fin.close();

	}
	return 0;
}