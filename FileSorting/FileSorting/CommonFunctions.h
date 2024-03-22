#pragma once
#include <iostream>

using namespace std;

void HoareQuickSorting(int* Arr, int startIndex, int endIndex)
{
    //Если индекс начался <= индекс конца
    if (startIndex <= endIndex)
    {
        int middleElement = Arr[(startIndex + endIndex) / 2]; //Находим средний элемент

        //Заводим индексы левого и правого элементов
        int LeftIndex = startIndex;
        int RightIndex = endIndex;

        while (LeftIndex <= RightIndex) //Пока левый индекс <= правого
        {
            while (Arr[LeftIndex] < middleElement) //Пока значение по левому индексу < среднего элемента
                LeftIndex++; //Увеличиваем левый индекс

            while (Arr[RightIndex] > middleElement) //Пока значение по правому индексу > среднее значение
                RightIndex--; //Уменьшаем правый индекс

            if (LeftIndex <= RightIndex) //Если левый индекс <= правого
            {
                //Меняем значение по ним местами
                int tmp = Arr[LeftIndex];
                Arr[LeftIndex] = Arr[RightIndex];
                Arr[RightIndex] = tmp;

                LeftIndex++; //Увеличиваем левый индекс
                RightIndex--; //Уменьшаем правый индекс
            }
        }

        HoareQuickSorting(Arr, startIndex, RightIndex); //Уходим в рекурсию. Начало не меняем, конец = правый индекс
        HoareQuickSorting(Arr, LeftIndex, endIndex); //Начало = левый индекс, конец не меняем
    }
}

void HoareQuickSorting(int* Arr, int Lenght)
{
    if (Lenght > 1)
        HoareQuickSorting(Arr, 0, Lenght - 1); //Запускаем рекурсию с начальным индексом 0 и индексом конца массива  
}

pair<int*, int> MergeSeries(pair<int*, int>& SeriesOne, pair<int*, int>& SeriesTwo)
{
	pair<int*, int> NewSeries;
	NewSeries.first = new int[SeriesOne.second + SeriesTwo.second];

	for (int i = 0; i < SeriesOne.second; i++)
		NewSeries.first[i] = SeriesOne.first[i];

	int counter = SeriesOne.second;

	for (int i = 0; i < SeriesTwo.second; i++)
	{
		NewSeries.first[counter] = SeriesTwo.first[i];
		counter++;
	}

	NewSeries.second = SeriesOne.second + SeriesTwo.second;

	HoareQuickSorting(NewSeries.first, NewSeries.second);

	return NewSeries;
}

void RemoveElement(pair<int*, int>* Arr, int Index, int Lenght)
{
	delete[] Arr[Index].first;
	for (int i = Index; i < Lenght - 1; i++)
		Arr[i] = Arr[i + 1];
}