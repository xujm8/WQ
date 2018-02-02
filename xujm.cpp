#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <map>
#include <ctime>
#include <cstring>
using namespace std;

struct Spell{
	string word;
	int val;
};


struct Path{
	string spstr;
	int val;
};

Path finalPath;
Spell allSpell[202];
string oriStr;
int greatestval = -2000000000;
int oriLen, spellNum;
map<string, Path> midPath;


Path findBest(string rsStr) {
	Path res;
	res.val = 0;
	if (rsStr.length() == 0) return res;
	map<string, Path>::iterator key = midPath.find(rsStr);
	if (key != midPath.end()) {
		return midPath[rsStr];
	}
	int val = -2000000000;
	int rslen = rsStr.length();
	for (int i = 0; i < spellNum; ++ i) {
		int j = rsStr.find(allSpell[i].word, 0);
		while(j != string::npos) {
			int splen = allSpell[i].word.length();
			Path bestpart = findBest(rsStr.substr(0,j) + rsStr.substr(j+splen));
			if (val < allSpell[i].val + bestpart.val){
				val = allSpell[i].val + bestpart.val;
				res = bestpart;
				res.val = bestpart.val + allSpell[i].val;
				res.spstr += to_string(j);
				res.spstr += ' ' ;
				res.spstr += allSpell[i].word;
				res.spstr += ',';
			}
			j = rsStr.find(allSpell[i].word, j + 1);
		}
	}
	midPath[rsStr] = res;
	return res;
}

void readData(string fileName) {
	ifstream in(fileName.c_str());
	if (!in.is_open()) {
		cout << "Error opening file\n";
		return;
	}
	in >> oriLen >> spellNum >> oriStr;
	for (int i = 0; i < spellNum; ++ i){
		in >> allSpell[i].word >> allSpell[i].val;
	}
	in.close();
}

void printSpell(string fileName, Path finalPath) {
	int len = finalPath.spstr.length();
	char finalStr[50000];
	strcpy(finalStr, finalPath.spstr.c_str());
	ofstream out(fileName.c_str());
	char * tokenPtr = strtok(finalStr, ",");
	while(tokenPtr != NULL) {
		out << tokenPtr << endl;
		tokenPtr = strtok(NULL, ",");
	}
	out << finalPath.val;
	out.close();
}



int main (int argc, char * argv[]) {
	clock_t start = clock();
	string inName = argv[1];
	string outName = argv[2];
	readData(inName);
	Path finalPath = findBest(oriStr);
	printSpell(outName, finalPath);
	clock_t finish = clock();
	double duration = (double)(finish - start)/CLOCKS_PER_SEC;
	cout << duration << endl;
	return 0;
}
