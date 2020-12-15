/*******************************************************************************
 * Name    : shortestpaths.cpp
 * Author  : Eric Rudzin and Edward Chung
 * Version : 1.0
 * Date    : December 7, 2020
 * Description : Solves the all pairs shortest paths problem with Floyd’s algorithm.
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

//global variables
vector<string> alphabet{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
						"N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
long INF = numeric_limits<long>::max();
int num_vertices;
long** intermediate_values;
long** path_lengths;

//converts a string into a number, ie: A-0, B-1... E-5
int letter_to_number(string letter){
    char char_of_letter = letter[0];
    return (int)char_of_letter-65;
}
//creates a 2d matrix with all values as infinity
long** make_2d_matrix(){
	long** my_matrix = new long*[num_vertices];
	for(int i = 0; i < num_vertices; i++){
		my_matrix[i] = new long[num_vertices];
	}
	for(int i = 0; i < num_vertices; i++){
		for(int j = 0; j < num_vertices; j++){
			my_matrix[i][j] = INF;
		}
	}
	return my_matrix;
}
//removes repeated items from a vector
void remove(vector<string> &v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = remove(it + 1, end, *it);
    }
    v.erase(end, v.end());
}

//recursively creates a vector of all vertices on path from v1 to v2
void  display_paths_helper(long v1, long v2, vector<string> &paths){
	if(v1 == v2){
		paths.push_back(alphabet[v1]);
	}
	else if(intermediate_values[v1][v2] == INF){
		paths.push_back(alphabet[v1]);
		paths.push_back(alphabet[v2]);
	}
	else{
		display_paths_helper(v1, intermediate_values[v1][v2], paths);
		display_paths_helper(intermediate_values[v1][v2], v2, paths);
	}

}
//prints out all paths in the path lengths matrix with the intermediate vertices
void display_paths(){
	for(int i = 0; i < num_vertices; i++){
		for(int j = 0; j < num_vertices; j++){
			if (path_lengths[i][j] == INF){
				cout << alphabet[i] << " -> " << alphabet[j] << ", distance: infinity, path: none" << endl;
			}
			else{
				cout << alphabet[i] << " -> " << alphabet[j] << ", distance: " << path_lengths[i][j] << ", path: ";
				vector<string> paths;
				display_paths_helper(i, j, paths);
				remove(paths);
				for (long unsigned int k = 0; k < paths.size(); k++){
					cout << paths[k];
					if (k != paths.size()-1){
						cout << " -> ";
					}
				}
				cout << endl;
			}

		}
	}
}

//returns the amount of digits in a long
int len(long n){
	if(n < 10){
		return 1;
	}
	else{
		return 1 + len(n/10);
	}
}
/**
* Displays the matrix on the screen formatted as a table.
*/
void display_table(long** const matrix, const string &label,
			const bool use_letters = false) {
	cout << label << endl;
	long max_val = 0;
	for (int i = 0; i < num_vertices; i++) {
		for (int j = 0; j < num_vertices; j++) {
			long cell = matrix[i][j];
			if (cell < INF && cell > max_val) {
				max_val = matrix[i][j];
			}
		}
	}
	int max_cell_width = use_letters ? len(max_val) :
			len(max(static_cast<long>(num_vertices), max_val));
	cout << ' ';
	for (int j = 0; j < num_vertices; j++) {
		cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
	}
	cout << endl;
	for (int i = 0; i < num_vertices; i++) {
		cout << static_cast<char>(i + 'A');
		for (int j = 0; j < num_vertices; j++) {
			cout << " " << setw(max_cell_width);
			if (matrix[i][j] == INF) {
				cout << "-";
			} else if (use_letters) {
				cout << static_cast<char>(matrix[i][j] + 'A');
			} else {
				cout << matrix[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

//uses floyd's algorithm to return the path lengths matrix
long** floyd(long** matrix){
	//creates a new matrix
    long** new_matrix = make_2d_matrix();
    //copies over matrix values from the original matrix into the new matrix
    for(int i = 0; i < num_vertices; i++){
    	for(int j = 0; j < num_vertices; j++){
    		new_matrix[i][j] = matrix[i][j];
    	}
    }
    //performs algorithm
    for(int k = 0; k < num_vertices; k++){
        for(int i = 0; i < num_vertices; i++){
            for(int j = 0; j < num_vertices; j++){
            	if (new_matrix[i][k] != INF && new_matrix[k][j] != INF) {
            		if (new_matrix[i][j] > new_matrix[i][k] + new_matrix[k][j]){
						intermediate_values[i][j] = k;
					}
            		new_matrix[i][j] = min(new_matrix[i][j], new_matrix[i][k] + new_matrix[k][j]);
				}
            }
        }
    }
    return new_matrix;
}

int main(int argc, char *argv[]) {
	 // Make sure the right number of command line arguments exist.
	if (argc != 2) {
		cerr << "Usage: " << argv[0] << " <filename>" << endl;
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

	//instantiate distance_array;
	long** distance_matrix;

	try {
		unsigned int line_number = 1;
		// Use getline to read in a line.

		// Check to see if line 1 is a valid integer from 1 to 26
		getline(input_file, line);
		istringstream iss(line);
		if(iss >> num_vertices){
			if(num_vertices < 1 || num_vertices > 26){
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

		//make a subvector containing only letter that would be in range A-num_vertices
		vector<string> sub_alpha{alphabet.begin(), alphabet.end() - 26 + num_vertices};

		//set distance_array = to a matrix of size num_vertices with 0s on the diagonal
		distance_matrix = make_2d_matrix();
		for(int i = 0; i < num_vertices; i++){
		        distance_matrix[i][i] = 0;
		    }

		// See http://www.cplusplus.com/reference/string/string/getline/
		while (getline(input_file, line)) {
			//copy the values from line into a vector as strings
			istringstream iss2(line);
			vector<string> result{istream_iterator<string>(iss2), {}};

			//throw an error if the vector does not contain 3 items
			if(result.size() != 3){
				cerr << "Error: Invalid edge data '" << line << "' on line " << line_number << "."<< endl;
				return 1;
			}
			else{
				int edge;
				//check if starting vertex is in subvector
				if(find(sub_alpha.begin(), sub_alpha.end(), result[0]) == sub_alpha.end()){
					cerr << "Error: Starting vertex '" << result[0] << "' on line " << line_number <<  " is not among valid values " << sub_alpha[0] << "-" << sub_alpha[sub_alpha.size() - 1] << "." << endl;
					return 1;
				}
				//check if ending vertex is in subvector
				if(find(sub_alpha.begin(), sub_alpha.end(), result[1]) == sub_alpha.end()){
					cerr << "Error: Ending vertex '" << result[1] << "' on line " << line_number << " is not among valid values " << sub_alpha[0] << "-" << sub_alpha[sub_alpha.size() - 1] << "." << endl;
					return 1;
				}
				//check if the edge is a valid number
				istringstream iss3(result[2]);
				iss3 >> edge;
				if(edge <= 0){
					cerr << "Error: Invalid edge weight '" << result[2] << "' on line " << line_number << "." << endl;
					return 1;
				}
			}
			//use result vector to update the distance array
			distance_matrix[letter_to_number(result[0])][letter_to_number(result[1])] = stoi(result[2]);

			//increment line number
			++line_number;
		}
		// Don't forget to close the file.
		input_file.close();
	} catch (const ifstream::failure &f) {
		cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
		return 1;
	}
	//set intermediate values = to a 2d matrix
	intermediate_values = make_2d_matrix();

	//display the distance matrix
	display_table(distance_matrix, "Distance matrix:", false);
	//now, create the paths matrix using floyd's algorithm
	path_lengths = floyd(distance_matrix);
	//display the matrices for path lengths and intermediate vertices
	display_table(path_lengths, "Path lengths:", false);
	display_table(intermediate_values, "Intermediate vertices:", true);
	//display all possible paths
	display_paths();

	for(int i = 0; i < num_vertices; i++){
		delete [] distance_matrix[i];
		delete [] path_lengths[i];
		delete [] intermediate_values[i];
	}
	delete [] distance_matrix;
	delete [] path_lengths;
	delete [] intermediate_values;

	return 0;
}

