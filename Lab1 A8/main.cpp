/*
Результатом должна быть консольная программа с текстовым меню,
выполняющая все перечисленные ниже пункты (1-8) для одного из контейнеров и
одного из преобразований. Например, задание A10 означает реализацию
преобразования No10 для вектора.
Написать программу, содержащую следующие функции:
1. Функцию заполнения текстового файла N целыми случайными числами в
диапазоне от -M до M. Имя файла, N и M поступают на вход функции, файл
возвращается функцией как результат (использовать потоки ввода-вывода).
Реализовать два варианта генерации чисел — в цикле и с использованием
алгоритма std::generate.
2. Функцию, получающую файл на вход, и возвращающую последовательный
контейнер, заполненный числами из файла.
3. Функцию modify, выполняющую преобразование полученного контейнера. На вход
функции должен поступать контейнер, в качестве результата функция должна
возвращать модифицированный контейнер.
4. Перегруженную функцию modify, принимающую на вход итераторы начала и конца
обрабатываемой части контейнера.
5. Функцию, реализующую требуемое преобразование с использованием алгоритма
std::transform вместо функции modify.
6. Функцию, реализующую требуемое преобразование с использованием алгоритма
std::for_each вместо функции modify.
7. Функции, вычисляющие сумму и среднее арифметическое чисел, содержащихся в
контейнере.
8. Функцию вывода результата в файл и на экран (опционально).
Вариант контейнера:
A) вектор (std::vector)
Вариант преобразования:
8. Добавить к каждому числу первое нечетное по абсолютной величине число.
*/

#include <iostream>
#include <fstream>
#include "func.h"
#include <algorithm>
#include <string>

using namespace std;

void fill_file()
{
	string file_name;
	int bottom_border, top_border;
	int count;
	cout << "Enter name of file: ";
	cin >> file_name;
	if (file_name == "")
	{
		cout << "Filling file cancelled\n";
		return;
	}
	cout << "Enter bottom border: ";
	cin >> bottom_border;
	cout << "Enter top border: ";
	cin >> top_border;
	cout << "Enter count of numbers: ";
	cin >> count;

	ofstream output_file = fill_txt_file(file_name, count, bottom_border, top_border);
	if (!output_file.is_open())
		cout << "Failed\n";
	else
	{
		output_file.close();
		cout << "Succes!\n";
	}
}

vector<int> txt_to_vector()
{
	vector<int> current_vector;
	string file_name;
	cout << "Enter file name: "
	cin >> file_name;
	ifstream input_file;
	input_file.open(file_name);
	if (!input_file.is_open())
	{
		cout << "Failed\n";
	}
	else
	{
		current_vector = file_to_vector(&input_file);
		input_file.close();
		cout << "Succes!\n";
	}
	return current_vector;
}

int vector_menu(vector<int>* current_vector)
{
	cout << "1 - print vector\n";
	cout << "2 - modify vector\n";
	cout << "3 - modify vector (using iterators)\n";
	cout << "4 - modify vector (transform algorithm)\n";
	cout << "5 - modify vector (for_each algorithm)\n";
	cout << "6 - Sum of vector elements\n";
	cout << "7 - Average of vector elements\n";
	cout << "0 - exit\n";

	char input;
	cin >> input;
	switch (input)
	{
	case '0':
		return 0;
	case '1':
		print_result(*current_vector);
		return 1;
	case '2':
		modify(current_vector);
		return 2;
	case '3':
		modify(current_vector->begin(), current_vector->end());
		return 3;
	case '4':
		transform_modify(current_vector);
		return 4;
	case '5':
		foreach_modify(current_vector);
		return 5;
	case '6':
		cout << "Sum of vector element - " << get_sum(*current_vector) << '\n';
		return 6;
	case '7':
		cout << "Average of vector element - " << get_average(*current_vector) << '\n';
		return 7;
	default:
		cout << "Incorrect input\n";
	}

}

void work_with_vector(vector<int> vector)
{
	cout << "\n***Working with vector***\n";
	while (vector_menu(&vector) != 0) { cout << "\n\n"; };
}

int main_menu()
{
	cout << "1 - Fill text file\n";
	cout << "2 - Text file to Vector\n";
	cout << "0 - Exit\n";

	char input;
	cin >> input;
	vector<int> current_vector;
	switch (input)
	{
	case '0':
		return 0;
	case '1':
		fill_file();
		return 1;
	case '2':
		current_vector = txt_to_vector();
		if (current_vector.size() != 0)
			work_with_vector(current_vector);
		return 2;
		break;
	default:
		cout << "Incorrect input";
		return -1;
	}
	
}

int main()
{

	while (main_menu() != 0) {}
	return 0;
}