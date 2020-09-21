#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;


class randomizer
{
private:
	int min, max;
public:
	randomizer(int min, int max)
	{
		this->min = min;
		this->max = max;
		srand(time(NULL));
	}

	int operator()()
	{
		if (max == min)
			return max;
		return (rand() % (max - min)) + min;
	}
};
ofstream fill_txt_file(string file_name, int count, int bottom_border, int top_border)
{
	ofstream output_file;
	vector<int> tmp_vector;
	if (bottom_border > top_border)
		swap(bottom_border, top_border);
	randomizer tmp_randomizer(bottom_border, top_border);
	/*for (int i = 0; i < count; i++)
	{
		tmp_vector.push_back(tmp_randomizer());
	}*/ // using loop
	if (count > 0)
	{
		tmp_vector.resize(count);
		generate(tmp_vector.begin(), tmp_vector.end(), tmp_randomizer); // using generate
		output_file.open(file_name);
		for (int num : tmp_vector)
		{
			output_file << num << ' ';
		}
	}

	return output_file;
}
vector<int> file_to_vector(ifstream *input_file)
{
	vector<int> current_vector;
	int tmp_num;
	while (*input_file >> tmp_num)
	{
		current_vector.push_back(tmp_num);
	}
	return current_vector;
}

bool is_not_odd(int value)
{
	return value % 2 != 0;
}

int find_first_not_odd(vector<int>::iterator begin, vector<int>::iterator end)
{
	int first_odd = 0;
	vector<int>::iterator odd_iterator = std::find_if(begin, end, is_not_odd);
	if (odd_iterator != end)
		first_odd = *odd_iterator;
	return first_odd;
}

void modify(vector<int>::iterator begin, vector<int>::iterator end)
{
	int first_odd = find_first_not_odd(begin, end);
	for (vector<int>::iterator current = begin; current < end; current++)
		*current += first_odd;

}

void modify(vector<int>* source_vector)
{
	modify(source_vector->begin(), source_vector->end());
}

class transform_modifyer
{
private:
	int value;
public:
	transform_modifyer(int value) : value(value) {}
	int operator()(int num) {return num + value;}
};
void transform_modify(vector<int>* source_vector)
{
	int first_odd = find_first_not_odd(source_vector->begin(), source_vector->end());
	vector<int> new_vector;
	new_vector.resize(source_vector->size());
	transform_modifyer tmp_mod(first_odd);
	transform(source_vector->begin(), source_vector->end(), source_vector->begin(), tmp_mod);

}

class foreach_modifyer
{
private:
	int value;
	//vector<int> *new_vector;
public:
	foreach_modifyer(int value) : value(value) {};// { new_vector = new vector<int>; }
	void operator()(int &num) { num += value; }
	//vector<int> get_vector() { return *new_vector; }
};
void foreach_modify(vector<int>* source_vector)
{
	int first_odd = find_first_not_odd(source_vector->begin(), source_vector->end());
	foreach_modifyer tmp_mod(first_odd);
	for_each(source_vector->begin(), source_vector->end(), tmp_mod);
	//return tmp_mod.get_vector();
}
int get_sum(vector<int> source_vector)
{
	int sum = 0;
	for (int num : source_vector)
		sum += num;
	return sum;
}
double get_average(vector<int> source_vector)
{
	return ((double)get_sum(source_vector)) / source_vector.size();
}
void print_result(vector<int> source_vector)
{
	for_each(source_vector.begin(), source_vector.end(), [](int num) {cout << num << ' '; });
	cout << endl;
}
void save_result_to_file(vector<int> source_vector, ofstream file)
{
	for (int num : source_vector)
		file << num;
	file << endl;
}