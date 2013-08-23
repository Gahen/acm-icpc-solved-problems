#include <iostream>
#include <string>
#include <set>
#include <math.h>

using namespace std;

int main() {
	int casos;
	cin >> casos;

	while (casos--) {
		int total_piedras = 0, piedra;
		multiset<int> piedras;
		cin >> total_piedras;
		int i = total_piedras;
		while (i--) {
			cin >> piedra;
			piedras.insert(piedra);
		}
		int total = 0;
		while (total_piedras-- -1) {
			int p1, p2; 
			p1 = *piedras.lower_bound(0); 
			piedras.erase(piedras.lower_bound(0));
			p2 = p1 + *piedras.lower_bound(0); 
			piedras.erase(piedras.lower_bound(0));
			total += p2;
			// cout << p1 << " " << p2 << "=" << total << endl;
			piedras.insert(p2);
		}

		cout << total << endl;
	}
}
