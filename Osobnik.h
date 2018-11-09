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
	pair<Osobnik, Osobnik> crossingMultipoint(int n, Osobnik * osobnik);
	pair<Osobnik, Osobnik> evenly(Osobnik * osobnik);
	pair<Osobnik, Osobnik> crossingOnePoint(Osobnik * osobnik);
	pair<Osobnik, Osobnik> crossingTwoPoints(Osobnik * osobnik);
	void printChromosome();
};
