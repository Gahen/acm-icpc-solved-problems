#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <set>
#include <math.h>

using namespace std;


bool caminar(map<pair<int, int>, bool> orientacion, set<pair<int, int> > &ms, pair<int, int>  point, bool sentidoPositivo, bool direccionHorizontal, set<pair<pair<int, int>, pair<int, int> > > &segmentos) {
	set<pair<int, int> >::iterator  next_pair;
	cout << "sentido: " << (sentidoPositivo ? "+" : "-") << " dirección: " << (direccionHorizontal?"h":"v") << endl;
	if (direccionHorizontal) {
		// cout << point.first << " " << point.second << endl;
		set<pair<int, int> >::iterator it = (sentidoPositivo ? ms.lower_bound(point) : --ms.lower_bound(point));
		cout << (*it).second << " " << (*it).second << endl;
		while (it != ms.end()) {
			cout << point.second << " " << (*it).second << endl;
			if ((*it).second == point.second) break; // Termino
			if (sentidoPositivo && ms.begin() == it) { // Hack para terminar cuando estoy contando para el otro lado.
				it = ms.end();
				break;
			}
			sentidoPositivo ? ++it: --it; // Me desplazo en el sentido correcto.
		}

		next_pair = it;
			
	} else {
		next_pair = sentidoPositivo ? ms.lower_bound(point) : --ms.lower_bound(point);
	}

	if (next_pair == ms.end()) {
		// cout << "nope: " << (*next_pair).first << " " << (*next_pair).first << endl;
		return false; // terminé este camino.
	} else {
		segmentos.insert(make_pair(point, (*next_pair)));
		cout << "borrando: " << (*next_pair).first << " " << (*next_pair).second << endl;
		ms.erase(next_pair);
	}

	/* Esto merece una explicación, surge de pensar bien fuerte sobre como funcino set para los puntos.
	 * Si es horizontal entonces busco el próximo, partiendo de mi x, que tiene el mismo y.
	 * Si no busco el próximo x, que tenga el mismo x. Esto sale al instante, es la definición de lower_bound.
	 */
	// Defino hacia donde va el rayo mirando la orientación del espejo
	return caminar(orientacion, ms, (*next_pair), (orientacion[(*next_pair)] ? sentidoPositivo : !sentidoPositivo), !direccionHorizontal, segmentos);
}

int main() {
	while (!feof(stdin)) {
		set<pair<pair<int, int>, pair<int, int> > > segmentosA, segmentosB; // Par de pares de enteros, segmentos
		int r, c, m, n, x, y;
		scanf("%d %d %d %d", &r, &c, &m, &n);

		set <pair<int, int> > ms; // mirrors 
		map<pair<int, int>, bool> orientacion;
		while (m-- > 0 || n-- > 0) {
			int x,y;
			scanf("%d %d", &y, &x);
			// cout << "leyendo: x=" << x << ", y=" << y << endl;
			ms.insert(make_pair(x, y));
			orientacion.insert(make_pair(make_pair(x, y), m>=0));
		}

		// Obtengo todos los segmentos en el sentido original
		caminar(orientacion, ms, make_pair(1,1), true, true, segmentosA);
		for (set<pair<pair<int, int>, pair<int, int> > >::iterator it = segmentosA.begin(); it != segmentosA.end(); ++it) {
			cout << "de " << "(" << (*it).first.first << "," << (*it).first.second << ")";
			cout << " hasta " << "(" << (*it).second.first << "," << (*it).second.second << ")" << endl;
		}
		cout << "B" << endl;

		// Obtengo todos los segmentos al revés.
		caminar(orientacion, ms, make_pair(c,r), false, true, segmentosB);
		for (set<pair<pair<int, int>, pair<int, int> > >::iterator it = segmentosB.begin(); it != segmentosB.end(); ++it) {
			cout << "de " << "(" << (*it).first.first << "," << (*it).first.second << ")";
			cout << " hasta " << "(" << (*it).second.first << "," << (*it).second.second << ")" << endl;
		}
		cout << "FIN" << endl;
		break;
	}
}
