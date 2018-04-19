
#ifndef UTILS_H__
#define UTILS_H__
#include <string>
#include <iostream>
#include <pthread.h>
#include <fstream>
#include <atomic>
#include <vector>
#include "ConcurrentHashMap.h"

struct  {
    std::vector<std::string>* archs;
    ConcurrentHashMap* map;
    std::atomic_int* index;
} typedef thread_struct;

struct {
    ConcurrentHashMap* map;
    Lista< std::pair < std::string,int >* >* maximos;
} typedef max_thread_struct;

int get_current(std::atomic_int* index, int current){
    while(!index->compare_exchange_strong(current, current+1)){
            current = index->load();
    };
    //current++;
    return *index;
}

void *count_words_t(void *args) {
    thread_struct* data=(thread_struct*) args;
    std::vector<std::string>* archs = data->archs;
    ConcurrentHashMap* map = data->map;
    std::atomic_int* index = data->index;

    int current = get_current(index, -1);
    
    //std::cout<<"Getting: "<<current<<std::endl;
    //std::cout<<"archs: "<<archs->size()<<std::endl;

    while(current < archs->size()){
        //std::cout<<"Processing File: "<<archs->at(current)<<std::endl;
        map->process_file(archs->at(current));
        current = get_current(index, current);
    }
    
    pthread_exit(0);
}

void *maximum_t(void *args) {
    max_thread_struct* data=(max_thread_struct*) args;
    ConcurrentHashMap* map = data->map;
    Lista< std::pair < std::string,int >* >* maximos = data->maximos;
    std::pair < std::string,int >* maximo;
    int maxCount = 0;
    for(int i = 0; i<SIZE; i++) {
        Lista< std::pair < std::string,int >* >* letraI = map->map[i];
        Lista< std::pair < std::string,int >* >::Iterador it = letraI->CrearIt();
        while(it.HaySiguiente()) {
            std::pair< std::string, int>* sig = it.Siguiente();
            if(sig->second > maxCount) {
                maximo = sig;
                maxCount = sig->second;
            }
            it.Avanzar();
        }
    }
    maximos->push_front(maximo);
    
    pthread_exit(0);
}

void *create_concurrent_hash_map(void * args){
    // thread_struct* data=(thread_struct*) args;
    // data->
    pthread_exit(0);
}


#endif