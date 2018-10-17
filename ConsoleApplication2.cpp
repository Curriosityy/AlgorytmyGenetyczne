#include "stdafx.h"
#include "Populacja.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int accSize = 6;
	int populationSize = 15;
	int* acc = new int[accSize];
	acc[0] = 1;
	acc[1] = 2;
	acc[2] = 3;
	acc[3] = 4;
	acc[4] = 5;
	acc[5] = 6;

	cout.fill(' ');
	Populacja pop(acc, populationSize, accSize);
	for (int a = 0; a < populationSize; a++)
	{
		Osobnik* ind = pop.getIndividual(a);
		double* chromosomValues = ind->getChromValues(pop.getArrayOfBinAccuLen(), accSize);
		for (int i = 0; i < accSize; i++)
		{
			double r = pow(10, pop.getAccuracy()[i]);
			chromosomValues[i] = round(chromosomValues[i] * r) / r;
			cout << " x" << i << "=" << setw(acc[i] + 3) << left << chromosomValues[i];
		}

		cout << " adaptacja=" << ind->adaptation(chromosomValues, accSize) << endl;
	}
	getchar();
	return 0;
}