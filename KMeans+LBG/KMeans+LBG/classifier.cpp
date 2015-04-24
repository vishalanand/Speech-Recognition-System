#include <iostream>
#include <fstream>
#include "kmeans.h"
#include "config.h"

using namespace std;

int main(int argc, char const *argv[])
{
	string fileName = "universe.txt";
	
	dataSet data(fileName);
	type_distortion last_distortion =0;
	int i = 1;

	cout << i << ' '<< data.avgDistortion << endl;
	data.printCentroids();
	
	// while(data.avgDistortion - last_distortion > ERROR)
	for (int i = 1; i < CODE_BOOK_SIZE; i=i*2)
	{
		data.splitCentroids();
		data.classify();
		data.updateClassCentroid();
		data.calDistortion();
		last_distortion = data.avgDistortion;

		cout << i << ' '<< data.avgDistortion << endl;
		data.printCentroids();
		cout << endl;
	}
	return 0;
}