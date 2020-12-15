/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Eric Rudzin
 * Date        : September 25, 2020
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
	bool lower = true;
	for(auto letter: s){
		if(!islower(letter)){
			lower = false;
		}
	}
	return lower;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
	unsigned int store = 0;
	for(auto letter: s){
		unsigned int asc = letter - 'a';
		if((store & (1 << asc)) > 0){
			return false;
		}
		store = store | ( 1 << asc);
	}
	return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.
	if(argc != 2){
		cerr << "Usage: " << argv[0] << " <string>" << endl;
		return 1;
	}

	if(!is_all_lowercase(argv[1])){
		cerr << "Error: String must contain only lowercase letters." << endl;
		return 1;
	}

	if(all_unique_letters(argv[1])){
		cout << "All letters are unique." << endl;
	}
	else{
		cerr << "Duplicate letters found." << endl;
		return 1;
	}
}
