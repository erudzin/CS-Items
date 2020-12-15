/*
 * pointers.cpp
 *
 *  Created on: Sep 4, 2020
 *      Author: user
 */

#include <iostream>

using namespace std;

int main(){
	int x = 5, *z = &x;
	cout << &x << " " << z << endl;
	cout << x << " " << *z << endl;
	*z = 7;
	cout << x << " " << z << endl;
	int y = 6;
	z = &y;
	cout << x << " " << *z << endl;
	return 0;
}



