/*
 ID:rookiec1
 PROG:crypt1
 LANG:C++
 */

#include <fstream>
#include <iostream>
#include <assert.h>

using namespace std;

const int MIN_A = 111;
const int MAX_A = 1000;
const int MIN_B = 11;
const int MAX_B = 100;

bool validnum(int num, const int* h) {
	bool is_valid = true;
	while (num) {
		int a = num % 10;
		if (a==0 || h[--a] < 1) {
			is_valid = false;
			break;
		}
		num /= 10;
	}
	return is_valid;
}

int main() {
	fstream in("crypt1.in", fstream::in);
	fstream out("crypt1.out", fstream::out);

	assert(in.is_open() && out.is_open());
	int N = 0;
	int htbl[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

	// set up hash table
	in >> N;
	int count = 0; // final output
	int rbit = 0;
	for (int i = 0; i < N; ++i) {
		in >> rbit;
		htbl[rbit - 1] = 1;
	}
	// print_htbl(htbl);

	for (int a = MIN_A; a < MAX_A; ++a) {
		for (int b = MIN_B; b < MAX_B; ++b) {
			if (validnum(a, htbl) && validnum(b, htbl)) {
				int b1 = b % 10;
				int b2 = (b / 10) % 10;
				int c = a*b1; // first part sum
				int d = a*b2; // second part sum
				int e = c+10*d; // final output
				if(c<MAX_A && d<MAX_A && e<10000
				   && validnum(c, htbl) && validnum(d, htbl)
				   && validnum(e, htbl))
				{
					// cout << a << '\t' << b << endl;
					++count;
				}
			}
		}
	}
	// cout << "output in stdio: " << count << endl;
	out << count << "\n";

	in.close();
	out.close();

	return 0;
}

