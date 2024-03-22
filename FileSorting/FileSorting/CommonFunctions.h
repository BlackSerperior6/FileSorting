#pragma once
#include <iostream>

using namespace std;

void HoareQuickSorting(int* Arr, int startIndex, int endIndex)
{
    //���� ������ ������� <= ������ �����
    if (startIndex <= endIndex)
    {
        int middleElement = Arr[(startIndex + endIndex) / 2]; //������� ������� �������

        //������� ������� ������ � ������� ���������
        int LeftIndex = startIndex;
        int RightIndex = endIndex;

        while (LeftIndex <= RightIndex) //���� ����� ������ <= �������
        {
            while (Arr[LeftIndex] < middleElement) //���� �������� �� ������ ������� < �������� ��������
                LeftIndex++; //����������� ����� ������

            while (Arr[RightIndex] > middleElement) //���� �������� �� ������� ������� > ������� ��������
                RightIndex--; //��������� ������ ������

            if (LeftIndex <= RightIndex) //���� ����� ������ <= �������
            {
                //������ �������� �� ��� �������
                int tmp = Arr[LeftIndex];
                Arr[LeftIndex] = Arr[RightIndex];
                Arr[RightIndex] = tmp;

                LeftIndex++; //����������� ����� ������
                RightIndex--; //��������� ������ ������
            }
        }

        HoareQuickSorting(Arr, startIndex, RightIndex); //������ � ��������. ������ �� ������, ����� = ������ ������
        HoareQuickSorting(Arr, LeftIndex, endIndex); //������ = ����� ������, ����� �� ������
    }
}

void HoareQuickSorting(int* Arr, int Lenght)
{
    if (Lenght > 1)
        HoareQuickSorting(Arr, 0, Lenght - 1); //��������� �������� � ��������� �������� 0 � �������� ����� �������  
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