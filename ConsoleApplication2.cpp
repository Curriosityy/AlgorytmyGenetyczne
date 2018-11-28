#include "stdafx.h"
#include "Populacja.h"

int _tmain(int argc, _TCHAR* argv[])
{
	srand(time(NULL));
	int chosedMethod, genCount, chosedSuccesMethod;
	int accSize = 6;
	int populationSize = 20;
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
	cout << "Podaj liczbe generacji\n";
	cin >> genCount;
	cout << "1-Ruletka Max 2-Ruletka Min 3-Rankingowa Max 4-Rankingowa Min 5-Turniejowa Max 6-Turniejowa Min 7-Turniejowa ze zwracaniem Max 8-Truniejowa ze zwracaniem Min" << endl;
	cin >> chosedMethod;
	cout << "1-Pelna 2-Czesciowa 3-Losowa 4-Elitarna\n" << endl;
	cin >> chosedSuccesMethod;
	cout.fill(' ');
	Populacja pop(acc, populationSize, accSize, range);
	cout << "________________Populacja poczatkowa____________________" << endl;
	pop.printInfo();
	switch (chosedMethod)
	{
	case 1:
		cout << "________________roulettMax____________________" << endl;
		for (int i = 0; i < genCount; i++)
		{
			pop.setNewPopulation(&pop.rouletteMax());
			pop.sukcesja(chosedSuccesMethod);
			pop.printInfo();
			cout << "------------------------------------------------------------\n";
		}
		break;
	case 2:
		cout << "________________roulettMin____________________" << endl;
		for (int i = 0; i < genCount; i++)
		{
			pop.setNewPopulation(&pop.rouletteMin());
			pop.sukcesja(chosedSuccesMethod);
			pop.printInfo();
			cout << "------------------------------------------------------------\n";
		}
		break;
	case 3:
		cout << "___________________rankMax_________________" << endl;

		for (int i = 0; i < genCount; i++)
		{
			pop.setNewPopulation(&pop.rankMax());
			pop.sukcesja(chosedSuccesMethod);
			pop.printInfo();
			cout << "------------------------------------------------------------\n";
		}
		break;
	case 4:
		cout << "__________________rankMin__________________" << endl;

		for (int i = 0; i < genCount; i++)
		{
			pop.setNewPopulation(&pop.rankMin());
			pop.sukcesja(chosedSuccesMethod);
			pop.printInfo();
			cout << "------------------------------------------------------------\n";
		}
		break;
	case 5:
		cout << "________________tournamentMin____________________" << endl;

		for (int i = 0; i < genCount; i++)
		{
			pop.setNewPopulation(&pop.tournamentMin(2));
			pop.sukcesja(chosedSuccesMethod);
			pop.printInfo();
			cout << "------------------------------------------------------------\n";
		}
		break;
	case 6:
		cout << "________________tournamentMax____________________" << endl;

		for (int i = 0; i < genCount; i++)
		{
			pop.setNewPopulation(&pop.tournamentMax(2));
			pop.sukcesja(chosedSuccesMethod);
			pop.printInfo();
			cout << "------------------------------------------------------------\n";
		}
		break;
	case 7:
		cout << "__________________tournamentReturnMax__________________" << endl;

		for (int i = 0; i < genCount; i++)
		{
			pop.setNewPopulation(&pop.tournamentReturnMax(2));
			pop.sukcesja(chosedSuccesMethod);
			pop.printInfo();
			cout << "------------------------------------------------------------\n";
		};
		break;
	case 8:
		cout << "___________________tournamentReturnMin_________________" << endl;

		for (int i = 0; i < genCount; i++)
		{
			pop.setNewPopulation(&pop.tournamentReturnMin(2));
			pop.sukcesja(chosedSuccesMethod);
			pop.printInfo();
			cout << "------------------------------------------------------------\n";
		}
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