/*12. Характеристикой строки матрицы назовём сумму её отрицательных четных элементов.
Расположить строки в соответствии с убыванием характеристик. (Пересыпкина)*/

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <functional>
#include <array>
#include <vector>
#include <string>
using namespace std;

// Главное меню
int Menu()
{
	cout << "---------------------------------------\n";
	cout << "                 MENU                  \n";
	cout << "---------------------------------------\n";
	cout << "1 - Load text from file.\n";
	cout << "2 - Enter text in the console.\n";
	cout << "---------------------------------------\n";
	int p;
	do {
		cin >> p;
		if ((p != 1) && (p != 2))
			cout << "The entered value is invalid. Re-enter.\n";
	} while ((p != 1) && (p != 2));
	getchar();
	cout << "\n";
	return p;
}


int **CreateMatrix(int nrow, int ncol)
{
	int **a = new int *[nrow]; // выделение памяти под матрицу
	for (int i = 0; i < nrow; i++)
		a[i] = new int[ncol]; // выделение памяти
	for (int i = 0; i < nrow; i++)
		for (int j = 0; j < ncol; j++)
			a[i][j] = 0;
	return a;
}

int main()
{
	int **Matrix;
	int nrow, ncol;
	int m = Menu();
	switch (m) {
	case 1:
	{
		string str;
		cout << "Enter file name:" << endl;
		cin >> str;
		// Открытие введенного пользователем файла
		ifstream file(str);
		if (!file.good())
		{
			cout << "Can not open file.\n";
			getchar();
			getchar();
			return 0;
		}
		else
		{
			// Инициализация матрицы 
			file >> nrow;
			file >> ncol;
			Matrix = CreateMatrix(nrow, ncol);
			bool ok = true;
			int i = 0, j = 0, j1 = 0;
			while (i < nrow && !file.eof())
			{
				while (j < ncol && !file.eof())
				{
					int a;
					file >> Matrix[i][j];
					j++;
				}
				i++;
				j1 = j;
				j = 0;
			}

			if (i < nrow || j1 < ncol) //!
			{
				cout << "There is not enough data in the file.\n" << endl;
				getchar();
				getchar();
				ok = false;
			}
			file.close();
			if (!ok)
			{
				return 0;
			}
		}
		break;
	}
	case 2:
	{
		cout << "Enter number of rows: ";
		cin >> nrow;
		cout << "Enter number of columns: ";
		cin >> ncol;

		Matrix = CreateMatrix(nrow, ncol);
		cout << "Enter matrix" << endl;
		for (int i = 0; i < nrow; i++) // ввод матрицы
			for (int j = 0; j < ncol; j++) cin >> Matrix[i][j];
	}
	break;
	default: return 0;
	}
	

	pair<long, int*> *HelpMas = new pair<long, int*>[nrow]; //двумерный массив: сумма элементов в строке-указатель на строку
	long sum;

	for (int i = 0; i < nrow; i++)
	{
		sum = 0;
		for (int j = 0; j < ncol; j++)
			if ((Matrix[i][j]<0) && ((Matrix[i][j] % 2) == 0)) //проверка условий
				sum += Matrix[i][j];
		HelpMas[i] = make_pair(sum, Matrix[i]);
	}
	
	sort(HelpMas, HelpMas + nrow, greater<>());
	cout << "Result" << endl;
	int *str;
	for (int i = 0; i < nrow; i++) // вывод упорядоченной матрицы	
	{
		str = HelpMas[i].second;
		for (int j = 0; j < ncol; j++)
			cout << setw(4) << str[j] << " ";
		cout << setw(2) << "|" << HelpMas[i].first << endl;
	}
	getchar();
	getchar();

    return 0;
}

