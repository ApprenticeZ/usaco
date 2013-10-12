/*
ID:rookiec1
PROG:milk
LANG:C++
*/

#include <fstream>
#include <iostream>
#include <cstdlib>
#include <assert.h>

using namespace std;

typedef struct farm
{
	int cost;
	int quant;
}farm;

int compar(const void *a, const void *b)
{
	farm *pa, *pb;
	pa = (farm *)a; pb = (farm *)b;
	return (pa->cost-pb->cost);
}

int main()
{
	fstream in("milk.in", fstream::in);
	fstream out("milk.out", fstream::out);

	assert(in.is_open() && out.is_open());

	int N, M;
	in >> N >> M;

	farm *milk_farms = new farm[M];
	for(int i=0; i<M; ++i)
		in >> (milk_farms+i)->cost >> (milk_farms+i)->quant;

	qsort(milk_farms, M, sizeof(farm), compar);

	// for(int i=0; i<M; ++i)
		// cout << (milk_farms+i)->cost << " " << (milk_farms+i)->quant << endl;

	int remain = N, sum = 0, ptr = 0;
	while(remain)
	{
		int take = remain>(milk_farms+ptr)->quant?(milk_farms+ptr)->quant:remain;
		remain -= take;
		sum += take*((milk_farms+ptr)->cost);
		++ptr;
	}

	out << sum << '\n';

	delete[] milk_farms;

	in.close();
	out.close();

	return 0;
}

