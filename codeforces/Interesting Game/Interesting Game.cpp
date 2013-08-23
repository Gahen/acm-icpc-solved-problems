#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <math.h>
#include <string.h>

using namespace std;

int INF = 100001;
int cribaR[100001];
bool calculados[100001];

map <long int, vector<pair<int,int> > > cribaS;

int mex(set<int> &nums) {
	int i = 0;
	while (true) {
		if (nums.count(i) == 0) {
			// cout << " mex: " << i << endl;
			return i;
		}
		i++;
	}
}

// Creamos una tabla de sumatorias para después tener una busqueda eficiente.
void llenarSumatoria() {
	for (int i=1; i < INF; i++) {
		for (int j=i+1; j < INF; j++) {
			long int t = (j*(j+1))/2 - ((i-1)*i)/2;
			if (t > INF) break;
			if (cribaS.count(t) == 0) {
				vector<pair<int,int> > v;
				v.push_back(make_pair(i,j));
				cribaS.insert( make_pair(t, v) );
			} else {
				cribaS[t].push_back(make_pair(i,j));
			}
		}
	}
}

// Calcula una tabla de valores de victoria (true|false) recursivamente.
int llenarJuegos(int n) {
	if (calculados[n]) return cribaR[n];
	if (n == 1 || cribaS.count(n) == 0) return false;
	set<int> nums;
	for (vector<pair<int,int> >::iterator it = cribaS[n].begin(); it != cribaS[n].end(); ++it) {
		int resultado = 0;
		int a = (*it).first, max = (*it).second;
		for (; a <= max; a++) {
			resultado = resultado ^ llenarJuegos(a);
		}
		nums.insert(resultado);
	}
	// cout << n << ": " << mex(nums) << endl;
	cribaR[n] = mex(nums);
	calculados[n] = true;
	return cribaR[n];
}

// Vuelve a calcular la victoria, se queda con la menor de las posibles.
int jugar(int n) {
	if (cribaR[n] > 0) {
		int minimo = INF;
		for (vector<pair<int,int> >::iterator it = cribaS[n].begin(); it != cribaS[n].end(); ++it) {
			int resultado = 0;
			int a = (*it).first, max = (*it).second;
			for (; a <= max; a++) {
				resultado = resultado ^ cribaR[a];
			}
			// nums.insert(resultado);
			if (resultado == 0) {
				// cout << "gano con: " << (*it).second - (*it).first + 1 << endl;
				minimo = min((*it).second - (*it).first + 1, minimo);
			}
		}
		return minimo;
	} else 
		return -1;
}

int main() {
	llenarSumatoria();
	for (int i = 0; i < INF; i++) {
		cribaR[i] = 0;
		calculados[i] = false;
	}
	cribaR[1] = 0;
	int n;
	cin >> n;
	llenarJuegos(n);
	cout << jugar(n);
}
