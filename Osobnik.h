#pragma once
class Osobnik
{
private:
	bool* chromosome;
	int binChromLen;
	float** range;

public:
	Osobnik(int binChromLen, float** range);
	Osobnik(const Osobnik* osobnik);
	Osobnik(const Osobnik& osobnik);
	void genChromosome();
	~Osobnik();
	bool* getChromosome();
	double* getChromValues(int* arrayOfBinAcc, int accSize);
	int getBinChromLen();
	float** getRange();
	double eval(double* values, int size);
	string printChromosome();
};
