
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
    Lista<std::pair< std::string, int>*>* maximos;
    std::atomic_int* index;
} typedef max_thread_struct;

struct  {
    ConcurrentHashMap* hm;
    std::vector<ConcurrentHashMap*>* hashMaps;
    std::atomic_int* index;
} typedef merge_struct;

int get_current(std::atomic_int* index){
    return ++(*index);
}

void *count_words_t(void *args) {
    thread_struct* data=(thread_struct*) args;
    std::vector<std::string>* archs = data->archs;
    ConcurrentHashMap* map = data->map;
    std::atomic_int* index = data->index;

    int current = get_current(index);
    
    //std::cout<<"Getting: "<<current<<std::endl;
    //std::cout<<"archs: "<<archs->size()<<std::endl;

    while(current < archs->size()){
        //std::cout<<"Processing File: "<<archs->at(current)<<std::endl;
        map->process_file(archs->at(current));
        current = get_current(index);
    }
    
    pthread_exit(0);
}

void *maximum_t(void *args) {
    max_thread_struct* data=(max_thread_struct*) args;
    ConcurrentHashMap* map = data->map;
    std::atomic_int* index = data->index;
    std::pair < std::string,int >* maximo = NULL;

    int current = get_current(index);
    while(current < SIZE){
        
        Lista< std::pair < std::string,int >* >* letraI = map->map[current];
        Lista< std::pair < std::string,int >* >::Iterador it = letraI->CrearIt();
        while(it.HaySiguiente()) {
            std::pair< std::string, int>* sig = it.Siguiente();
            if(maximo == NULL || sig->second > maximo->second) {
                maximo = sig;
            }
            it.Avanzar();
        }
        if(maximo != NULL)
            data->maximos->push_front(maximo);
        current = get_current(index);
    }
//    std::cout<<"sdsd"<<std::endl;
    pthread_exit(0);
}

void *create_concurrent_hash_map(void * args){
    thread_struct* data=(thread_struct*) args;
    std::vector<std::string>* archs = data->archs;
    std::atomic_int* index = data->index;
    ConcurrentHashMap* hm = data->map;

    int current = get_current(index);


    while(current < archs->size()){
        hm->process_file(archs->at(current));
        current = get_current(index);
    }
    pthread_exit(0);
}


void *merge_hash_maps(void * args){
    merge_struct* data=(merge_struct*) args;
    std::atomic_int* index = data->index;
    ConcurrentHashMap* hm = data->hm;
    std::vector<ConcurrentHashMap*>* hashMaps = data->hashMaps;

    int current = get_current(index);
    while(current < SIZE){
        for(int i = 0; i < hashMaps->size();i++){
            Lista< std::pair < std::string,int >* >::Iterador it = (*hashMaps)[i]->map[current]->CrearIt();
            while(it.HaySiguiente()) {
                std::pair<std::string,int> * elem = it.Siguiente();
                hm->add_and_inc(elem->first,elem->second);
                it.Avanzar();
            }
        } 
        current = get_current(index);
    }
    pthread_exit(0);
}

#endif