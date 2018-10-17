#include "stdafx.h"
#include "Osobnik.h"

Osobnik::Osobnik(int binChromLen)
{
	this->binChromLen = binChromLen;
	chromosome = new bool[binChromLen];
	genChromosome();
}
void Osobnik::genChromosome()
{
	for (int i = 0; i < binChromLen; i++)
	{
		chromosome[i] = rand() % 2;
	}
}
Osobnik::~Osobnik()
{
	delete chromosome;
}

bool* Osobnik::getChromosome()
{
	return chromosome;
}

double* Osobnik::getChromValues(int* arrayOfBinAcc, int accSize)
{
	double* chromValues = new double[accSize];
	int lastInd = binChromLen - 1;
	for (int i = 0; i < accSize; i++)
	{
		int temp = 0;
		for (int x = lastInd; x > lastInd - arrayOfBinAcc[i]; x--)
		{
			temp += chromosome[x] * pow(2, abs((lastInd - x)));
		}
		lastInd -= arrayOfBinAcc[i];
		chromValues[i] = A + ((B - A)*temp*1.0) / ((pow(2, arrayOfBinAcc[i]) - 1)*1.0);
	}
	return chromValues;
}

double Osobnik::adaptation(double* values, int size)
{
	double adapt = C * size;
	for (int i = 0; i < size; i++)
	{
		adapt += pow(values[i], 2) - (C * cos(20 * _Pi*values[i]));
	}
	return adapt;
}

string Osobnik::printChromosome()
{
	return "";
}