
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
    thread_struct* data=(thread_struct*) args;
    ConcurrentHashMap* map = data->map;
    std::atomic_int* index = data->index;
    std::vector<std::string>* archs = data->archs;

    int current = get_current(index, -1);

    while(current < archs->size()){
        map->process_file(archs->at(current));
        current = get_current(index, current);
    }
    
    pthread_exit(0);
}

void *create_concurrent_hash_map(void * args){
    thread_struct* data=(thread_struct*) args;
    std::vector<std::string>* archs = data->archs;
    std::atomic_int* index = data->index;
    ConcurrentHashMap* hm = data->map;

    int current = get_current(index, -1);

    while(current < archs->size()){
        hm->process_file(archs->at(current));
        current = get_current(index, current);
    }
    pthread_exit(0);
}


#endif