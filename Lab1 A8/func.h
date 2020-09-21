#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

ofstream fill_txt_file(string file_name, int count, int bottom_border, int top_border);
vector<int> file_to_vector(ifstream *input_file);

void modify(vector<int>* source_vector);
void modify(vector<int>::iterator begin, vector<int>::iterator end);
void transform_modify(vector<int>* source_vector);
void foreach_modify(vector<int>* source_vector);
int get_sum(vector<int> source_vector);
double get_average(vector<int> source_vector);
void print_result(vector<int> source_vector);
void save_result_to_file(vector<int> source_vector, ofstream file);
