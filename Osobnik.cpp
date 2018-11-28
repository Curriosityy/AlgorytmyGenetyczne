#include "stdafx.h"
#include "Osobnik.h"

Osobnik::Osobnik(int binChromLen, float** range)
{
	this->binChromLen = binChromLen;
	this->range = range;
	chromosome = genChromosome();
}
Osobnik::Osobnik(const Osobnik* osobnik)
{
	this->binChromLen = osobnik->binChromLen;
	chromosome = new bool[binChromLen];
	this->range = osobnik->range;
	for (int i = 0; i < binChromLen; i++)
	{
		chromosome[i] = osobnik->chromosome[i];
	}
}
Osobnik::Osobnik(const Osobnik& osobnik)
{
	binChromLen = osobnik.binChromLen;
	chromosome = new bool[binChromLen];
	for (int i = 0; i < binChromLen; i++)
	{
		chromosome[i] = osobnik.chromosome[i];
	}
	range = osobnik.range;
}
Osobnik& Osobnik::operator=(const Osobnik& osobnik) {
	binChromLen = osobnik.binChromLen;
	chromosome = new bool[binChromLen];
	for (int i = 0; i < binChromLen; i++)
	{
		chromosome[i] = osobnik.chromosome[i];
	}
	range = osobnik.range;
	return *this;
}
bool* Osobnik::genChromosome()
{
	bool* chrom = new bool[binChromLen];
	for (int i = 0; i < binChromLen; i++)
	{
		chrom[i] = rand() % 2;
	}
	return chrom;
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
		chromValues[i] = range[i][0] + ((range[i][1] - range[i][0])*temp*1.0) / ((pow(2, arrayOfBinAcc[i]) - 1)*1.0);
	}
	return chromValues;
}

int Osobnik::getBinChromLen()
{
	return binChromLen;
}

int Osobnik::getChromLen()
{
	return binChromLen;
}

float ** Osobnik::getRange()
{
	return range;
}

double Osobnik::eval(double* values, int size)
{
	double adapt = C * size;
	for (int i = 0; i < size; i++)
	{
		adapt += pow(values[i], 2) - (C * cos(20 * _Pi*values[i]));
	}
	return adapt;
}

void Osobnik::printChromosome()
{
	for (int i = 0; i < binChromLen; i++)
	{
		cout << chromosome[i];
	}
	cout << endl;
}

Osobnik Osobnik::invert()
{
	int from, to;
	bool temp;
	from = rand() % binChromLen;
	to = (rand() % (binChromLen - from)) + from;
	Osobnik nowy(this);
	for (int i = from, j = to; i < j; i++, j--)
	{
		temp = nowy.chromosome[i];
		nowy.chromosome[i] = nowy.chromosome[j];
		nowy.chromosome[j] = temp;
	}
	return Osobnik(nowy);
}
pair<Osobnik, Osobnik> Osobnik::crossing(int type, Osobnik * osobnik)
{
	switch (type)
	{
	case 1:
		return crossingMultipoint(1, osobnik);
		break;
	case 2:
		return crossingMultipoint(2, osobnik);
		break;
	case 3:
		return crossingMultipoint(rand() % (binChromLen / 7), osobnik);
		break;
	case 4:
		return evenly(osobnik);
		break;
	}
}
Osobnik Osobnik::mutate()
{
	Osobnik nowy(this);
	for (int i = 0; i < binChromLen; i++)
	{
		if (((double)rand() / RAND_MAX) < PI)
			nowy.chromosome[i] = !nowy.chromosome[i];
	}
	return Osobnik(nowy);
}
pair<Osobnik, Osobnik> Osobnik::crossingMultipoint(int n, Osobnik* osobnik)
{
	Osobnik potomek1(this);
	Osobnik potomek2(osobnik);
	int* crossingPoints = new int[n + 1];
	for (int i = 0; i < n; i++)
	{
		crossingPoints[i] = rand() % binChromLen;
	}
	crossingPoints[n] = binChromLen;
	sort(crossingPoints, crossingPoints + n + 1);
	n = unique(crossingPoints, crossingPoints + n + 1) - crossingPoints;
	bool rodzic = false;
	int crossing = 0;
	for (int i = 0; i < binChromLen; i++)
	{
		if (crossingPoints[crossing] < i)
		{
			rodzic = !rodzic;
			crossing++;
		}
		if (rodzic)
		{
			potomek2.chromosome[i] = chromosome[i];
			potomek1.chromosome[i] = osobnik->chromosome[i];
		}
	}
	delete crossingPoints;
	return make_pair(potomek1, potomek2);
}

pair<Osobnik, Osobnik> Osobnik::evenly(Osobnik * osobnik)
{
	bool* pattern = genChromosome();
	Osobnik potomek1(this);
	Osobnik potomek2(osobnik);
	for (int i = 0; i < binChromLen; i++)
	{
		if (pattern) {
			potomek1.chromosome[i] = osobnik->chromosome[i];
			potomek2.chromosome[i] = chromosome[i];
		}
	}
	delete pattern;
	return make_pair(potomek1, potomek2);
}