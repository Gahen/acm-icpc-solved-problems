#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <math.h>
#include <stdlib.h>

using namespace std;

int n;
struct trie {
	map <char, int> sig;
	bool final;
};

trie t[100000];
void init() {
	n = 1;
	t[0].sig.clear();
	t[0].final = false;
}

void insertar(string st) {
	int pos = 0;
	for (int i = 0; i < st.size(); i++) {
		if (t[pos].sig.find(st[i]) == t[pos].sig.end()) { // Si no está aún la letra en el trie
			t[pos].sig[st[i]] = n;
			t[n].sig.clear();
			t[n].final = false;
			n++;
		}
		pos = t[pos].sig[st[i]]; // La próxima posición de trie será la de la última letra insertada.
	}
	t[pos].final = true;
}

int main() {
	while (!feof(stdin)) {
		int total_nombres;
		string st;
		cin >> total_nombres;
		if (total_nombres == -1) break;
		int  i = total_nombres;
		string nombresA[total_nombres], nombresB[total_nombres];

		init();

		while (i--) {
			string s;
			cin >> s;
			insertar(s);
			nombresA[i] = s;
		}

		i = total_nombres;
		while (i--) {
			string s;
			cin >> s;
			insertar(s);
			nombresB[i] = s;
		}

		int counterA[100000], counterB[100000];
		int max = 0;
		i = 100000;
		while (i--) {
			counterA[i] = 0;
			counterB[i] = 0;
		}
		
		for (i=0; i < total_nombres; i++) {
			int x = 0;
			for (int j=0; j < nombresA[i].size(); j++) {
				x = t[x].sig[nombresA[i][j]];
				counterA[x]++;
			}
		}

		for (i=0; i < total_nombres; i++) {
			int x = 0;
			for (int j=0; j < nombresB[i].size(); j++) {
				x = t[x].sig[nombresB[i][j]];
				counterB[x]++;
			}
		}

		i = 100000;
		while (i--) {
			max += min(counterA[i], counterB[i]);
		}

		cout << max << endl;
	}
}

// Anduvo =)
