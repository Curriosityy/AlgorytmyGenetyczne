#include "stdafx.h"
#include "Populacja.h"

Populacja::Populacja(int* accuracy, int populationSize, int accSize)
{
	this->accuracy = accuracy;
	arrayOfBinAccuLen = new int[accSize];
	this->accSize = accSize;
	this->pupulationSize = populationSize;
	for (int i = 0; i < populationSize; i++)
	{
		population.push_back(new Osobnik(setChromLen()));
	}
}

int Populacja::setChromLen()
{
	int len = 0;
	for (int i = 0; i < accSize; i++)
	{
		int numOfVariance = (B - A)*pow(10, accuracy[i]);
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

Osobnik * Populacja::getIndividual(int i)
{
	return population[i];
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