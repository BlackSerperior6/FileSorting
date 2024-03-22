#pragma once

#include <iostream>
#include <fstream>

#include "CommonFunctions.h"

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

void SortUsingManyPhaseMerging(istream* file, int Lenght)
{
	pair<int*, int>* SeriesArr = new pair<int*, int>[Lenght]; //first - серия, second - его длина
	int AmountOfSeries = 1;

	int indexOfCurSeries = 0;
	SeriesArr[0].first = new int[Lenght];
	SeriesArr[0].second = 1;

	file->read((char*)&SeriesArr[0].first[0], sizeof(int));

	for (int i = 1; i < Lenght; i++)
	{
		int curElement;
		file->read((char*)&curElement, sizeof(int));

		if (curElement >= SeriesArr[indexOfCurSeries].first[SeriesArr[indexOfCurSeries].second - 1])
		{
			SeriesArr[indexOfCurSeries].first[SeriesArr[indexOfCurSeries].second] = curElement;
			SeriesArr[indexOfCurSeries].second++;
		}
		else
		{
			indexOfCurSeries++;
			AmountOfSeries++;

			SeriesArr[indexOfCurSeries].first = new int[Lenght];
			SeriesArr[indexOfCurSeries].second = 1;
			SeriesArr[indexOfCurSeries].first[0] = curElement;
		}
	}

	pair<int, int> PerfectFibonachiNumbers = GetFibonnachiNumbers(Lenght);

	pair<pair<int*, int>*, int>* Buckets = new pair<pair<int*, int>*, int>[3];

	Buckets[0].second = PerfectFibonachiNumbers.second;
	Buckets[1].second = PerfectFibonachiNumbers.first;
	Buckets[2].second = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < Buckets[i].second; j++)
			Buckets[i].first = new pair<int*, int>[Lenght];
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < Buckets[i].second; j++)
			Buckets[i].first[j].second = 0;
	}

	indexOfCurSeries = 0;

	for (int i = 0; i < 2 && indexOfCurSeries < AmountOfSeries; i++)
	{
		for (int j = 0; j < Buckets[i].second && indexOfCurSeries < AmountOfSeries; j++)
		{
			Buckets[i].first[j] = SeriesArr[indexOfCurSeries];
			indexOfCurSeries++;
		}
	}

	AmountOfSeries = PerfectFibonachiNumbers.first + PerfectFibonachiNumbers.second;

	int IndexOfTheBiggerBucket = 0;
	int IndexOfTheSmallerBucket = 1;
	int IndexOfTheHelpingBucket = 2;

	while (AmountOfSeries > 1)
	{
		int NewLenght = Buckets[IndexOfTheBiggerBucket].second - Buckets[IndexOfTheSmallerBucket].second;

		int curIndexOfTheHelpingBucket = 0;
		int lastIndexOfSmalletBucket = Buckets[IndexOfTheSmallerBucket].second - 1;

		for (int i = Buckets[IndexOfTheBiggerBucket].second - 1; i > NewLenght; i--)
		{
			pair<int*, int> NewSeries = MergeSeries(Buckets[IndexOfTheBiggerBucket].first[i], Buckets[IndexOfTheSmallerBucket].first[lastIndexOfSmalletBucket]);

			cout << (Buckets[IndexOfTheHelpingBucket].first == nullptr) << endl;

			Buckets[IndexOfTheHelpingBucket].first[curIndexOfTheHelpingBucket] = NewSeries;

			Buckets[IndexOfTheHelpingBucket].second++;

			curIndexOfTheHelpingBucket++;
			lastIndexOfSmalletBucket--;

			AmountOfSeries--;
		}

		Buckets[IndexOfTheBiggerBucket].second -= Buckets[IndexOfTheSmallerBucket].second;

		for (int i = 0; i < Buckets[IndexOfTheSmallerBucket].second; i++)
			delete[] Buckets[IndexOfTheSmallerBucket].first[i].first;

		delete[] Buckets[IndexOfTheSmallerBucket].first;
	
		Buckets[IndexOfTheSmallerBucket].second = 0;

		int tmp = IndexOfTheBiggerBucket;
		IndexOfTheBiggerBucket = IndexOfTheHelpingBucket;
		IndexOfTheHelpingBucket = IndexOfTheSmallerBucket;
		IndexOfTheSmallerBucket = tmp;
	}

	pair<int*, int> sortedContent = Buckets[IndexOfTheBiggerBucket].first[0];

	ofstream Output("F2.txt");

	Output << sortedContent.first[0];
	cout << sortedContent.first[0];

	for (int i = 1; i < sortedContent.second; i++)
	{
		cout << " " << sortedContent.first[i];
		Output << " " << sortedContent.first[i];
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < Lenght; j++)
			delete[] Buckets[i].first[j].first;

		delete[] Buckets[i].first;
	}

	delete[] Buckets;

	delete[] SeriesArr;

	Output.close();
}