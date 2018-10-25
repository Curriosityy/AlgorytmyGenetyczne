#include "stdafx.h"
#include "Populacja.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int chosedMethod;
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
	cout << "1-Ruletka Max 2-Ruletka Min 3-Rankingowa Max 4-Rankingowa Min 5-Turniejowa Max 6-Turniejowa Min 7-Turniejowa ze zwracaniem Max 8-Truniejowa ze zwracaniem Min" << endl;
	cin >> chosedMethod;
	cout.fill(' ');
	Populacja pop(acc, populationSize, accSize, range);
	cout << "________________Populacja przed wyborem____________________" << endl;
	pop.printInfo();
	switch (chosedMethod)
	{
	case 1:
		pop.setNewPopulation(&pop.rouletteMax());
		cout << "________________roulettMax____________________" << endl;
		pop.printInfo();
		pop.useGeneticOperatorsOnPopulation();
		cout << "__________________After operations__________________" << endl;
		pop.printInfo();
		break;
	case 2:
		pop.setNewPopulation(&pop.rouletteMin());
		cout << "________________roulettMin____________________" << endl;
		pop.printInfo();
		pop.useGeneticOperatorsOnPopulation();
		cout << "__________________After operations__________________" << endl;
		pop.printInfo();
		break;
	case 3:
		pop.setNewPopulation(&pop.rankMax());
		cout << "___________________rankMax_________________" << endl;
		pop.printInfo();
		pop.useGeneticOperatorsOnPopulation();
		cout << "__________________After operations__________________" << endl;
		pop.printInfo();
		break;
	case 4:
		pop.setNewPopulation(&pop.rankMin());
		cout << "__________________rankMin__________________" << endl;
		pop.printInfo();
		pop.useGeneticOperatorsOnPopulation();
		cout << "__________________After operations__________________" << endl;
		pop.printInfo();
		break;
	case 5:
		cout << "________________tournamentMin____________________" << endl;
		pop.setNewPopulation(&pop.tournamentMin(2));
		pop.printInfo();
		pop.useGeneticOperatorsOnPopulation();
		cout << "__________________After operations__________________" << endl;
		pop.printInfo();
		break;
	case 6:
		pop.setNewPopulation(&pop.tournamentMax(2));
		cout << "________________tournamentMax____________________" << endl;
		pop.printInfo();
		pop.useGeneticOperatorsOnPopulation();
		cout << "__________________After operations__________________" << endl;
		pop.printInfo();
		break;
	case 7:
		pop.setNewPopulation(&pop.tournamentReturnMax(2));
		cout << "__________________tournamentReturnMax__________________" << endl;
		pop.printInfo();
		pop.useGeneticOperatorsOnPopulation();
		cout << "__________________After operations__________________" << endl;
		pop.printInfo();
		break;
	case 8:
		cout << "___________________tournamentReturnMin_________________" << endl;
		pop.setNewPopulation(&pop.tournamentReturnMin(2));
		pop.printInfo();
		pop.useGeneticOperatorsOnPopulation();
		cout << "__________________After operations__________________" << endl;
		pop.printInfo();
		break;
	default:
		cout << "Wrong number" << endl;
		break;
	}

	getchar();
	getchar();
	delete acc;
	for (int i = 0; i < accSize; i++) {
		delete range[i];
	}
	delete range;
	return 0;
}