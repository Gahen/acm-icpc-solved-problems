#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <string.h>

using namespace std;

int deDiez(int n) {
	int a = n/5 + 1;
	int b = n/10 + 1;

	return (b * ( (a%2==0?2:1) + a)) / 2; // combinaciones posibles usando los de 10
}

int jugar(int n) {
	int total = 0;
	do {
		int nn = n;
		do {
			total += deDiez(nn);
			nn -= 25;
		} while (nn>=0);
		n -= 50;
	} while (n>=0);
	return total;
}

int main() {
	while (true) {
		int n = 0;
		cin >> n;

		if (n==0) {
			break;
		} else { 
			cout << jugar(n) << endl;
		}
	}
}

