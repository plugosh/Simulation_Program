// Simulation_Program.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
//Algorytmy użyte - FCFS, LCSF, SJF, Algorytm loteryjny

#include <random>
#include "Process.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>

std::fstream allData;

void FCFS(Process p[],double &cData,double &wData,int savecounter)	//zakladamy ze procesy przychodza zgodnie z kolejnoscia w tablicy
{
	allData.open("Collected_Data.txt", std::ios::out | std::ios::app);
	allData << " ALGORYTM FCFS " << "\n";

	const int count = 100;
	double avgWaitingTime[count];		//zapis czasow dla kolejnych procesow
	double avgCycleTime[count];

	avgWaitingTime[0] = 0;
	avgCycleTime[0] = p[0].returnDurationTime();

	for (int i = 0; i < count; ++i)
	{
		if (i > 0)
		{
			avgWaitingTime[i] = p[i - 1].returnDurationTime() + avgWaitingTime[i - 1];	//odtwarzanie procesow od pierwszego do ostatniego
			avgCycleTime[i] = p[i].returnDurationTime() + avgWaitingTime[i];
		}
	}

	double aCT=0;
	double aWT=0;

	for (int i = 0; i < count; ++i)
	{
		aCT += avgCycleTime[i];			//liczenie srednich czasow
		aWT += avgWaitingTime[i];
	}

	aCT = aCT / count;
	aWT = aWT / count;

	std::cout << std::setprecision(20) << "Sredni czas cyklu dla algorytmu FCFS: " << aCT << "\n";
	allData << savecounter << " CYKL: " << aCT << "\n";
	std::cout << std::setprecision(20) << "Sredni czas oczekiwania na procesor dla algorytmu FCFS: " << aWT << "\n";
	allData << savecounter << " OCZEKIWANIE: " << aWT << "\n";

	cData += aCT;
	wData += aWT;

	allData.close();
}

void LCFS(Process p[], double &cData, double &wData, int savecounter)
{

	allData.open("Collected_Data.txt", std::ios::out | std::ios::app);
	allData <<" ALGORYTM LCFS " << "\n";

	const int count = 100;
	double avgWaitingTime[count];
	double avgCycleTime[count];

	avgWaitingTime[count - 1] = 0;
	avgCycleTime[count - 1] = p[count-1].returnDurationTime();

	for (int i = count - 1; i >= 0; --i)
	{
		if (i < count - 1)
		{
			avgWaitingTime[i] = p[i + 1].returnDurationTime() + avgWaitingTime[i + 1];		//odtwarzanie procesow od ostatniego do pierwszego
			avgCycleTime[i] = p[i].returnDurationTime() + avgWaitingTime[i];
		}
	}



	double aCT=0;
	double aWT=0;

	for (int i = 0; i < count; ++i)
	{
		aCT += avgCycleTime[i];
		aWT += avgWaitingTime[i];
	}

	aCT = aCT / count;
	aWT = aWT / count;

	std::cout << std::setprecision(20) << "Sredni czas cyklu dla algorytmu LCFS: " << aCT << "\n";
	allData << savecounter << " CYKL: " << aCT << "\n";
	std::cout << std::setprecision(20) << "Sredni czas oczekiwania na procesor dla algorytmu LCFS: " << aWT << "\n";
	allData << savecounter << " OCZEKIWANIE: " << aWT << "\n";

	cData += aCT;
	wData += aWT;

	allData.close();


}

