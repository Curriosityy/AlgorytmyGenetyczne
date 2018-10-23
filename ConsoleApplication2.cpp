#include "stdafx.h"
#include "Populacja.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int accSize = 6;
	int populationSize = 5;
	int* acc = new int[accSize];
	acc[0] = 1;
	acc[1] = 2;
	acc[2] = 3;
	acc[3] = 4;
	acc[4] = 5;
	acc[5] = 6;

	float** range = new float*[accSize];
	for (int i = 0; i < accSize; i++) {
		range[i] = new float[2];
		range[i][0] = -1.0f;
		range[i][1] = 1.0f;
	}

	cout.fill(' ');
	Populacja pop(acc, populationSize, accSize, range);
	pop.printInfo();
	auto roulettMax = pop.rouletteMax();
	pop.rankMin();
	cout << "____________________________________" << endl;
	getchar();
	delete acc;
	for (int i = 0; i < accSize; i++) {
		delete range[i];
	}
	delete range;
	return 0;
}