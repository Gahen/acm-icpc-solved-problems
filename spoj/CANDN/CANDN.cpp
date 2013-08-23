#include <stdio.h>
#include <string>
#include <set>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdlib.h>

using namespace std;

int INF = 99999999;

vector <int> dijkstra(vector <vector<pair <int, int> > > &lista, int nodoInicial) {
	int n= lista.size();
	vector <int> dist(n,INF);
	vector <bool> toc(n, false);
	dist[nodoInicial] = 0;
	int t = nodoInicial;
	for (int i=0; i<n; i++) {
		toc[t] = true;
		for (int i=0; i < lista[t].size(); i++) {
			if (dist[lista[t][i].first] > dist[t] + lista[t][i].second) {
				dist[lista[t][i].first] = dist[t] + lista[t][i].second;
			}
		}
		for (int i=0; i<n; i++)
			if (toc[t] == true || (toc[i] == false && dist[i] < dist[t]))
				t = i;
	}
	return dist;
}

int main() {
	while (!feof(stdin)) {
		double l;
		int j, b, c, n, s;
		scanf("%d %d %d %d %d", &j, &b, &c, &n, &s);
		if (j== -1) break;
		int i = s;
		vector <vector<pair<int, int> > > nodos;
		for (int i = 0; i <= j; i++) {
			vector<pair<int, int> > v;
			nodos.push_back(v);
		}

		while (i--) {
			int e1, e2, l;
			scanf("%d %d %d", &e1, &e2, &l);
			// cout << e1 << " -> " << e2 << " : " << l << endl;
			nodos[e1].push_back(make_pair(e2, l));
			nodos[e2].push_back(make_pair(e1, l));
		}

		vector <int> db = dijkstra(nodos, b);
		vector <int> dc = dijkstra(nodos, c);
		vector <int> dn = dijkstra(nodos, n);

		int dnmax = db[n], dcmax = db[c];
		int djmax = 0; // distancia juntos max
		// busco el camino mínimo común con una especie de BFS
		for (int i = 1; i < dc.size(); i++) {
			if (db[i] + dc[i] <= dcmax && db[i] + dn[i] <= dnmax) { // Es un camino mínimo
				if (dnmax - dn[i] == dcmax - dc[i])
					djmax = max(dnmax - dn[i], djmax);
			}
		}

		cout << djmax << " " << (dcmax-djmax) << " " << (dnmax-djmax) << endl;
	}
}

// ANDUVO =)
