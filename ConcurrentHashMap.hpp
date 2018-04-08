#ifndef CONCURRENT_HASH_MAP_H__
#define CONCURRENT_HASH_MAP_H__
#include "ListaAtomica.hpp"
#include <string>
#include <list>
#include <iostream>
#define SIZE 26
#define ASCII_OFFSET 97
class ConcurrentHashMap {
    private:
        
        Lista< std::pair < std::string,int >* >* getLista(std::string* key) {
            char firstLetter = key->at(0);
            firstLetter = std::tolower(firstLetter, std::locale());
            //std::cout << "Adding: " << firstLetter << std::endl;
            int asciiCode = firstLetter;
            //std::cout << "ASCII CODE: " << asciiCode << std::endl;
            Lista< std::pair < std::string,int >* > * listOfLetter = map[asciiCode-ASCII_OFFSET];
            return listOfLetter;
        }

         Lista< std::pair < std::string,int >* >::Iterador getListIt(int mapPos) {
            Lista< std::pair < std::string,int >* > * list = map[mapPos];
            Lista< std::pair < std::string,int >* >::Iterador it = list->CrearIt();
            return it;
         }


    public:
        Lista<std::pair<std::string,int>* >* map[SIZE];
        ConcurrentHashMap() {
            std::cout << "Builing Concurrent Hash Map"<<std::endl;
            for(int i = 0; i < SIZE; i++) {
                map[i] = new Lista< std::pair < std::string, int >* >();
            }
        }

        static ConcurrentHashMap count_words(std::string archs) {
            return ConcurrentHashMap();   
        }

        static ConcurrentHashMap count_words(std::list<std::string> archs) {
            return ConcurrentHashMap();
        }

        static ConcurrentHashMap count_words(unsigned int n, std::list<std::string> archs) {
            return ConcurrentHashMap();
        }

        void addAndInc(std::string* key) {
            std::cout << "Tratando de Agregar o Incrementar: " << *key << std::endl;
            Lista< std::pair < std::string,int >* >* listOfLetter=getLista(key);
            //std::cout << "Lista: " << listOfLetter << std::endl;
            Lista< std::pair < std::string,int > *>::Iterador it = listOfLetter->CrearIt();
            //std::cout << "Iterador: " << listOfLetter << std::endl;
            while(it.HaySiguiente()){
                std::pair< std::string, int>* sig = it.Siguiente();
                if(sig->first.compare(*key)==0) {
                     std::cout << "Incrementando: " << *key << ": "<< sig->second<< std::endl;
                     sig->second++;
                     return;
                }
                it.Avanzar();
            }
            //si llego aca es porque no hay una entrada con esa key. Entonces la agregamos.
            std::cout << "Agregando: " << *key << std::endl;
            std::pair< std::string, int> * nuevo = new std::pair< std::string, int>();
            nuevo->first = *key;
            nuevo->second = 1;
            listOfLetter->push_front(nuevo);
        }

        bool member(std::string* key) {
            Lista< std::pair < std::string,int >* >* listOfLetter=getLista(key);
            //std::cout << "Lista: " << listOfLetter << std::endl;
            Lista< std::pair < std::string,int >* >::Iterador it = listOfLetter->CrearIt();
            //std::cout << "Iterador: " << listOfLetter << std::endl;
            while(it.HaySiguiente()){
                std::pair< std::string, int>* sig = it.Siguiente();
                if(sig->first.compare(*key)==0) {
                     return true;
                }
                it.Avanzar();
            }
            return false;
        }

        std::pair< std::string, int >* maximum(unsigned int nt) {
            std::pair< std::string, int>  *maximo;
            int maxCount = 0;
            for(int i = 0; i<SIZE; i++) {
                Lista< std::pair < std::string,int > *>::Iterador it = getListIt(i);
                while(it.HaySiguiente()) {
                    std::pair< std::string, int> *sig = it.Siguiente();
                    if(sig->second > maxCount) {
                        maximo = sig;
                        maxCount = sig->second;
                    }
                    it.Avanzar();
                }
            }
            return maximo;
        }

        static std::pair< std::string, unsigned int >* maximum(unsigned int p_archivos, unsigned int p_maximos, std::list<std::string> archs) {
            std::pair< std::string, unsigned int>  *maximo = new std::pair< std::string, unsigned int>();
            maximo->first = "No implementado";
            maximo->second = 1;
            return maximo;
        }

        ~ConcurrentHashMap() {
            std::cout << "Destroying Concurrent Hash Map"<<std::endl;
            for(int i = 0; i<SIZE; i++) {
                map[i]->~Lista();
            }
        }

};

#endif /* CONCURRENT_HASH_MAP_H__ */