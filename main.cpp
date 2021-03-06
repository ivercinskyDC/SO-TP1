#include "ConcurrentHashMap.h"
#include <string>
#include <iostream>
#include <cstdlib>
using namespace std;
ConcurrentHashMap map = ConcurrentHashMap();
pthread_mutex_t semaforo;
void *addWord(void* word){

    string* w = static_cast<string*>(word);
    //pthread_mutex_lock(&semaforo);
    map.add_and_inc(*w);
    //pthread_mutex_unlock(&semaforo);
    pthread_exit(0);
}

int main() {
    
    string key = "Pepe";
    string key2 = "False";
    string key3 = "Armando";

    int n_threads = 100;
    pthread_mutex_init(&semaforo, NULL);
    pthread_t threads[n_threads];
    for(int i = 0; i<n_threads; i++){
        if(i % 3 == 0) {
            pthread_create(&threads[i],NULL,addWord,static_cast<void*>(new string("Pepe")));
        } else if (i % 3 == 1) {
            pthread_create(&threads[i],NULL,addWord,static_cast<void*>(new string("Bosa")));    
        } else {
            pthread_create(&threads[i],NULL,addWord,static_cast<void*>(new string("Titere")));
        }
        
    }
    for(int i = 0; i<n_threads; i++){
        pthread_join(threads[i],NULL);
    }
    pthread_mutex_destroy(&semaforo);
    cout<<"Done Adding"<<endl;
    pair< string, int > maximo = map.maximum(1);
    //cout << "Maximo: "<< maximo.first << ", " << maximo.second << endl;
    for (int i = 0; i < 26; i++) {
		for (auto it = map.map[i]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
			auto t = it.Siguiente();
			//cout << char(i+97) << ": " << t->first << " " << t->second << endl;
		}
    }

    ConcurrentHashMap cp1 = ConcurrentHashMap("corpus");
    cout<<"creo cp1"<<endl;
    ConcurrentHashMap cp2 = ConcurrentHashMap(1,{"corpus","corpus"});
    cout<<"creo cp2"<<endl;
    for (int i = 0; i < 26; i++) {
		for (auto it = cp2.map[i]->CrearIt(); it.HaySiguiente(); it.Avanzar()) {
			auto t = it.Siguiente();
		//	cout << char(i+97) << ": " << t->first << " " << t->second << endl;
		}
    }

    cout<<"test maximo"<<endl;

    pair< string, int > max = ConcurrentHashMap::maximum(1,2,{"pepe","pepa"});
    cout<<"maximum: "<<max.first<<" "<<max.second<<endl;
    

}