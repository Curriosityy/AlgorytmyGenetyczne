#pragma once
#include "Osobnik.h"
class Populacja
{
private:
	vector<Osobnik*> population;
	int* accuracy;
	int* arrayOfBinAccuLen;
	int accSize;
	int pupulationSize;
public:
	Populacja(int* accuracy, int populationNumber, int accNumber);
	int setChromLen();
	~Populacja();
	Osobnik* getIndividual(int i);
	int* getArrayOfBinAccuLen();
	int* getAccuracy();
	int getAccSize();
};