void SJF(Process p[], double &cData, double &wData, int savecounter)
{
	allData.open("Collected_Data.txt", std::ios::out | std::ios::app);
	allData << " ALGORYTM SFJ " << "\n";

	const int count = 100;
	double* sortedArray = new double[count];
	double avgWaitingTime[count];
	double avgCycleTime[count];

	for (int i = 0; i < count; ++i)
	{
		sortedArray[i] = p[i].returnDurationTime();		//uproszczenie sortowania dzieki zalozeniu, ze procesy przychodza w tym samym momencie
	}

	for (int i = 1; i < count; ++i)
	{
		for (int j = count - 1; j >= 1; --j)
		{
			if (sortedArray[j] < sortedArray[j - 1])		//sortowanie procesow rosnaco wzgledem czasu ich trwania
			{
				double bufor;
				bufor = sortedArray[j - 1];
				sortedArray[j - 1] = sortedArray[j];
				sortedArray[j] = bufor;
			}
		}
	}

	/*for (int i = 0; i < count; ++i)
	{
		std::cout << "POSORTOWANE " << i << " " << sortedArray[i] << "\n";
	}*/
	avgWaitingTime[0] = 0;
	avgCycleTime[0] = p[0].returnDurationTime();

	for (int i = 0; i < count; ++i)
	{
		if (i > 0)
		{
			avgWaitingTime[i] = sortedArray[i - 1] + avgWaitingTime[i - 1];		//odtwarzanie posortowanych procesow
			avgCycleTime[i] = sortedArray[i] + avgWaitingTime[i];
		}
	}

	double aCT=0;
	double aWT=0;

	for (int i = 0; i < count; ++i)
	{
		aCT += avgCycleTime[i];
		aWT += avgWaitingTime[i];
	}

	aCT = aCT / count;
	aWT = aWT / count;

	std::cout << std::setprecision(20) << "Sredni czas cyklu dla algorytmu SJF: " << aCT << "\n";
	allData << savecounter << " CYKL: " << aCT << "\n";
	std::cout << std::setprecision(20) << "Sredni czas oczekiwania na procesor dla algorytmu SJF: " << aWT << "\n";
	allData << savecounter << " OCZEKIWANIE: " << aWT << "\n";

	cData += aCT;
	wData += aWT;

	allData.close();
	delete[]sortedArray;

}

void lottery(Process p[], double &cData, double &wData, int savecounter)
{
	srand(time(NULL));
	allData.open("Collected_Data.txt", std::ios::out | std::ios::app);
	allData << " ALGORYTM LOTERYJNY " << "\n";

	const int count = 100;
	double avgWaitingTime[count];
	double avgCycleTime[count];
	int queue[count];
	bool Used[count];

	for (int i = 0; i < count; ++i)
	{
		Used[i] = false;
	}

	for (int i = 0; i < count; ++i)
	{
		bool x;
		do
		{
			int number = std::rand() % count;				//ustawianie losowej kolejki procesow
			if (Used[number] == false)
			{
				queue[i] = number;
				Used[number] = true;
				x = false;
			}
			else
			{
				x = true;
			}
		} while (x);
	}

	//losowanie liczby od 0 do 99, sprawdzanie czy jest uzyta, wpisywanie jej do kolejnych indeksow tablicy;

	avgWaitingTime[0] = 0;
	avgCycleTime[0] = p[0].returnDurationTime();

	for (int i = 0; i < count; ++i)
	{
		if (i > 0)
		{
			avgWaitingTime[i] = p[queue[i - 1]].returnDurationTime() + avgWaitingTime[i - 1];	//odtwarzanie losowej kolejki
			avgCycleTime[i] = p[queue[i]].returnDurationTime() + avgWaitingTime[i];
		}
	}

	double aCT=0;
	double aWT=0;

	for (int i = 0; i < count; ++i)
	{
		aCT += avgCycleTime[i];
		aWT += avgWaitingTime[i];
	}

	aCT = aCT / count;
	aWT = aWT / count;

	std::cout << std::setprecision(20) << "Sredni czas cyklu dla algorytmu Loteryjnego: " << aCT << "\n";
	allData << savecounter << " CYKL: " << aCT << "\n";
	std::cout << std::setprecision(20) << "Sredni czas oczekiwania na procesor dla algorytmu Loteryjnego: " << aWT << "\n";
	allData << savecounter << " OCZEKIWANIE: " << aWT << "\n";

	cData += aCT;
	wData += aWT;

	allData.close();
}


