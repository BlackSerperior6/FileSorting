#include <iostream>
#include <fstream>

#include "ManyPhaseMerge.h"

using namespace std;

int main()
{
	srand(time(0));
	int Lenght;

	cin >> Lenght;

	ofstream Output("F1.bin");

	for (int i = 0; i < Lenght; i++)
	{
		int element = rand() % 100;

		cout << element << " ";

		Output.write((char*) &element, sizeof(int));
	}

	cout << endl;

	Output.close();

	ifstream Input("F1.bin");

	SortUsingManyPhaseMerging(&Input, Lenght);
}
