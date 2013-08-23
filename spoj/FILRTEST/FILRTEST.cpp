#include <stdio.h>
#include <string>
#include <iostream>
#include <math.h>
#include <stdlib.h>

using namespace std;

int main() {
	while (!feof(stdin)) {
		double l;
		string st;
		cin >> l >> st;
		if (l== -1) break;
		double size = st.size();
		long int i=1, j=0;
		long int bordes[st.size()];
		bordes[0] = 0;
		while (i<size) {
			while (j>0 && st[i] != st[j])
				j = bordes[j-1];
			if (st[i] == st[j])
				j++;
			bordes[i++] = j;
		}
		long int borde = bordes[st.size()-1];
		long int max = 0;
		if (l >= size) {
			l -= borde;
			max = floor(l/(size-borde));
			// cout << l/(size-borde) << endl;
		}
		// cout << "borde: " << borde << endl;
		cout << max << endl;
	}
}
