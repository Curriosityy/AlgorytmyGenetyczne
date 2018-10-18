#include "stdafx.h"
#include "Populacja.h"

Populacja::Populacja(int* accuracy, int populationSize, int accSize, float** range)
{
	this->accuracy = accuracy;
	arrayOfBinAccuLen = new int[accSize];
	this->accSize = accSize;
	this->populationSize = populationSize;
	this->range = range;
	int binlen = setChromLen();
	for (int i = 0; i < populationSize; i++)
	{
		population.push_back(Osobnik(binlen, range));
	}
}

int Populacja::setChromLen()
{
	int len = 0;
	for (int i = 0; i < accSize; i++)
	{
		int numOfVariance = (range[i][1] - range[i][0])*pow(10, accuracy[i]);
		int temp = 0;
		int oneMLen = 0;
		do
		{
			temp++;
			oneMLen = pow(2, temp);
		} while (oneMLen <= numOfVariance);
		arrayOfBinAccuLen[i] = temp;
		len += temp;
	}
	return len;
}
Populacja::~Populacja()
{
	delete arrayOfBinAccuLen;
}

Osobnik* Populacja::getIndividual(int i)
{
	return &population[i];
}

int* Populacja::getArrayOfBinAccuLen()
{
	return arrayOfBinAccuLen;
}

int* Populacja::getAccuracy()
{
	return accuracy;
}

int Populacja::getAccSize()
{
	return accSize;
}
void Populacja::printInfo()
{
	for (int i = 0; i < populationSize; i++)
	{
		Osobnik* ind = &population[i];
		double* chromosomValues = ind->getChromValues(arrayOfBinAccuLen, accSize);
		for (int j = 0; j < accSize; j++)
		{
			double r = pow(10, accuracy[j]);
			chromosomValues[j] = round(chromosomValues[j] * r) / r;
			cout << " x" << j << "=" << setw(accuracy[j] + 3) << left << chromosomValues[j];
		}
		cout << " adaptacja=" << ind->eval(chromosomValues, accSize) << endl;
		delete chromosomValues;
	}
}

double* Populacja::getEvalMatrix()
{
	double* evalMatrix = new double[accSize];
	for (int i = 0; i < populationSize; i++)
	{
		Osobnik* ind = &population[i];
		double* chromosomValues = ind->getChromValues(arrayOfBinAccuLen, accSize);
		for (int j = 0; j < accSize; j++)
		{
			double r = pow(10, accuracy[j]);
			chromosomValues[j] = round(chromosomValues[j] * r) / r;
		}
		evalMatrix[i] = ind->eval(chromosomValues, accSize);
		delete chromosomValues;
	}
	return evalMatrix;
}

map<Osobnik*, int> Populacja::createMapIndividualValue()
{
	double* evalMatrix = getEvalMatrix();
	map<Osobnik*, int> mapIndividualValue;
	for (int i = 0; i < populationSize; i++)
	{
		mapIndividualValue.insert_or_assign(&population[i], evalMatrix[i]);
	}
	delete evalMatrix;
	return mapIndividualValue;
}

vector<Osobnik> Populacja::rouletteMin()
{
	map<Osobnik*, int> individualValue = createMapIndividualValue();
	return vector<Osobnik>();
}

vector<Osobnik> Populacja::rouletteMax()
{
	map<Osobnik*, int> individualValue = createMapIndividualValue();
	return vector<Osobnik>();
}

vector<Osobnik> Populacja::rankMin()
{
	map<Osobnik*, int> individualValue = createMapIndividualValue();
	return vector<Osobnik>();
}

vector<Osobnik> Populacja::rankMax()
{
	map<Osobnik*, int> individualValue = createMapIndividualValue();
	return vector<Osobnik>();
}

vector<Osobnik> Populacja::tournamentMin()
{
	map<Osobnik*, int> individualValue = createMapIndividualValue();
	return vector<Osobnik>();
}

vector<Osobnik> Populacja::tournamentMax()
{
	map<Osobnik*, int> individualValue = createMapIndividualValue();
	return vector<Osobnik>();
}

vector<Osobnik> Populacja::tournamentReturnMin()
{
	map<Osobnik*, int> individualValue = createMapIndividualValue();
	return vector<Osobnik>();
}

vector<Osobnik> Populacja::tournamentReturnMax()
{
	map<Osobnik*, int> individualValue = createMapIndividualValue();
	return vector<Osobnik>();
}