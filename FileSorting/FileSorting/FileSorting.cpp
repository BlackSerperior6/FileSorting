#include <iostream>
#include <fstream>

#include "NaturalMerge.h"
#include "ManyPhaseMerge.h"

using namespace std;

typedef void(*functionPointer)(ifstream*, int);

int main()
{
	srand(time(0));
	setlocale(LC_ALL, "RUS");

	functionPointer functions[] = {&SortUsingNaturalMerge, &SortUsingManyPhaseMerging};
	int Lenght;

	for (functionPointer function : functions)
	{
		cout << "Режим генерации случайных элементов" << endl;

		cin >> Lenght;

		ofstream Output("F1.bin", ios_base::binary);

		for (int i = 0; i < Lenght; i++)
		{
			int element = rand() % 100;

			cout << element << " ";

			Output.write(reinterpret_cast<const char*>(&element), sizeof(element));
		}

		cout << endl;

		Output.close();

		ifstream Input("F1.bin", ios_base::binary);

		function(&Input, Lenght);

		cout << endl << endl;
	}
}
