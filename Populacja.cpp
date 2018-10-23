#include "stdafx.h"
#include "Populacja.h"

double Populacja::changeEvalToProb(double sum, double eval)
{
	return eval / sum;
}

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
	double* evalMatrix = new double[populationSize];
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

vector<pair<Osobnik*, double>> Populacja::createPairIndividualValue()
{
	double* evalMatrix = getEvalMatrix();
	vector<pair<Osobnik*, double>> vecIndividualValue;
	for (int i = 0; i < populationSize; i++)
	{
		vecIndividualValue.push_back(make_pair(&population[i], evalMatrix[i]));
	}
	delete evalMatrix;
	return vecIndividualValue;
}

vector<pair<Osobnik*, double>> Populacja::sortVecInc(vector<pair<Osobnik*, double>> unsortedVec)
{
	vector<pair<Osobnik*, double>> pairs;
	for (auto ite = unsortedVec.begin(); ite != unsortedVec.end(); ite++)
	{
		pairs.push_back(*ite);
	}
	sort(pairs.begin(), pairs.end(), [=](pair<Osobnik*, double> a, pair<Osobnik*, double>b) {return a.second < b.second; });
	return pairs;
}

vector<pair<Osobnik*, double>> Populacja::sortVecDec(vector<pair<Osobnik*, double>> unsortedVec)
{
	vector<pair<Osobnik*, double>> pairs;
	for (auto ite = unsortedVec.begin(); ite != unsortedVec.end(); ite++)
	{
		pairs.push_back(*ite);
	}
	sort(pairs.begin(), pairs.end(), [=](pair<Osobnik*, double> a, pair<Osobnik*, double>b) {return a.second > b.second; });
	return pairs;
}

vector<Osobnik> Populacja::rouletteMin()
{
	vector<pair<Osobnik*, double>> individualValue = sortVecDec(createPairIndividualValue());
	vector<Osobnik> newPopulation;
	double sumOfEval = 0;
	for (auto ite = individualValue.begin(); ite != individualValue.end(); ite++)
	{
		sumOfEval += ite->second;
	}
	for (auto ite = individualValue.begin(); ite != individualValue.end(); ite++)
	{
		ite->second = changeEvalToProb(sumOfEval, ite->second);
	}

	for (int i = 0; i < populationSize; i++)
	{
		double temp = 0;
		double randomNumber = ((double)rand() / RAND_MAX);
		for (auto ite = individualValue.cbegin(), ite2 = individualValue.cend() - 1; ite != individualValue.cend(); ite++, ite2--)
		{
			temp += ite->second;
			if (temp >= randomNumber)
			{
				newPopulation.push_back(Osobnik(ite2->first));
				break;
			}
		}
	}
	return newPopulation;
}

vector<Osobnik> Populacja::rouletteMax()
{
	vector<pair<Osobnik*, double>> individualValue = sortVecDec(createPairIndividualValue());
	vector<Osobnik> newPopulation;
	double sumOfEval = 0;
	for (auto ite = individualValue.begin(); ite != individualValue.end(); ite++)
	{
		sumOfEval += ite->second;
	}
	for (auto ite = individualValue.begin(); ite != individualValue.end(); ite++)
	{
		ite->second = changeEvalToProb(sumOfEval, ite->second);
	}

	for (int i = 0; i < populationSize; i++)
	{
		double temp = 0;
		double randomNumber = ((double)rand() / RAND_MAX);
		for (auto ite = individualValue.cbegin(); ite != individualValue.cend(); ite++)
		{
			temp += ite->second;
			if (temp >= randomNumber)
			{
				newPopulation.push_back(Osobnik(ite->first));
				break;
			}
		}
	}
	return newPopulation;
}

vector<Osobnik> Populacja::rankMin()
{
	vector<pair<Osobnik*, double>> individualValue = sortVecInc(createPairIndividualValue());
	vector<Osobnik> newPopulation;
	for (int i = 0; i < populationSize; i++)
	{
		int rand1 = rand() % populationSize;
		newPopulation.push_back(Osobnik(individualValue[rand1 == 0 ? 0 : rand() % rand1].first));
	}
	return newPopulation;
}

vector<Osobnik> Populacja::rankMax()
{
	vector<pair<Osobnik*, double>> individualValue = sortVecDec(createPairIndividualValue());
	vector<Osobnik> newPopulation;
	for (int i = 0; i < populationSize; i++)
	{
		int rand1 = rand() % populationSize;
		newPopulation.push_back(Osobnik(individualValue[rand1 == 0 ? 0 : rand() % rand1].first));
	}
	return newPopulation;
}

vector<Osobnik> Populacja::tournamentMin(int numberOfGroups)
{
	vector<pair<Osobnik*, double>> individualValue = createPairIndividualValue();
	vector<Osobnik> newPopulation;
	return newPopulation;
}

vector<Osobnik> Populacja::tournamentMax(int numberOfGroups)
{
	vector<pair<Osobnik*, double>> individualValue = createPairIndividualValue();
	vector<Osobnik> newPopulation;
	return newPopulation;
}

vector<Osobnik> Populacja::tournamentReturnMin(int numberOfGroups)
{
	vector<pair<Osobnik*, double>> individualValue = createPairIndividualValue();
	vector<Osobnik> newPopulation;
	return newPopulation;
}

vector<Osobnik> Populacja::tournamentReturnMax(int numberOfGroups)
{
	vector<pair<Osobnik*, double>> individualValue = createPairIndividualValue();
	vector<Osobnik> newPopulation;
	return newPopulation;
}

void Populacja::setNewPopulation(vector<Osobnik>* newPopulation)
{
	population.clear();
	while (!newPopulation->empty())
	{
		population.push_back(newPopulation->back());
		newPopulation->pop_back();
	}
}