int main()
{
	srand(time(NULL));

	Process *Array;
	Array = new Process[100];
	int scount = 0;
	const int series = 100;

	allData.open("Collected_Data.txt", std::ios::out | std::ios::trunc);
	allData.close();

	std::fstream FinalData;
	FinalData.open("FinalData.txt", std::ios::out);


	double collectedWaitingData[4]; // 0. FCFS; 1. LCFS; 2. SFJ; 3. Loteryjny
	double collectedCycleData[4]; // 0. FCFS; 1. LCFS; 2. SFJ; 3. Loteryjny

	for (int j = 0; j < 4; ++j)
	{
		collectedCycleData[j] = 0;
		collectedWaitingData[j] = 0;
	}


	for (int i = 0; i < series; ++i)							//petla iterujaca po ciagach
	{

		for (int j = 0; j < 100; ++j)
		{
			Array[j].replaceIndex(j);							//ustawianie indeksow dla procesow
		}
		for (int j = 0; j < 100; ++j)
		{
			std::random_device rd;								//losowanie dlugosci procesow
			std::mt19937 gen(rd()); 
			std::uniform_real_distribution<> dis(1.0, 20.0);
			Array[j].setDurationTime(dis(gen));
		}
		//zrob aby procesy sie nie powtarzaly

		for (int j = 0; j < 100; ++j)
		{
			std::cout << Array[j].returnDurationTime() << "\n";			//wypisywanie dlugosci procesow w ciagu
		}

		std::cout << "CIAG NR:		" << i << "\n";
		std::cout << "\n";

		

		FCFS(Array, collectedCycleData[0], collectedWaitingData[0],  scount);		//algorytmy
		LCFS(Array, collectedCycleData[1], collectedWaitingData[1],  scount);
		SJF(Array, collectedCycleData[2], collectedWaitingData[2],  scount);
		lottery(Array, collectedCycleData[3], collectedWaitingData[3],  scount);

		scount++;
		std::cout << "\n";
		allData << "\n";
	}

	for (int i = 0; i < 4; ++i)
	{
		collectedCycleData[i] = collectedCycleData[i] / series;			//srednia ze 100 ciagow
		collectedWaitingData[i] = collectedWaitingData[i] / series;
	}
	


	std::cout << std::setprecision(10) << "sredni czas po usrednieniu wszystkich ciagow dla FCFS:" << "\n";
	std::cout << std::setprecision(10) << "cyklu:" << collectedCycleData[0] << "\n";
	std::cout << std::setprecision(10) << "oczekiwania:" << collectedWaitingData[0] << "\n";

	std::cout << std::setprecision(10) << "sredni czas po usrednieniu wszystkich ciagow dla LCFS:" << "\n";
	std::cout << std::setprecision(10) << "cyklu:" << collectedCycleData[1] << "\n";
	std::cout << std::setprecision(10) << "oczekiwania:" << collectedWaitingData[1] << "\n";

	std::cout << std::setprecision(10) << "sredni czas po usrednieniu wszystkich ciagow dla SJF:" << "\n";
	std::cout << std::setprecision(10) << "cyklu:" << collectedCycleData[2] << "\n";
	std::cout << std::setprecision(10) << "oczekiwania:" << collectedWaitingData[2] << "\n";

	std::cout << std::setprecision(10) << "sredni czas po usrednieniu wszystkich ciagow dla LOTERYJNEGO:" << "\n";
	std::cout << std::setprecision(10) << "cyklu:" << collectedCycleData[3] << "\n";
	std::cout << std::setprecision(10) << "oczekiwania:" << collectedWaitingData[3] << "\n";

	std::cout << "\n";
	std::cout << "PODSUMOWANIE: " << "\n";
	std::cout << "           SR CZAS OCZEKIWANIA | SR CZAS CYKLU    " << "\n";
	std::cout << "FCFS:      " << collectedWaitingData[0] << "  |  " << collectedCycleData[0] << "\n";
	std::cout << "LCFS:      " << collectedWaitingData[1] << "  |  " << collectedCycleData[1] << "\n";
	std::cout << "SJF:       " << collectedWaitingData[2] << "  |  " << collectedCycleData[2] << "\n";
	std::cout << "Loteryjny: " << collectedWaitingData[3] << "  |  " << collectedCycleData[3] << "\n";

	FinalData << "\n";
	FinalData << "PODSUMOWANIE: " << "\n";
	FinalData << "SR CZAS OCZEKIWANIA  SR CZAS CYKLU    " << "\n";
	FinalData << "FCFS:" <<"\t"<< collectedWaitingData[0] << "|" << collectedCycleData[0] << "\n";
	FinalData << "LCFS:" << "\t" << collectedWaitingData[1] << "|" << collectedCycleData[1] << "\n";
	FinalData << "SJF:" << "\t" << collectedWaitingData[2] << "|" << collectedCycleData[2] << "\n";
	FinalData << "Loteryjny:" << "\t" << collectedWaitingData[3] << "|" << collectedCycleData[3] << "\n";

	FinalData.close();

	delete[] Array;
}

