/*******************************************************************************
 * Name        : sieve.cpp
 * Author      : Eric Rudzin
 * Date        : 9/18/20
 * Description : Sieve of Eratosthenes
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
	cout << endl << "Number of primes found: " << num_primes() << endl << "Primes up to " << limit_ << ":" << endl;

	const int max_prime_width = num_digits(max_prime_),
			primes_per_row = 80 / (max_prime_width + 1);


	if(primes_per_row >= num_primes_){
		for (int i = 2; i <= limit_; i++){
			if(is_prime_[i]){
				if(i != max_prime_){
					cout << i <<  " ";
				}
				else{
					cout << i << endl;
				}
			}
		}
	}
	else{
		int primes_in_row = 1;
		for (int i = 2; i <= limit_; i++){
			if(is_prime_[i]){
				if(primes_in_row < primes_per_row){
					if(i == max_prime_){
						cout << setw(max_prime_width) << i ;
						primes_in_row++;
					}
					else{
						cout << setw(max_prime_width) << i <<  " " ;
						primes_in_row++;
					}
				}
				else{
					cout << setw(max_prime_width) << i << endl;
					primes_in_row = 1;

				}
			}
		}
	}
}


int PrimesSieve::count_num_primes() const {
	int count = 0;
	for(int i = 2; i <= limit_; i++){
		if(is_prime_[i]){
			count++;
		}
	}
	return count;
}

void PrimesSieve::sieve() {
	for(int i=2; i<=limit_;i++){
		is_prime_[i]=true;
	}

	for(int i = 2; i <= sqrt(limit_); i++){
		if(is_prime_[i]){
			for(int j = i*i; j <= limit_; j += i){
				is_prime_[j] = false;
			}
		}
	}

	num_primes_ = count_num_primes();
	for(int i = limit_; i >= 2; i--){
		if(is_prime_[i]){
			max_prime_ = i;
			break;
		}
	}
	num_primes_ = count_num_primes();
}

int PrimesSieve::num_digits(int num) {
	int count = 1;
	while (num > 10){
		num = num /10;
		count++;
	}
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

	PrimesSieve sieve(limit);
	sieve.display_primes();
	return 0;
}
