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
string oristr;
int greatestval = -2000000000;
int orilen, spellnum;
map<string, Path> midPath;
/*
void dfs(string rsstr, int val, Path & onePath) {
	if (val > greatestval) {
		greatestval = val;
		finalPath = onePath;
	}
	//len()
	bool endFlag = 0;
	int rslen = rsstr.length();
	for (int i = 0; i < spellnum; ++ i) {
		int splen = allSpell[i].word.length();
		for (int j = 0; j <= rslen - splen; ++ j) {
			endFlag = 1;
			if (rsstr.substr(j, splen) == allSpell[i].word) {
				onePath.spstr.push_back(allSpell[i].word);
				onePath.sppos.push_back(j);
				dfs(rsstr.substr(0,j) + rsstr.substr(j+splen), val + allSpell[i].val, onePath);
			}
		}
	}
	if (!endFlag) {
		midPath[rsstr] = 0;
	} 
	//map<string, Path>::iterator key = midPath.find(rsstr);
	return;
}*/

Path findBest(string rsstr) {
	Path res;
	res.val = 0;
	if (rsstr.length() == 0) return res;
	map<string, Path>::iterator key = midPath.find(rsstr);
	if (key != midPath.end()) {
		return midPath[rsstr];
	}
	int val = -2000000000;
	bool endFlag = 0;
	int rslen = rsstr.length();
	for (int i = 0; i < spellnum; ++ i) {
		int splen = allSpell[i].word.length();
		for (int j = 0; j <= rslen - splen; ++ j) {
			endFlag = 1;
			if (rsstr.substr(j,splen) == allSpell[i].word) {
				Path bestpart = findBest(rsstr.substr(0,j) + rsstr.substr(j+splen));
				if (val < allSpell[i].val + bestpart.val){
					val = allSpell[i].val + bestpart.val;
					res = bestpart;
					res.val = bestpart.val + allSpell[i].val;
					res.spstr.push_back(allSpell[i].word);
					res.sppos.push_back(j);
					midPath[rsstr] = res;
				}
			}
		}
	}
	if (!endFlag) {
		midPath[rsstr] = res;
	}
	return res;
}


int main () {
	clock_t start = clock();
	ifstream in("in");
	if (!in.is_open()) {
		cout << "Error opening file\n";
		return 0;
	}
	in >> orilen >> spellnum >> oristr;
	for (int i = 0; i < spellnum; ++ i){
		in >> allSpell[i].word >> allSpell[i].val;
	}
	in.close();
	Path finalPath = findBest(oristr);
	int finalLen = finalPath.sppos.size();
	ofstream out("out");
	for(int i = finalLen - 1; i >= 0; -- i) {
		out << finalPath.sppos[i] << ' ' << finalPath.spstr[i] << endl;
	}
	out << finalPath.val;
	out.close();
	clock_t finish = clock();
	double duration = (double)(finish - start)/CLOCKS_PER_SEC;
	cout << duration << endl;
	return 0;
}