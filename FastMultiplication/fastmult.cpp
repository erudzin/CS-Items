/*******************************************************************************
 * Name        : fastmult.cpp
 * Author      : Eric Rudzin
 * Version     : 1.0
 * Date        : 12/1/2020
 * Description : Implementation of fast multiplication
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
using namespace std;
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include<bits/stdc++.h>

//perfoms addition of long numbers
string add(const string& a, const string& b){
	string first = a;
	string second = b;
	first.erase(0, min(first.find_first_not_of('0'), first.size()-1));
	second.erase(0, min(second.find_first_not_of('0'), second.size()-1));
	while(first.length() > second.length()){
		second = "0" + second;
	}
	while(first.length() < second.length()){
		first = "0" + first;
	}
	string total = "";
	int carry = 0;
	for(long unsigned int i = 0; i < first.length(); i++){
		int num = int(first[first.length() - 1 - i] - '0') + int(second[second.length() - 1 - i] - '0') + carry;
		if(num < 10){
			carry = 0;
			total += char(num + '0');
		}
		else{
			carry = 1;
			total += char(num%10 + '0');
		}
	}
	if(carry == 1){
		total += '1';
	}
	reverse(total.begin(), total.end());
	return total.erase(0, min(total.find_first_not_of('0'), total.size()-1));;
}

//performs subtraction of large numbers
string subtract(const string& a, const string& b) {
	string first = a;
	string second = b;;
	first.erase(0, min(first.find_first_not_of('0'), first.size()-1));
	second.erase(0, min(second.find_first_not_of('0'), second.size()-1));
	while(first.length() > second.length()){
		second = "0" + second;
	}
	while(first.length() < second.length()){
		first = "0" + first;
	}
	string total = "";
	int carry = 0;
	for(long unsigned int i = 0; i < first.length(); i++){

		int num = int(first[first.length() - 1 - i] - '0') - int(second[second.length() - 1 - i] - '0') - carry;
		if(num < 0){
			num += 10;
			carry = 1;
			total += char(num + '0');
		}
		else{
			carry = 0;
			total += char(num + '0');
		}
	}
	reverse(total.begin(), total.end());
	return total.erase(0, min(total.find_first_not_of('0'), total.size()-1));
}

//recursively uses multiplication of large numbers formula
string multiply_helper(const string& a, const string& b) {
	string first = a;
	string second = b;
	while(first.length() > second.length()){
		second = "0" + second;
	}
	while(first.length() < second.length()){
		first = "0" + first;
	}
	if(first.length() == 1){
		return to_string((int(first[0]) - '0') * (int(second[0]) - '0'));
	}
	else if(first.length() % 2 == 1){
		return multiply_helper("0" + first, "0" + second);
	}
	else{
		string a1 = first.substr(0, first.length()/2);
		string a0 = first.substr(first.length()/2);
		string b1 = second.substr(0, second.length()/2);
		string b0 = second.substr(second.length()/2);
		string c2 = multiply_helper(a1, b1);
		string c0 = multiply_helper(a0, b0);
		string c1 = subtract(multiply_helper(add(a1, a0), add(b1, b0)), add(c2, c0));
		for(long unsigned int i = 0; i < first.length(); i++){
			c2 += '0';
		}
		for(long unsigned int i = 0; i < first.length()/2; i++){
			c1 += '0';
		}
        return add(add(c2, c1),c0);
	}
}

//keeps track of negatives and plugs numbers into multiply_helper
string multiply(const string& a, const string& b) {
	int num_neg = 0;
	string first = a;
	string second = b;
	if(first[0] == '-'){
		num_neg++;
		first = first.erase(0,1);
	}
	if(second[0] == '-'){
		num_neg++;
		second = second.erase(0,1);
	}

	if(num_neg % 2 == 0){
		return multiply_helper(first, second);
	}
	else{
		return "-" + multiply_helper(first, second);
	}
}

int main(int argc, char *argv[]) {

	cout << multiply(argv[1], argv[2]) << endl;
}
