#include "stdafx.h"
#include "Populacja.h"
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int accSize = 6;
	int populationSize = 10;
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
	cout << "________________Populacja przed wyborem____________________" << endl;
	pop.printInfo();
	auto roulettMax = pop.rouletteMax();
	auto rankMin = pop.rankMin();
	auto rankMax = pop.rankMax();
	auto roulettMin = pop.rouletteMin();
	cout << "________________roulettMax____________________" << endl;
	pop.setNewPopulation(&roulettMax);
	pop.printInfo();
	cout << "________________roulettMin____________________" << endl;
	pop.setNewPopulation(&roulettMin);
	pop.printInfo();
	cout << "__________________rankMin__________________" << endl;
	pop.setNewPopulation(&rankMin);
	pop.printInfo();
	cout << "___________________rankMax_________________" << endl;
	pop.setNewPopulation(&rankMax);
	pop.printInfo();
	getchar();
	delete acc;
	for (int i = 0; i < accSize; i++) {
		delete range[i];
	}
	delete range;
	return 0;
}