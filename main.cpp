#include "ConcurrentHashMap.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
int main() {
    ConcurrentHashMap map = ConcurrentHashMap::count_words("corpus");
    string key = "Pepe";
    string key2 = "False";
    string key3 = "Armando";
    map.addAndInc(key);
    map.addAndInc(key);
    map.addAndInc(key);
    map.addAndInc(key);
    map.addAndInc(key3);
    map.addAndInc(key3);
    map.addAndInc(key3);
    map.addAndInc(key3);
    map.addAndInc(key3);
    cout << map.member(key) << endl;
    cout << map.member(key2) << endl;

    
    pair< string, int > maximo = map.maximum(1);
    cout << maximo.first << ", " << maximo.second << endl;
    for (int i = 0; i < 26; i++) {
		for (auto it = map.map[i]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
			auto t = it.Siguiente();
			cout << t.first << " " << t.second << endl;
		}
    }

}