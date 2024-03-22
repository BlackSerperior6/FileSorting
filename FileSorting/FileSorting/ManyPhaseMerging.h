#pragma once

#include <iostream>
#include "NaturalMerge.h"

using namespace std;

pair<int, int> GetFibonnachiNumbers(int numberToCompareTo, pair<int, int> PreviousTwoNumbers)
{
	int currentNumber = PreviousTwoNumbers.first + PreviousTwoNumbers.second;
	pair <int, int> PairToReturn;

	if (currentNumber < numberToCompareTo)
		PairToReturn = GetFibonnachiNumbers(numberToCompareTo, { PreviousTwoNumbers.second, currentNumber });
	else
		PairToReturn = PreviousTwoNumbers;

	return PairToReturn;
}

pair<int, int> GetFibonnachiNumbers(int numberToCompareTo)
{
	return GetFibonnachiNumbers(numberToCompareTo, { 0, 1 });
}

void ManyPhaseMerge(int* Arr, int Lenght)
{
	cout << "Метод многомерной сортировки" << endl;

	pair<pair<int, int>*, int>* Buckets = new pair<pair<int, int>*, int>[3];

	pair<int, int> PerfectFibonachiNumbers = GetFibonnachiNumbers(Lenght);

	int countOfPairs = PerfectFibonachiNumbers.first + PerfectFibonachiNumbers.second;

	Buckets[0].second = PerfectFibonachiNumbers.second;
	Buckets[1].second = PerfectFibonachiNumbers.first;
	Buckets[2].second = 0;

	cout << Buckets[0].second << Buckets[1].second << endl;

	for (int i = 0; i < 3; i++)
	{
		Buckets[i].first = new pair<int, int>[Lenght];

		for (int j = 0; j < Buckets[i].second; j++)
			Buckets[i].first[j] = { 0, 0 };
	}

	int CurrentIndex = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < Buckets[i].second; j++)
		{
			Buckets[i].first[j] = { CurrentIndex, CurrentIndex };
			CurrentIndex++;
		}
	}

	int NumberOfFictiveSeries = PerfectFibonachiNumbers.first + PerfectFibonachiNumbers.second - Lenght;

	for (int i = Buckets[1].second - NumberOfFictiveSeries; i < Buckets[1].second; i++)
		Buckets[1].first[i] = { -1, -1 };

	for (int i = 0; i < 2; i++)
	{
		cout << i << ":" << endl;

		for (int j = 0; j < Buckets[i].second; j++)
			cout << Buckets[i].first[j].first << Buckets[i].first[j].first << endl;
	}

	int IndexOfTheBiggerBucket = 0;
	int IndexOfTheSmallerBucket = 1;
	int IndexOfTheHelpingBucket = 2;

	while (countOfPairs >= 1)
	{
		for (int i = 0; i < Buckets[IndexOfTheSmallerBucket].second; i++)
			Buckets[IndexOfTheHelpingBucket].first[i] = Buckets[IndexOfTheSmallerBucket].first[i];

		Buckets[IndexOfTheHelpingBucket].second = Buckets[IndexOfTheSmallerBucket].second;

		for (int i = 0; i < Buckets[IndexOfTheHelpingBucket].second; i++)
		{
			if (Buckets[IndexOfTheHelpingBucket].first[i].first != -1)
			{
				MergeSeries(Arr, Buckets[IndexOfTheBiggerBucket].first[i].first, Buckets[IndexOfTheHelpingBucket].first[i].second);
				Buckets[IndexOfTheHelpingBucket].first[i].first = Buckets[IndexOfTheBiggerBucket].first[i].first;
				countOfPairs--;
			}
		}

		int NewLenghtOfBiggerArray = Buckets[IndexOfTheBiggerBucket].second;

		while (Buckets[IndexOfTheBiggerBucket].second > NewLenghtOfBiggerArray - Buckets[IndexOfTheHelpingBucket].second)
		{
			RemoveElement(Buckets[IndexOfTheBiggerBucket].first, 0, Buckets[IndexOfTheBiggerBucket].second);
			Buckets[IndexOfTheBiggerBucket].second--;
		}

		delete[] Buckets[IndexOfTheSmallerBucket].first;
		Buckets[IndexOfTheSmallerBucket].first = new pair<int, int>[Lenght];
		Buckets[IndexOfTheSmallerBucket].second = 0;

		int tmp = IndexOfTheBiggerBucket;
		IndexOfTheBiggerBucket = IndexOfTheHelpingBucket;
		IndexOfTheHelpingBucket = IndexOfTheSmallerBucket;
		IndexOfTheSmallerBucket = tmp;
	}

	for (int i = 0; i < 3; i++)
		delete[] Buckets[i].first;

	delete[] Buckets;
}