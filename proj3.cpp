#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#include <vector>
#include <cstdio>
#include <map>
#include <ctime>

struct Spell{
	string word;
	int val;
};

struct Path{
	vector<string> spstr;
	vector<int> sppos;
	int val;
	/*Path(vector<string> tmpspstr = vector<string>(), vector<int> tmpsppos = vector<string> (), int tmpval = 0){
		spstr = tmpspstr;
		sppos = tmpspstr;
		val = tmpval;
	}*/
};

Path finalPath;
Spell allSpell[202];
string oriStr;
int greatestval = -2000000000;
int oriLen, spellNum;
map<string, Path> midPath;
/*
void dfs(string rsStr, int val, Path & onePath) {
	if (val > greatestval) {
		greatestval = val;
		finalPath = onePath;
	}
	//len()
	bool endFlag = 0;
	int rslen = rsStr.length();
	for (int i = 0; i < spellNum; ++ i) {
		int splen = allSpell[i].word.length();
		for (int j = 0; j <= rslen - splen; ++ j) {
			endFlag = 1;
			if (rsStr.substr(j, splen) == allSpell[i].word) {
				onePath.spstr.push_back(allSpell[i].word);
				onePath.sppos.push_back(j);
				dfs(rsStr.substr(0,j) + rsStr.substr(j+splen), val + allSpell[i].val, onePath);
			}
		}
	}
	if (!endFlag) {
		midPath[rsStr] = 0;
	} 
	//map<string, Path>::iterator key = midPath.find(rsStr);
	return;
}*/

Path findBest(string rsStr) {
	Path res;
	res.val = 0;
	if (rsStr.length() == 0) return res;
	map<string, Path>::iterator key = midPath.find(rsStr);
	if (key != midPath.end()) {
		return midPath[rsStr];
	}
	int val = -2000000000;
	bool endFlag = 0;
	int rslen = rsStr.length();
	for (int i = 0; i < spellNum; ++ i) {
		int splen = allSpell[i].word.length();
		for (int j = 0; j <= rslen - splen; ++ j) {
			endFlag = 1;
			if (rsStr.substr(j,splen) == allSpell[i].word) {
				Path bestpart = findBest(rsStr.substr(0,j) + rsStr.substr(j+splen));
				if (val < allSpell[i].val + bestpart.val){
					val = allSpell[i].val + bestpart.val;
					res = bestpart;
					res.val = bestpart.val + allSpell[i].val;
					res.spstr.push_back(allSpell[i].word);
					res.sppos.push_back(j);
					midPath[rsStr] = res;
				}
			}
		}
	}
	if (!endFlag) {
		midPath[rsStr] = res;
	}
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
	int finalLen = finalPath.sppos.size();
	ofstream out(fileName.c_str());
	for(int i = finalLen - 1; i >= 0; -- i) {
		out << finalPath.sppos[i] << ' ' << finalPath.spstr[i] << endl;
	}
	out << finalPath.val;
	out.close();
}


int main () {
	clock_t start = clock();
	readData("in.txt");
	Path finalPath = findBest(oriStr);
	printSpell("out.txt",finalPath);
	clock_t finish = clock();
	double duration = (double)(finish - start)/CLOCKS_PER_SEC;
	cout << duration << endl;
	return 0;
}
