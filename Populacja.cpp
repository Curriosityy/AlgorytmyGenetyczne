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
	max = false;
	vector<pair<Osobnik*, double>> individualValue = createPairIndividualValue();
	vector<Osobnik> newPopulation;
	double sumOfEval = 0;
	double max = numeric_limits<double>::min(), min = numeric_limits<double>::max();
	for (auto ite = individualValue.begin(); ite != individualValue.end(); ite++)
	{
		if (max < ite->second)
		{
			max = ite->second;
		}
		if (min > ite->second)
		{
			min = ite->second;
		}
	}
	for (auto ite = individualValue.begin(); ite != individualValue.end(); ite++)
	{
		ite->second = max - ite->second + min;
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

vector<Osobnik> Populacja::rouletteMax()
{
	max = true;
	vector<pair<Osobnik*, double>> individualValue = createPairIndividualValue();
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
	max = false;
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
	max = true;
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
	max = false;
	vector<pair<Osobnik*, double>> individualValue = createPairIndividualValue();
	map<Osobnik*, double> battleGroup;
	map<Osobnik*, double>::iterator ite;
	pair<Osobnik*, double> pair;
	vector<Osobnik> newPopulation;
	for (int i = 0; i < populationSize; i++)
	{
		while (battleGroup.size() <= numberOfGroups)
		{
			pair = individualValue[rand() % populationSize];
			ite = battleGroup.find(pair.first);
			if (ite == battleGroup.end())
			{
				battleGroup[pair.first] = pair.second;
			}
		}
		pair = *battleGroup.begin();
		for (ite = battleGroup.begin(); ite != battleGroup.end(); ite++)
		{
			if (pair.second >= ite->second)
			{
				pair = *ite;
			}
		}
		newPopulation.push_back(Osobnik(pair.first));
		battleGroup.clear();
	}
	return newPopulation;
}

vector<Osobnik> Populacja::tournamentMax(int numberOfGroups)
{
	max = true;
	vector<pair<Osobnik*, double>> individualValue = createPairIndividualValue();
	vector<Osobnik> newPopulation;
	map<Osobnik*, double> battleGroup;
	map<Osobnik*, double>::iterator ite;
	pair<Osobnik*, double> pair;
	for (int i = 0; i < populationSize; i++)
	{
		while (battleGroup.size() <= numberOfGroups)
		{
			pair = individualValue[rand() % populationSize];
			ite = battleGroup.find(pair.first);
			if (ite == battleGroup.end())
			{
				battleGroup[pair.first] = pair.second;
			}
		}
		pair = *battleGroup.begin();
		for (ite = battleGroup.begin(); ite != battleGroup.end(); ite++)
		{
			if (pair.second <= ite->second)
			{
				pair = *ite;
			}
		}
		newPopulation.push_back(Osobnik(pair.first));
		battleGroup.clear();
	}
	return newPopulation;
}

vector<Osobnik> Populacja::tournamentReturnMin(int numberOfGroups)
{
	max = false;
	vector<pair<Osobnik*, double>> individualValue = createPairIndividualValue();
	vector<Osobnik> newPopulation;
	vector<pair<Osobnik*, double>> battleGroup;
	vector<pair<Osobnik*, double>>::iterator ite;
	pair<Osobnik*, double> pair;
	for (int i = 0; i < populationSize; i++)
	{
		while (battleGroup.size() <= numberOfGroups)
		{
			pair = individualValue[rand() % populationSize];
			battleGroup.push_back(pair);
		}
		pair = *battleGroup.begin();
		for (ite = battleGroup.begin(); ite != battleGroup.end(); ite++)
		{
			if (pair.second >= ite->second)
			{
				pair = *ite;
			}
		}
		newPopulation.push_back(Osobnik(pair.first));
		battleGroup.clear();
	}
	return newPopulation;
}

vector<Osobnik> Populacja::tournamentReturnMax(int numberOfGroups)
{
	max = true;
	vector<pair<Osobnik*, double>> individualValue = createPairIndividualValue();
	vector<Osobnik> newPopulation;
	vector<pair<Osobnik*, double>> battleGroup;
	vector<pair<Osobnik*, double>>::iterator ite;
	pair<Osobnik*, double> pair;
	for (int i = 0; i < populationSize; i++)
	{
		while (battleGroup.size() <= numberOfGroups)
		{
			pair = individualValue[rand() % populationSize];
			battleGroup.push_back(pair);
		}
		pair = *battleGroup.begin();
		for (ite = battleGroup.begin(); ite != battleGroup.end(); ite++)
		{
			if (pair.second <= ite->second)
			{
				pair = *ite;
			}
		}
		newPopulation.push_back(Osobnik(pair.first));
		battleGroup.clear();
	}
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

void Populacja::sukcesjaPelna()
{
	for (int i = 0; i < populationSize; i++)
	{
		population[i] = population[i].mutate();
		if (((double)rand() / RAND_MAX) < PI)
			population[i] = population[i].invert();
	}
	vector<Osobnik> toCrossing;
	vector<int> deck;
	int decker = 0;
	for (auto ite = population.begin(); ite != population.end(); ++ite)
	{
		if (((double)rand() / RAND_MAX) < PK)
		{
			toCrossing.push_back(Osobnik(*ite));
			deck.push_back(decker);
			decker++;
		}
	}
	shuffle(deck.begin(), deck.end(), default_random_engine(time(NULL)));
	if (toCrossing.size() % 2 == 1)
	{
		//toCrossing.erase(toCrossing.begin() + deck.back());
		deck.pop_back();
	}
	vector<Osobnik> childs;
	for (int i = 0; i < deck.size(); i += 2)
	{
		pair<Osobnik, Osobnik> childsPair2 = toCrossing[deck[i]].crossing(CROSSINGMETHOD, &toCrossing[deck[i + 1]]);
		childs.push_back(childsPair2.first);
		childs.push_back(childsPair2.second);
	}
	for (int i = 0; i < childs.size(); i++)
	{
		population[deck[i]] = childs[i];
	}
}
void Populacja::sukcesjaCzesciowa()
{
	int childToPick = populationSize * CP;
	int parentToDelete = populationSize - childToPick;
	vector<Osobnik> dziecioki;
	for (int i = 0; i < populationSize; i++)
	{
		dziecioki.push_back(population[i].mutate());
		if (((double)rand() / RAND_MAX) < PI)
			dziecioki.push_back(population[i].invert());
	}
	vector<Osobnik> toCrossing;
	vector<int> deck;
	int decker = 0;
	for (auto ite = population.begin(); ite != population.end(); ++ite)
	{
		if (((double)rand() / RAND_MAX) < PK)
		{
			toCrossing.push_back(Osobnik(*ite));
			deck.push_back(decker);
			decker++;
		}
	}
	shuffle(deck.begin(), deck.end(), default_random_engine(time(NULL)));
	if (toCrossing.size() % 2 == 1)
	{
		//toCrossing.erase(toCrossing.begin() + deck.back());
		deck.pop_back();
	}
	for (int i = 0; i < deck.size(); i += 2)
	{
		pair<Osobnik, Osobnik> childsPair2 = toCrossing[deck[i]].crossing(CROSSINGMETHOD, &toCrossing[deck[i + 1]]);
		dziecioki.push_back(childsPair2.first);
		dziecioki.push_back(childsPair2.second);
	}
	for (int i = 0; i < parentToDelete; i++)
	{
		population.erase(population.begin() + rand() % population.size());
	}
	for (int i = 0; i < childToPick; i++)
	{
		int childToAdd = rand() % dziecioki.size();
		population.push_back(dziecioki[childToAdd]);
		dziecioki.erase(dziecioki.begin() + childToAdd);
	}
}

void Populacja::sukcesjaLosowa()
{
	vector<Osobnik> dziecioki;
	for (int i = 0; i < population.size(); i++)
	{
		dziecioki.push_back(population[i]);
	}
	for (int i = 0; i < populationSize; i++)
	{
		dziecioki.push_back(population[i].mutate());
		if (((double)rand() / RAND_MAX) < PI)
			dziecioki.push_back(population[i].invert());
	}
	vector<Osobnik> toCrossing;
	vector<int> deck;
	int decker = 0;
	for (auto ite = population.begin(); ite != population.end(); ++ite)
	{
		if (((double)rand() / RAND_MAX) < PK)
		{
			toCrossing.push_back(Osobnik(*ite));
			deck.push_back(decker);
			decker++;
		}
	}
	shuffle(deck.begin(), deck.end(), default_random_engine(time(NULL)));
	if (toCrossing.size() % 2 == 1)
	{
		//toCrossing.erase(toCrossing.begin() + deck.back());
		deck.pop_back();
	}
	for (int i = 0; i < deck.size(); i += 2)
	{
		pair<Osobnik, Osobnik> childsPair2 = toCrossing[deck[i]].crossing(CROSSINGMETHOD, &toCrossing[deck[i + 1]]);
		dziecioki.push_back(childsPair2.first);
		dziecioki.push_back(childsPair2.second);
	}
	population.clear();
	int a = dziecioki.size();
	for (int i = 0; i < populationSize; i++)
	{
		int childToAdd = rand() % a;
		population.push_back(dziecioki[childToAdd]);
		dziecioki.erase(dziecioki.begin() + childToAdd);
		--a;
	}
	dziecioki.clear();
}

void Populacja::sukcesjaElitarna()
{
	vector<Osobnik> dziecioki;
	for (int i = 0; i < population.size(); i++)
	{
		dziecioki.push_back(population[i]);
	}

	for (int i = 0; i < populationSize; i++)
	{
		dziecioki.push_back(population[i].mutate());
		if (((double)rand() / RAND_MAX) < PI)
			dziecioki.push_back(population[i].invert());
	}
	vector<Osobnik> toCrossing;
	vector<int> deck;
	int decker = 0;
	for (auto ite = population.begin(); ite != population.end(); ++ite)
	{
		if (((double)rand() / RAND_MAX) < PK)
		{
			toCrossing.push_back(Osobnik(*ite));
			deck.push_back(decker);
			decker++;
		}
	}
	shuffle(deck.begin(), deck.end(), default_random_engine(time(NULL)));
	if (toCrossing.size() % 2 == 1)
	{
		//toCrossing.erase(toCrossing.begin() + deck.back());
		deck.pop_back();
	}
	for (int i = 0; i < deck.size(); i += 2)
	{
		pair<Osobnik, Osobnik> childsPair2 = toCrossing[deck[i]].crossing(CROSSINGMETHOD, &toCrossing[deck[i + 1]]);
		dziecioki.push_back(childsPair2.first);
		dziecioki.push_back(childsPair2.second);
	}

	double* evalMatrix = new double[dziecioki.size()];
	for (int i = 0; i < dziecioki.size(); i++)
	{
		Osobnik* ind = &dziecioki[i];
		double* chromosomValues = ind->getChromValues(arrayOfBinAccuLen, accSize);

		evalMatrix[i] = ind->eval(chromosomValues, accSize);
		delete chromosomValues;
	}
	vector<pair<Osobnik*, double>> pairIndVal;
	for (int i = 0; i < dziecioki.size(); i++)
	{
		pairIndVal.push_back(make_pair(&dziecioki[i], evalMatrix[i]));
	}
	pairIndVal = max ? sortVecDec(pairIndVal) : sortVecInc(pairIndVal);
	population.clear();
	for (int i = 0; i < populationSize; i++)
	{
		population.push_back(Osobnik(pairIndVal[i].first));
	}
	delete evalMatrix;
}

void Populacja::sukcesja(int i)
{
	switch (i)
	{
	case 1:
		sukcesjaPelna();
		break;
	case 2:
		sukcesjaCzesciowa();
		break;
	case 3:
		sukcesjaLosowa();
		break;
	case 4:
		sukcesjaElitarna();
		break;
	case 5:
		break;
	}
}