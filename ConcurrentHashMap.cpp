#include "ConcurrentHashMap.h"
#include "Utils.h"
#include <atomic>
#include <vector>

ConcurrentHashMap::ConcurrentHashMap() {
    //std::cout << "Builing Concurrent Hash Map"<<std::endl;
    for(int i = 0; i < SIZE; i++) {
        map[i] = new Lista< std::pair < std::string, int >* >();
        pthread_mutex_init(&addAndIncMutex[i],NULL);
    }
    
}

ConcurrentHashMap::ConcurrentHashMap(std::string arch) : ConcurrentHashMap() {
    process_file(arch);
}


ConcurrentHashMap::ConcurrentHashMap(unsigned int nt, std::list<std::string> archs) : ConcurrentHashMap() {
    std::atomic_int index(-1);
    pthread_t threads[nt];
    std::cout<<"Lanzando "<<nt<<" threads" <<std::endl;

    std::vector<std::string> vector;
    for (std::list<std::string>::iterator it=archs.begin(); it != archs.end(); ++it)
        vector.push_back(*it);


    for(int i = 0; i < nt; i++){
        thread_struct data= {&vector, this, &index};
        pthread_create(&threads[i],NULL,count_words_t,&data);
    }

    std::cout<<"Esperando "<<nt<<" threads" <<std::endl;
    for(int i = 0; i < nt; i++){
        pthread_join(threads[i],NULL);
    }

}

ConcurrentHashMap ConcurrentHashMap::count_words(std::string arch) {
    return ConcurrentHashMap(arch);
}

ConcurrentHashMap ConcurrentHashMap::count_words(std::list<std::string> archs) {
    return ConcurrentHashMap(archs.size(),archs);
}

ConcurrentHashMap ConcurrentHashMap::count_words(unsigned int n, std::list<std::string> archs) {
    return ConcurrentHashMap(n, archs);
}

void ConcurrentHashMap::process_file(std::string arch){
    std::ifstream farch;
    farch.open(arch);
    std::string line;
    if (farch.is_open())
    {
        while ( getline (farch,line) )
        {
            add_and_inc(line);
        }
        farch.close();
    } else {
        std::cout<<"No lo pudo abrir"<<std::endl;
    }
}

void ConcurrentHashMap::add_and_inc(std::string key) {
    ///std::cout << "Tratando de Agregar o Incrementar: " << *key << std::endl;
    //UN ARRAY DE MUTEX, UN POR CADA LETRA.
    lock_add_and_inc_mutex(key);
    Lista< std::pair < std::string,int >* >* listOfLetter = get_lista(key);
    //std::cout << "Lista: " << listOfLetter << std::endl;
    Lista< std::pair < std::string,int >* >::Iterador it = listOfLetter->CrearIt();
    //std::cout << "Iterador: " << listOfLetter << std::endl;
    
    
    while(it.HaySiguiente()){
        std::pair< std::string, int>* sig = it.Siguiente();
        if(sig->first.compare(key)==0) {
                //std::cout << "Incrementando: " << *key << ": "<< sig->second<< std::endl;
                
                //pthread_mutex_lock(&addAndIncMutex);
                sig->second++;
                unlock_add_and_inc_mutex(key);
                return;
        }
        it.Avanzar();
    }
    
    //si llego aca es porque no hay una entrada con esa key. Entonces la agregamos.
    //std::cout << "Agregando: " << *key << std::endl;

    std::pair< std::string, int>* nuevo = new std::pair< std::string, int>();
    nuevo->first = key;
    nuevo->second = 1;
    listOfLetter->push_front(nuevo);
    unlock_add_and_inc_mutex(key);
    
}

bool ConcurrentHashMap::member(std::string key) {
    Lista< std::pair < std::string,int >* >* listOfLetter = get_lista(key);
    //std::cout << "Lista: " << listOfLetter << std::endl;
    Lista< std::pair < std::string,int >* >::Iterador it = listOfLetter->CrearIt();
    //std::cout << "Iterador: " << listOfLetter << std::endl;
    while(it.HaySiguiente()){
        std::pair< std::string, int>* sig = it.Siguiente();
        if(sig->first.compare(key)==0) {
                return true;
        }
        it.Avanzar();
    }
    return false;
}

std::pair< std::string, int > ConcurrentHashMap::maximum(unsigned int nt) {
    std::pair< std::string, int> * maximo;
    int maxCount = 0;
    for(int i = 0; i<SIZE; i++) {
        Lista< std::pair < std::string,int >* >::Iterador it = get_list_it(i);
        while(it.HaySiguiente()) {
            std::pair< std::string, int>* sig = it.Siguiente();
            if(sig->second > maxCount) {
                maximo = sig;
                maxCount = sig->second;
            }
            it.Avanzar();
        }
    }
    return *maximo;
}

        

ConcurrentHashMap::~ConcurrentHashMap() {
    //std::cout << "Destroying Concurrent Hash Map"<<std::endl;
    for(int i = 0; i<SIZE; i++) {
        map[i]->~Lista();
        pthread_mutex_destroy(&addAndIncMutex[i]);
    }
}

std::pair< std::string, unsigned int > ConcurrentHashMap::maximum(unsigned int p_archivos, unsigned int p_maximos, std::list<std::string> archs) {
    std::pair< std::string, unsigned int>  maximo;
    maximo.first = "No implementado";
    maximo.second = 1;
    return maximo;
}


