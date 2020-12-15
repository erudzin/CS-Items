/*******************************************************************************
 * Name    : powergrid.cpp
 * Author  : Eric Rudzin
 * Version : 1.0
 * Date    : December 14, 2020
 * Description : Reads the graph representation from a file and computes the minimum set of roads on which to install power lines.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
#include <iterator>
#include <sstream>
#include <algorithm>
#include <iomanip>
using namespace std;

int num_vertices;

//creates a 2d matrix with all values as infinity
string** make_2d_matrix(){
	string** my_matrix = new string*[num_vertices+1];
	for(int i = 0; i < num_vertices; i++){
		my_matrix[i] = new string[num_vertices+1];
	}
	for(int i = 0; i < num_vertices; i++){
		for(int j = 0; j < num_vertices; j++){
			my_matrix[i][j] = "none";
		}
	}
	return my_matrix;
}

void delete_matrix(string** matrix){
	for(int i = 0; i < num_vertices; i++){
		delete [] matrix[i];
	}
	delete [] matrix;
}

bool is_int(string str){
	int x;
	stringstream s(str);
	if(s >> x){
		return true;
	}
	else{
		return false;
	}
}


vector<int> makeset(){
	vector<int> set(num_vertices + 1);
	for(unsigned int i = 0; i < set.size() + 1; i++){
		set[i] = i;
	}
	return set;
}

void union_vertices(vector<int> set, int x, int y){
	set[y] = x;
}

int find_root(vector<int> set, int x){
	int index = x;
	while(set[index] != index){
		index = set[index];
	}
	return index;
}

void kruskal(vector<int> set, vector<pair<int,pair<int, int>>> weights){
	for(int i = 0; i < num_vertices + 1; i++){
		int first_vert = find_root(set, weights[i].second.first);
		int second_vert = find_root(set, weights[i].second.second);
		if(first_vert == second_vert){
			set[second_vert] = first_vert;
		}
	}
}



int main(int argc, char *argv[]) {
	 // Make sure the right number of command line arguments exist.
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <input file>" << endl;
		return 1;
	}
	// Create an ifstream object.
	ifstream input_file(argv[1]);
	// If it does not exist, print an error message.
	if (!input_file) {
		cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
		return 1;
	}
	// Add read errors to the list of exceptions the ifstream will handle.
	input_file.exceptions(ifstream::badbit);
	string line;

	try {
		unsigned int line_number = 1;
		// Use getline to read in a line.

		// Check to see if line 1 is a valid integer from 1 to 26
		getline(input_file, line);
		istringstream iss(line);
		if(iss >> num_vertices){
			if(num_vertices < 1 || num_vertices > 1000){
				if(num_vertices == 1){
					cout << "No solution." << endl;
					return 0;
				}
				cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
				return 1;
			}
		}
		else{
			cerr << "Error: Invalid number of vertices '" << line << "' on line " << line_number << "." << endl;
			return 1;
		}

		// increment to line 2 before loop
		line_number ++;
		string** street_names = make_2d_matrix();
		vector<pair<int, pair<int, int>>> paths;

		// See http://www.cplusplus.com/reference/string/string/getline/
		while (getline(input_file, line)) {
			//copy the values from line into a vector as strings
			vector<string> result;
			stringstream iss2(line);
			while(iss2.good()){
				string sub;
				getline(iss2, sub, ',');
				result.push_back(sub);
			}
			//throw an error if the vector does not contain 3 items
			if(result.size() != 4){
				delete_matrix(street_names);
				cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "."<< endl;
				return 1;
			}
			else{

				//check if starting vertex is in subvector

				if(!is_int(result[0]) || (stoi(result[0]) < 1 || stoi(result[0]) > num_vertices)){
					delete_matrix(street_names);
					cerr << "Error: Starting vertex '" << result[0] << "' on line " << line_number <<  " is not among valid values 1-" << num_vertices << "." << endl;
					return 1;
				}
				//check if ending vertex is in subvector

				if(!is_int(result[1]) || (stoi(result[1]) < 1 || stoi(result[1]) > num_vertices)){
					delete_matrix(street_names);
					cerr << "Error: Ending vertex '" << result[1] << "' on line " << line_number <<  " is not among valid values 1-" << num_vertices << "." << endl;
					return 1;
				}

				//check if the edge is a valid number
				if(!is_int(result[2]) || stoi(result[2]) <= 0){
					delete_matrix(street_names);
					cerr << "Error: Invalid edge weight '" << result[2] << "' on line " << line_number << "." << endl;
					return 1;
				}
			}
			paths.push_back(make_pair(stoi(result[2]), make_pair(stoi(result[0]), stoi(result[1]))));
			//increment line number
			++line_number;
		}
		sort(paths.begin(), paths.end());
		// Don't forget to close the file.
		input_file.close();
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		input_file.close();
		return 1;
	}


	return 0;
}
