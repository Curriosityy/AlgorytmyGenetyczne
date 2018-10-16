#pragma once
class Osobnik
{
private:
	bool* chromosome;
	int binChromLen;
public:
	Osobnik(int binChromLen);
	void genChromosome();
	~Osobnik();
	bool* getChromosome();
	double* getChromValues(int* arrayOfBinAcc, int accSize);
	double adaptation(double* values, int size);
	string printChromosome();
};
