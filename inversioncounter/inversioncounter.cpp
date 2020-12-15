/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Eric Rudzin
 * Version     : 1.0
 * Date        : October 29, 2020
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
	long num_inversions = 0;
	for(int i = 0; i < length - 1; i++){
		for(int j = i; j < length - 1; j++){
			if(array[i] > array[j + 1]){
				num_inversions++;
			}
		}
	}
	return num_inversions;
}

/**
 * Counts the number of inversions in an array in theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
	int* scratch = new int[length];
	long num_inversions = mergesort(array, scratch, 0, length - 1);
	delete [] scratch;
	return num_inversions;

}

static long mergesort(int array[], int scratch[], int low, int high) {
	long count = 0;
	if(low < high){
		int mid = low + (high - low) / 2;
		count += mergesort(array, scratch, low, mid);
		count += mergesort(array, scratch, mid + 1, high);
		int l = low;
		int h = mid + 1;
		for(int i = low; i < high + 1; i++){
			if((l <= mid) && ((h > high) || array[l] <= array[h])){
				scratch[i] = array[l];
				l++;
			}
			else{
				scratch[i] = array[h];
				h++;
				count += mid - l + 1;
			}
		}
		for(int i = low; i < high + 1; i++){
			array[i] = scratch[i];
		}
	}
	return count;
}

int main(int argc, char *argv[]) {
	if(argc == 2){
		if(strcmp(argv[1], "slow") != 0){
			cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
			return 1;
		}
	}
	if(argc > 2){
		cerr << "Usage: " << argv[0] << " [slow]" << endl;
		return 1;
	}

    cout << "Enter sequence of integers, each followed by a space: " << flush;



    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    if(values.size() == 0){
    	cerr << "Error: Sequence of integers not received." << endl;
    	return 1;
    }

    if(argc == 2){
    	cout << "Number of inversions: " << count_inversions_slow(&values[0], values.size()) << endl;
    }
    else{
    	cout << "Number of inversions: " << count_inversions_fast(&values[0], values.size()) << endl;
    }

    return 0;
}
