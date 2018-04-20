#include <iostream>
#include <cstdlib>
#include <fstream>
#include "ConcurrentHashMap.h"
#include "time.h"

using namespace std;


int main(int argc, char **argv) {

 
 	fstream data;
    data.open("resultadosMaximos", fstream::out);

	struct timespec start, stop;
    double accum;
	pair<string, unsigned int> p1;
    pair<string, unsigned int> p2;

	list<string> l = { "cien1", "cien2", "cien3", "cien4", "cien5" };

	if (argc != 3) {
		cerr << "uso: " << argv[0] << " #tarchivos #tmaximum" << endl;
		return 1;
	}

	data << "normal;concurrent" << endl;
	for(int i = 0; i <= 1000; i++) {

		clock_gettime( CLOCK_REALTIME, &start);
		p1 = ConcurrentHashMap::maximum(atoi(argv[1]), atoi(argv[2]), l);
		clock_gettime( CLOCK_REALTIME, &stop);

		accum = ((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)) / 1E6;
            

		cout << p1.first << " " << p1.second << " en: " << accum << " ms" << endl;

		data << accum << ";";

		clock_gettime( CLOCK_REALTIME, &start);
		p2 = ConcurrentHashMap::concurrent_maximum(atoi(argv[1]), atoi(argv[2]), l);
		clock_gettime( CLOCK_REALTIME, &stop);

		accum = ((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)) / 1E6;

		data << accum << endl;
		cout << p2.first << " " << p2.second << " en: " << accum << " ms" << endl;

	}
	data.close();

	return 0;
}