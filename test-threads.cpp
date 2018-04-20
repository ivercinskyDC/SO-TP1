#include <iostream>
#include <cstdlib>
#include <fstream>
#include "ConcurrentHashMap.h"
#include "time.h"

using namespace std;


int main(int argc, char **argv) {


 	fstream data;
    data.open("resultadosThreads", fstream::out);

	struct timespec start, stop;
    double accum1;

	pair<string, unsigned int> p1;
    pair<string, unsigned int> p2;

	list<string> l = { "cien1", "cien2", "cien3", "cien4", "cien5","cien6","mil","cien7","cien8","cien9","cien10"};

	// if (argc != 3) {
	// 	cerr << "uso: " << argv[0] << " #tarchivos #tmaximum" << endl;
	// 	return 1;
	// }

	data << "normal;concurrent;threads" << endl;
	for(int t = 1; t < 11; t++){
		double accum1 = 0;
		double accum2 = 0;
		int n1 = 0;
		int n2 = 0;
		double time = 0;
		for(int i = 0; i < 500; i++) {
			clock_gettime( CLOCK_REALTIME, &start);
			p1 = ConcurrentHashMap::maximum(t, t, l);
			clock_gettime( CLOCK_REALTIME, &stop);

			time = ((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)) / 1E6;
			if(time > 0){
				accum1 += time;
				n1++;
			}

			clock_gettime( CLOCK_REALTIME, &start);
			p2 = ConcurrentHashMap::concurrent_maximum(t, t, l);
			clock_gettime( CLOCK_REALTIME, &stop);

			time = ((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec)) / 1E6;
			if(time > 0){
				accum2 += time;
				n2++;
			}
		}
		data<< accum1/n1 << ";" << accum2/n2 << ";" << t << endl;
		cout << accum1/n1 << ";" << accum2/n2 << ";" << t << endl;
	}
	
	data.close();

	return 0;
}
