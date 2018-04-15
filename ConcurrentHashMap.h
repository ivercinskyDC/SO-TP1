#ifndef CONCURRENT_HASH_MAP_H__
#define CONCURRENT_HASH_MAP_H__
#include "ListaAtomica.hpp"
#include <string>
#include <list>
#include <iostream>
#include <pthread.h>
#include <fstream>

#define SIZE 26
#define ASCII_OFFSET 97
class ConcurrentHashMap {
    public:
    Lista<std::pair<std::string,int> *>* map[SIZE];
    ConcurrentHashMap();
    ConcurrentHashMap(std::string arch);
    ConcurrentHashMap(unsigned int nt, std::list<std::string> archs);
    static ConcurrentHashMap count_words(std::string arch);
    static ConcurrentHashMap count_words(std::list<std::string> archs);
    static ConcurrentHashMap count_words(unsigned int n, std::list<std::string> archs);
    ~ConcurrentHashMap();
    std::pair< std::string, int > maximum(unsigned int nt);
    static std::pair< std::string, unsigned int > maximum(unsigned int p_archivos, unsigned int p_maximos, std::list<std::string> archs);
    bool member(std::string key);
    void addAndInc(std::string key);
    
    private:
        
        pthread_mutex_t addAndIncMutex[SIZE];

        int getHashKey(std::string key) {
            char firstLetter = key.at(0);
            int asciiCode = std::tolower(firstLetter, std::locale());
            return asciiCode;
        }

        
        Lista< std::pair < std::string,int >* >* getLista(std::string key) {
            int asciiCode = getHashKey(key);
            //std::cout << "ASCII CODE: " << asciiCode << std::endl;
            Lista< std::pair < std::string,int >* >* listOfLetter = map[asciiCode-ASCII_OFFSET];
            return listOfLetter;
        }

         Lista< std::pair < std::string,int >* >::Iterador getListIt(int mapPos) {
            Lista< std::pair < std::string,int >* > * list = map[mapPos];
            Lista< std::pair < std::string,int >* >::Iterador it = list->CrearIt();
            return it;
         }

         void lockAddAndIncMutex(std::string key) {
            int asciiCode = getHashKey(key);
            pthread_mutex_lock(&addAndIncMutex[asciiCode-ASCII_OFFSET]);
         } 

         void unlockAddAndIncMutex(std::string key) {
            int asciiCode = getHashKey(key);
            pthread_mutex_unlock(&addAndIncMutex[asciiCode-ASCII_OFFSET]);   
         }

          
    
};
#endif /* CONCURRENT_HASH_MAP_H__ */