#include <iostream>
#include "ConcurrentHashMap.h"

using namespace std;

int main(void) {
	ConcurrentHashMap h;
	int i;
	
	h = ConcurrentHashMap::count_words("corpus");
	cout<<"Corriendo"<<endl;
	for (i = 0; i < 26; i++) {
		for (auto it = h.map[i]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
			auto t = it.Siguiente();
			cout << t->first << " " << t->second << endl;
		}
	}

	return 0;
}

