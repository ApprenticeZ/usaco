/*
ID:rookiec1
PROG:barn1
LANG:C++
*/

#include <fstream>
#include <cstdlib>
#include <iostream>
#include <assert.h>

using namespace std;

/* sort the integer array in descending order
 */
int compar(const void *a, const void *b)
{
	return (*(int *)b-*(int *)a);
}

int main()
{
	fstream in("barn1.in", fstream::in);
	fstream out("barn1.out", fstream::out);

	assert(in.is_open() && out.is_open());

	int N, S, C;
	in >> N >> S >> C;

	int sum = 0;

	/* if more barns than cows, each cow gets a barn
	 * barns are equal to cow num
	 */
	if (N >= C)
	{
		sum = C;
		out << sum << '\n';
	}
	else {
		int *occupied = new int[C]();
		int *diff = new int[C - 1]();
		for (int i = 0; i < C; ++i) {
			in >> *(occupied + i);
		}

		// cow barn # may come in any order, sort it in des order
		qsort(occupied, C, sizeof(int), compar);

		// calculate gap between two adjacent barns
		for (int i = 0; i < C - 1; ++i)
			diff[i] = occupied[i] - occupied[i + 1];

		// sort gap in desc order
		qsort(diff, C - 1, sizeof(int), compar);

		// remove the top N-1 gaps
		for (int i = N - 1; i < C - 1; ++i)
			sum += diff[i];

		// each barn count 1
		sum += N;

		out << sum << '\n';

		delete[] occupied;
		delete[] diff;
	}

	in.close();
	out.close();

	return 0;
}

