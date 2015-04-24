#include <vector>
using namespace std;

#define NUM_COEFF 12
typedef long double type_cep;
typedef int type_clusterNumber;
typedef double type_distance;
typedef type_distance type_distortion;
typedef unsigned long long int ulli;

class dataPoint{
public:
	vector<type_cep> coeff;
	type_clusterNumber clusterNumber;
	type_distance distance(dataPoint p);
	void add(dataPoint);
	void add(type_cep);
	void divide(double);
	void reset();
	dataPoint(vector<type_cep> v){
		coeff = v;
		clusterNumber = 0;
	};
};

class dataSet{
public:
	vector<dataPoint> universe;			//Set of all data points
	vector<dataPoint> classCentroid;	//Set of centroids
	vector<ulli> classCount ;			// Number of data in the class
	long iteration;
	double epsilon;				
	type_distortion avgDistortion;
	void classify();
	void updateClassCentroid();
	type_distortion calDistortion();
	void resetCentroids();
	void resetCounts();
	dataSet(string fileName);
	void printCentroids();
	void splitCentroids();
};