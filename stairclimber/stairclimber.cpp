/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Eric Rudzin
 * Date        : October 2, 2020
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;

vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.
	vector<vector<int>> ways;
	if(num_stairs <= 0){
		ways.push_back(vector<int> ());
	}
	else{
		for(int i = 1; i <= 3; i++){
			if (num_stairs >= i){
				vector<vector<int>> result = get_ways(num_stairs - i);
				for(unsigned int j = 0; j < result.size(); j++){
					result[j].insert(result[j].begin(), i);
				}
				ways.insert(ways.end(), result.begin(), result.end());
			}
		}
	}
	return ways;
}

void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
	for(unsigned int i = 0; i < ways.size(); i++){
		if(ways.size() > 9){
			cout << setw(2) << i + 1 << ". [" ;
		}
		else{
			cout << i + 1 << ". [";
		}
		for (unsigned int j = 0; j < ways[i].size(); j++){
			if(j < ways[i].size() - 1){
				cout << ways[i][j] << ", ";
			}
			else{
				cout << ways[i][j] << "]" << endl;
			}
		}
	}

}

int main(int argc, char * const argv[]) {
	int x;
	istringstream iss;

	if(argc != 2){
		cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
		return 1;
	}

	iss.str(argv[1]);;
	if(!(iss >> x)){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	iss >> x;
	if( x <= 0 ){
		cerr << "Error: Number of stairs must be a positive integer." << endl;
		return 1;
	}
	if(x > 1){
		cout << get_ways(x).size() << " ways to climb " << argv[1] << " stairs." << endl;
	}
	else{
		cout << get_ways(x).size() << " way to climb " << argv[1] << " stair." << endl;
	}
	display_ways(get_ways(x));
}
