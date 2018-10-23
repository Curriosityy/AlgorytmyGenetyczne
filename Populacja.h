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
	double changeEvalToProb(double sum, double eval);
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
	void setNewPopulation(vector<Osobnik>* newPopulation);
	vector<pair<Osobnik*, double>> createVecIndividualValue();
	vector<pair<Osobnik*, double>> sortVecInc(vector<pair<Osobnik*, double>>unordered_mapToSort);
	vector<pair<Osobnik*, double>> sortVecDec(vector<pair<Osobnik*, double>> unordered_mapToSort);
};
