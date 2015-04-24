#include "kmeans.h"
#include <cmath>
#include <iostream>
#include <fstream>

#define EPS 0.00001


using namespace std;

type_distance dataPoint::distance(dataPoint p){
	double weights[] = {1,3,7,13,19,22,25,33,42,50,56,61};
	double sum = 0;
	for (int i = 0; i < coeff.size(); ++i)
	{
		sum += weights[i]*(coeff[i]-p.coeff[i])*(coeff[i]-p.coeff[i]);
	}
	// cout << "Dist : " << sqrt(sum) << " sum " << sum;
	return sqrt(sum);
}

void dataPoint::add(dataPoint p){
	for (int i = 0; i < coeff.size(); ++i)
	{
		coeff[i] += p.coeff[i];
	}
}

void dataPoint::add(type_cep data){
	for (int i = 0; i < coeff.size(); ++i)
	{
		coeff[i] += data;
	}
}

void dataPoint::divide(double data){
	for (int i = 0; i < coeff.size(); ++i)
	{
		coeff[i] /= data;
	}
}

void dataPoint::reset(){
	for (int i = 0; i < coeff.size(); ++i)
	{
		coeff[i] = 0.0;
	}
}

void dataSet::classify(){
	resetCounts();
	for (ulli i = 0; i < universe.size(); ++i)
	{
		dataPoint point = universe[i];
		//Change to max limit
		type_distance min_dist = 10000000.0;
		for (unsigned int i = 0; i < classCentroid.size(); ++i)
		{
			long double dist = point.distance(classCentroid[i]) ;
			// The type_distance will be float hence to compare floats
			if(dist-min_dist < EPS){
				min_dist = dist;
				point.clusterNumber = i;
			}
		}
		universe[i] = point;
		classCount[point.clusterNumber]++;
	}
}

void dataSet::updateClassCentroid(){
	resetCentroids();
	// printCentroids();
	for (ulli i = 0; i < universe.size(); ++i)
	{
		dataPoint point = universe[i];
		classCentroid[point.clusterNumber].add(point);
	}
	// printCentroids();
	for (ulli i = 0; i < classCount.size(); ++i)
	{
		classCentroid[i].divide(classCount[i]);
	}
	// printCentroids();
}

type_distortion dataSet::calDistortion(){
	type_distortion distortion = 0;
	for (ulli i = 0; i < universe.size(); ++i)
	{
		dataPoint point = universe[i];
		dataPoint centroid = classCentroid[point.clusterNumber];
		distortion += point.distance(centroid);
	}
	avgDistortion = distortion / (type_distortion) universe.size();
	return avgDistortion;
}

void dataSet::resetCentroids(){
	for (ulli i = 0; i < classCentroid.size(); ++i)		
	{
		classCentroid[i].reset();
	}
}
void dataSet::resetCounts(){
	for (ulli i = 0; i < classCount.size(); ++i)
	{
		classCount[i] = 0;
	}
}

dataSet::dataSet(string fileName){
	ifstream file(fileName);
	if (!file.is_open()){
		cout << "Cannot open File ";
		exit(1);
	}

	long double data = 0;
	vector<type_cep> temp;
	classCentroid.push_back(dataPoint(temp));
	int count = 0;
	while(file.good())
	{
		count++;
		file >> data;
		temp.push_back(data);
		if(count % 12 == 0)
		{
			universe.push_back(dataPoint(temp));
			classCentroid[0] = (dataPoint(temp));
			temp.clear();
		}
	}
	classCount.push_back(universe.size());
	updateClassCentroid();
	calDistortion();
	iteration = 0;
	epsilon = 0.0001;
	file.close();
}

void dataSet::printCentroids(){
	for (int i = 0; i < classCentroid.size(); ++i)
	{
		dataPoint p = classCentroid[i];
		for (int i = 0; i < p.coeff.size(); ++i)
		{
			printf("%.5f ",p.coeff[i]);
		}
		cout << endl;
	}
}

void dataSet::splitCentroids(){

	vector<dataPoint> newCentroids;
	for (int i = 0; i < classCentroid.size(); ++i)
	{
		dataPoint p = classCentroid[i];
		p.add(epsilon);
		newCentroids.push_back(p);
		p = classCentroid[i];
		p.add(epsilon*-1);
		newCentroids.push_back(p);
		classCount.push_back(0);
	}
	classCentroid = newCentroids;
}