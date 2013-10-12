/*
ID:rookiec1
PROG:transform
LANG:C++
*/

#include <fstream>
#include <iostream>
#include <assert.h>

using namespace std;

/* rotate src square clockwise by 90 deg
 * N is the side length of square
 * save the rotated pattern in mid
 * if mid == dest, return true; else return false
 */
bool ror90(const char *src, char *mid, const char *dest, int N)
{
	bool isEqual = true;
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<N; ++j)
		{
			*(mid + j*N + (N-i-1)) = *(src+i*N+j);
			if( *(dest+j*N+(N-i-1))!=*(mid+j*N+(N-i-1)))
				isEqual = false;
		}
	}
	return isEqual;
}

/* reflect square horizontally
 *
 */
bool horizon_reflect(const char *src, char *mid, const char* dest, int N)
{
	bool isEqual = true;
	// copy src to mid
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<N; ++j)
			*(mid+i*N+j) = *(src+i*N+j);
	}
	// horizontally reflect mid
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<=(N-1)/2 && j<(N-j-1); ++j)
		{
			char tmp = *(mid+i*N+j);
			*(mid+i*N+j) = *(mid+i*N+N-j-1);
			*(mid+i*N+N-j-1) = tmp;
			if(!( *(mid+i*N+j)==*(dest+i*N+j) && *(mid+i*N+N-j-1) == *(dest+i*N+N-j-1) ))
				isEqual = false;
		}
	}
	if((N-1)%2==0)
	{
		for(int i=0; i<N; ++i)
		{
			if(*(mid+i*N+(N-1)/2)!=*(dest+i*N+(N-1)/2))
				isEqual = false;
		}
	}
	return isEqual;
}

bool swap_squares(char *a, char *b, int N)
{
	if(a==b)
		return false;
	else
	{
		for(int i=0; i<N; ++i)
		{
			for(int j=0; j<N; ++j)
				*(a+i*N+j) = *(b+i*N+j);
		}
		return true;
	}
}

bool equal_square(const char* a, const char* b, int N)
{
	bool isEqual = true;
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<N; ++j)
		{
			if(*(a+i*N+j)!=*(b+i*N+j))
			{
				isEqual = false;
				return isEqual;
			}
		}
	}
	return isEqual;
}

/*
 * helper function: print the square to console
 */
void print_square(char *src, int N)
{
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<N; ++j)
		{
			cout << *(src+i*N+j) << ' ';
			if(j==N-1)
				cout << '\n';
		}
	}
}

int main()
{
	fstream in("transform.in", fstream::in);
	fstream out("transform.out", fstream::out);

	assert(in.is_open() && out.is_open());

	int N;
	in >> N;
	char *src = new char[N*N]();
	char *mid = new char[N*N]();
	char *mid2 = new char[N*N]();
	char *dest = new char[N*N]();
	
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<N; ++j)
		{
			in >> *(src+i*N+j);
			*(mid+i*N+j) = *(src+i*N+j);
		}
	}
	
	for(int i=0; i<N; ++i)
	{
		for(int j=0; j<N; ++j)
			in >> *(dest+i*N+j);
	}

	int pattern = 1;
	bool cont = true;
	while (cont) {
		switch (pattern) {
		// rotate 90 deg
		case (1):
			cont = !ror90(src, mid, dest, N);
			// print_square(mid, N);
			if (cont)
				++pattern;
			//cout << "continue? " << cont << " next pattern: " << pattern << endl;
			break;
			// rotate 180 deg
		case (2):
			cont = !ror90(mid, mid2, dest, N);
			// print_square(mid2, N);
			if (cont)
				++pattern;
			//cout << "continue? " << cont << " next pattern: " << pattern << endl;
			break;
			// rotate 270 deg
		case (3):
			cont = !ror90(mid2, mid, dest, N);
			if (cont)
				++pattern;
			//cout << "continue? " << cont << " next pattern: " << pattern << endl;
			break;
			// horizontal reflect
		case (4):
			cont = !horizon_reflect(src, mid, dest, N);
			//print_square(mid, N);
			if (cont)
				++pattern;
			//cout << "continue? " << cont << " next pattern: " << pattern << endl;
			break;
			// horizontal reflect + rotation 90->180->270
		case (5):
			for (int i = 0; i < 3; ++i) {
				cont = !ror90(mid, mid2, dest, N);
				if (cont)
					swap_squares(mid, mid2, N);
				else
					break;
			}
			if (cont)
				++pattern;
			//cout << "continue? " << cont << " next pattern: " << pattern << endl;
			break;
			// if src is equal to dest
		case (6):
			cont = !equal_square(src, dest, N);
			if (cont)
				++pattern;
			//cout << "continue? " << cont << " next pattern: " << pattern << endl;
			break;
		default:
			cont = false;
			break;
		}
	}

	out << pattern << endl;

	delete[] src;
	delete[] mid;
	delete[] mid2;
	delete[] dest;
	
	in.close();
	out.close();
	return 0;
}
