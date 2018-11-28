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
	Osobnik& operator=(const Osobnik& osobnik);
	bool* genChromosome();
	~Osobnik();
	bool* getChromosome();
	double* getChromValues(int* arrayOfBinAcc, int accSize);
	int getBinChromLen();
	int getChromLen();
	float** getRange();
	double eval(double* values, int size);
	Osobnik mutate();
	Osobnik invert();
	pair<Osobnik, Osobnik> crossing(int type, Osobnik * osobnik);
	pair<Osobnik, Osobnik> crossingMultipoint(int n, Osobnik * osobnik);
	pair<Osobnik, Osobnik> evenly(Osobnik * osobnik);
	void printChromosome();
};
