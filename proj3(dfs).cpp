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
};

Path finalPath;
Spell allSpell[202];
string oristr;
int greatestval = -2000000000;
int orilen, spellnum;
vector<Spell> midSpell;

void dfs(string rsstr, int val, Path & onePath) {
	if (val > greatestval) {
		greatestval = val;
		finalPath = onePath;
	}
	//len()
	int rslen = rsstr.length();
	for (int i = 0; i < spellnum; ++ i) {
		int splen = allSpell[i].word.length();
		for (int j = 0; j <= rslen - splen; ++ j) {
			if (rsstr.substr(j,splen) == allSpell[i].word) {
				onePath.spstr.push_back(allSpell[i].word);
				onePath.sppos.push_back(j);
				dfs(rsstr.substr(0,j) + rsstr.substr(j+splen),val + allSpell[i].val,onePath);
			}
		}
	}
	return;
}


int main () {
	clock_t start,finish;
	double duration;
	start = clock();
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
	for (int i = 0; i < spellnum; ++ i) {
		int splen = allSpell[i].word.length();
		for (int j = 0; j <= orilen - splen; ++ j) {
			if (oristr.substr(j,splen) == allSpell[i].word) {
				Path onePath;
				onePath.spstr.push_back(allSpell[i].word);
				onePath.sppos.push_back(j);
				dfs(oristr.substr(0,j) + oristr.substr(j+splen), allSpell[i].val, onePath);
			}
		}
	}
	int finallen = finalPath.sppos.size();
	ofstream out("out");
	for(int i = 0; i < finallen; ++ i) {
		out << finalPath.sppos[i] << ' ' << finalPath.spstr[i] << endl;
	}
	out << greatestval;
	out.close();
	finish = clock();
	duration = (double)(finish - start)/CLOCKS_PER_SEC;
	cout << duration;
	return 0;
}