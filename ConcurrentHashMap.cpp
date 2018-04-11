#include "ConcurrentHashMap.h"

ConcurrentHashMap::ConcurrentHashMap() {
    //std::cout << "Builing Concurrent Hash Map"<<std::endl;
    for(int i = 0; i < SIZE; i++) {
        map[i] = new Lista< std::pair < std::string, int > >();
    }
    
}

        

ConcurrentHashMap ConcurrentHashMap::count_words(std::list<std::string> archs) {
    pthread_t pid;
    pthread_create(&pid,NULL,count_words_t,&archs.front());
    ConcurrentHashMap map = ConcurrentHashMap();
    pthread_join(pid,NULL);
    return map;
}

ConcurrentHashMap ConcurrentHashMap::count_words(unsigned int n, std::list<std::string> archs) {
    return ConcurrentHashMap();
}

void ConcurrentHashMap::addAndInc(std::string key) {
        ///std::cout << "Tratando de Agregar o Incrementar: " << *key << std::endl;
    Lista< std::pair < std::string,int > >* listOfLetter=getLista(key);
    //std::cout << "Lista: " << listOfLetter << std::endl;
    Lista< std::pair < std::string,int > >::Iterador it = listOfLetter->CrearIt();
    //std::cout << "Iterador: " << listOfLetter << std::endl;
    while(it.HaySiguiente()){
        std::pair< std::string, int> sig = it.Siguiente();
        if(sig.first.compare(key)==0) {
                //std::cout << "Incrementando: " << *key << ": "<< sig->second<< std::endl;
                //hay que usar un semaforo para el incrementar el second++
                sig.second++;
                return;
        }
        it.Avanzar();
    }
    //si llego aca es porque no hay una entrada con esa key. Entonces la agregamos.
    //std::cout << "Agregando: " << *key << std::endl;
    std::pair< std::string, int> nuevo;
    nuevo.first = key;
    nuevo.second = 1;
    listOfLetter->push_front(nuevo);
}

bool ConcurrentHashMap::member(std::string key) {
    Lista< std::pair < std::string,int > >* listOfLetter=getLista(key);
    //std::cout << "Lista: " << listOfLetter << std::endl;
    Lista< std::pair < std::string,int > >::Iterador it = listOfLetter->CrearIt();
    //std::cout << "Iterador: " << listOfLetter << std::endl;
    while(it.HaySiguiente()){
        std::pair< std::string, int> sig = it.Siguiente();
        if(sig.first.compare(key)==0) {
                return true;
        }
        it.Avanzar();
    }
    return false;
}

std::pair< std::string, int > ConcurrentHashMap::maximum(unsigned int nt) {
    std::pair< std::string, int>  maximo;
    int maxCount = 0;
    for(int i = 0; i<SIZE; i++) {
        Lista< std::pair < std::string,int > >::Iterador it = getListIt(i);
        while(it.HaySiguiente()) {
            std::pair< std::string, int> sig = it.Siguiente();
            if(sig.second > maxCount) {
                maximo = sig;
                maxCount = sig.second;
            }
            it.Avanzar();
        }
    }
    return maximo;
}

        

ConcurrentHashMap::~ConcurrentHashMap() {
    std::cout << "Destroying Concurrent Hash Map"<<std::endl;
    for(int i = 0; i<SIZE; i++) {
        map[i]->~Lista();
    }
}

ConcurrentHashMap ConcurrentHashMap::count_words(std::string arch) {
    std::ifstream farch;
    farch.open(arch);
    std::string line;

    ConcurrentHashMap cp = ConcurrentHashMap();
    if (farch.is_open())
    {
        while ( getline (farch,line) )
        {
            cp.addAndInc(line);
        }
        farch.close();
    } else {
        std::cout<<"No lo pudo abrir"<<std::endl;
    }

    return cp;

}

std::pair< std::string, unsigned int > ConcurrentHashMap::maximum(unsigned int p_archivos, unsigned int p_maximos, std::list<std::string> archs) {
    std::pair< std::string, unsigned int>  maximo;
    maximo.first = "No implementado";
    maximo.second = 1;
    return maximo;
}

