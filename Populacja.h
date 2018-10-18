#pragma once
#include "Osobnik.h"
class Populacja
{
private:
	vector<Osobnik> population;
	int* accuracy;
	int* arrayOfBinAccuLen;
	int accSize;
	int populationSize;
	float** range;
public:
	Populacja(int* accuracy, int populationNumber, int accNumber, float** range);
	int setChromLen();
	~Populacja();
	Osobnik* getIndividual(int i);
	int* getArrayOfBinAccuLen();
	int* getAccuracy();
	int getAccSize();
	void printInfo();
	double* getEvalMatrix();
	vector<Osobnik> rouletteMin();
	vector<Osobnik> rouletteMax();
	vector<Osobnik> rankMin();
	vector<Osobnik> rankMax();
	vector<Osobnik> tournamentMin();
	vector<Osobnik> tournamentMax();
	vector<Osobnik> tournamentReturnMin();
	vector<Osobnik> tournamentReturnMax();
	map<Osobnik*, int> createMapIndividualValue();
};
