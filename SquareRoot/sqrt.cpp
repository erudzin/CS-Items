/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Eric Rudzin
 * Version : 1.0
 * Date    : September 3, 2020
 * Description : Computes the square root of two command-line arguments.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <cmath>
#include <iomanip>
#include <limits>

using namespace std;

double sqrt(double num, double epsilon){
	double last_guess = num;
	double next_guess;

	if (num < 0.0){
		return numeric_limits<double>::quiet_NaN();
	}

	else if (num == 0.0){
		return num;
	}

	else if(num == 1.0){
		return num;
	}

	else{
		next_guess = (last_guess + num/last_guess) / 2;
		while (!(abs(last_guess - next_guess) <= epsilon)){
			last_guess = next_guess;
			next_guess = (last_guess + num/last_guess) / 2;
		}
	}
	return next_guess;
}

int main(int argc, char* const argv[]){
    istringstream iss;
    double num, epsilon;

    if (argc > 3){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }

    if (argc < 2){
        cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
        return 1;
    }

    iss.str(argv[1]);
    if (!(iss >> num)) {
        cerr << "Error: Value argument must be a double." << endl;
        return 1;
    }

    if (argc == 2){
            epsilon = 1e-7;
    }

    if (argc == 3){
    	iss.clear();
        iss.str(argv[2]);
        if (!(iss >> epsilon)) {
            cerr << "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
        if (epsilon <= 0){
            cerr<< "Error: Epsilon argument must be a positive double." << endl;
            return 1;
        }
    }

    cout << setprecision(8);
    cout << fixed;
    cout << sqrt(num, epsilon) << endl;
    return 0;
}



