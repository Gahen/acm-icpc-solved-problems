#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <set>
#include <map>

using namespace std;

struct Word {
	string value;
	Word(string s) {
		value = s;
	}
};

// Programación dinámica
map<string, int> mapa;

// Devuelve el número para esa letra en lo que resta del string
int wordSortLetter(string word, char letter) {
	int counter = 0;
	for (int i=0; i<word.size(); i++) {
		if (letter > word[i]) {
			// cout << word << ": " << letter << word[i] << endl;
			counter++;
		}
	}
	return counter;
}

int wordSortVal(Word w1) {
	string wword = w1.value;
	if (mapa.find(wword) == mapa.end()) {
		// cout << "palabra: " << wword << endl;
		string word = wword;
		int total = 0;
		while (word.size() > 0) {
			char letter = word[0];
			word.erase(0,1);
			// cout << letter << ": " << wordSortLetter(word, letter) << endl;
			total += wordSortLetter(word, letter);
		}
		mapa.insert(make_pair(wword, total));
		// cout << wword << " : " << total << endl;
	}
	return mapa[wword];
}

bool operator < (const Word &w1,const Word &w2) {
	int v1 = wordSortVal(w1), v2 = wordSortVal(w2);
	return v1 < v2;
}

int main() {
	int total_casos;
	cin >> total_casos;
	while (total_casos--) {
		int n, m;
		cin >> n >> m;
		multiset<Word> words;
		mapa.clear();
		while (m--) {
			string s;
			cin >> s;
			// cout << s << endl;
			Word w = Word(s);
			words.insert(w);
		}

		for (multiset<Word>::iterator it = words.begin(); it != words.end(); ++it) {
			cout << (*it).value << endl;
		}
		if (total_casos) cout << endl;
	}
}
