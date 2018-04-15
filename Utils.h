
#ifndef UTILS_H__
#define UTILS_H__
#include <string>
#include <list>
#include <iostream>
#include <pthread.h>
#include <fstream>
#include "ConcurrentHashMap.h"

struct  {
    std::string arch;
    ConcurrentHashMap* map;
} typedef thread_struct;

void *count_words_t(void *args) {
    thread_struct* data=(thread_struct*) args;
    std::string arch = data->arch;
    ConcurrentHashMap* map = data->map;
    std::ifstream farch;
    farch.open(arch);
    std::string line;
    std::cout << "Corriendo" << std::endl;
    if (farch.is_open())
    {
        while ( getline (farch,line) )
        {
            map->addAndInc(line);
        }
        farch.close();
    } else {
        std::cout<<"No lo pudo abrir"<<std::endl;
    }
    pthread_exit(0);
}

#endif