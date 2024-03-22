#pragma once

#include <iostream>
#include <fstream>

#include "CommonFunctions.h"

using namespace std;

void SortUsingNaturalMerge(istream *file, int Lenght)
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

	while (AmountOfSeries > 1)
	{
		for (int i = 0; i < AmountOfSeries - 1; i++)
		{
			pair<int*, int> MergedSeries = MergeSeries(SeriesArr[i], SeriesArr[i + 1]);

			delete[] SeriesArr[i].first;
			SeriesArr[i] = MergedSeries;
			RemoveElement(SeriesArr, i + 1, AmountOfSeries);
			AmountOfSeries--;
		}
	}

	pair<int*, int> sortedContent = SeriesArr[0];

	ofstream Output("F2.txt");

	Output << sortedContent.first[0];
	cout << sortedContent.first[0];

	for (int i = 1; i < sortedContent.second; i++)
	{
		cout << " " << sortedContent.first[i];
		Output << " " << sortedContent.first[i];
	}
	
	Output.close();

	delete[] sortedContent.first;
	delete[] SeriesArr;
}