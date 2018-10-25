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
	vector<Osobnik> tournamentMin(int numberOfGroups);
	vector<Osobnik> tournamentMax(int numberOfGroups);
	vector<Osobnik> tournamentReturnMin(int numberOfGroups);
	vector<Osobnik> tournamentReturnMax(int numberOfGroups);
	void setNewPopulation(vector<Osobnik>* newPopulation);
	void useGeneticOperatorsOnPopulation();
private:
	int setChromLen();
	vector<pair<Osobnik*, double>> createPairIndividualValue();
	vector<pair<Osobnik*, double>> sortVecInc(vector<pair<Osobnik*, double>>unordered_mapToSort);
	vector<pair<Osobnik*, double>> sortVecDec(vector<pair<Osobnik*, double>> unordered_mapToSort);
};
