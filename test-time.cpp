#include <iostream>
#include <cstdlib>
#include <fstream>
#include "ConcurrentHashMap.h"
#include "time.h"

using namespace std;


int main(int argc, char **argv) {


 	fstream data;
    data.open("resultadosMaximos2", fstream::out);

	struct timespec start, stop;
    double accum1;
    double accum2;
	pair<string, unsigned int> p1;
    pair<string, unsigned int> p2;

	list<string> l = { "cien1", "cien2", "cien3", "cien4", "cien5","cien6","mil","cien7","cien8","cien9","cien10"};

	if (argc != 3) {
		cerr << "uso: " << argv[0] << " #tarchivos #tmaximum" << endl;
		return 1;
	}

	data << "normal;concurrent" << endl;
	for(int i = 0; i < 500; i++) {

		clock_gettime( CLOCK_REALTIME, &start);
		p1 = ConcurrentHashMap::maximum(atoi(argv[1]), atoi(argv[2]), l);
		clock_gettime( CLOCK_REALTIME, &stop);

		accum1 = ((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)) / 1E6;

		clock_gettime( CLOCK_REALTIME, &start);
		p2 = ConcurrentHashMap::concurrent_maximum(atoi(argv[1]), atoi(argv[2]), l);
		clock_gettime( CLOCK_REALTIME, &stop);

		accum2 = ((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)) / 1E6;

    if(accum1 > 0 && accum2 > 0){
		    data << accum1 << ";"<< accum2 << endl;
        cout << p1.first << " " << p1.second << " en: " << accum1 << " ms" << endl;
        cout << p2.first << " " << p2.second << " en: " << accum2 << " ms" << endl;
    }
	}
	data.close();

	return 0;
}
