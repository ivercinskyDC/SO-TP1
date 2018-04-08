#include "ConcurrentHashMap.hpp"
#include <string>

using namespace std;
int main() {
    ConcurrentHashMap* map = new ConcurrentHashMap();
    string key = "Pepe";
    string key2 = "False";
    string key3 = "Armando";
    map->addAndInc(&key);
    map->addAndInc(&key);
    map->addAndInc(&key);
    map->addAndInc(&key);
    map->addAndInc(&key3);
    map->addAndInc(&key3);
    map->addAndInc(&key3);
    map->addAndInc(&key3);
    map->addAndInc(&key3);
    cout << map->member(&key) << endl;
    cout << map->member(&key2) << endl;

    pair< string, int >* maximo = map->maximum(1);
    cout << maximo->first << ", " << maximo->second << endl;
    delete map;

}