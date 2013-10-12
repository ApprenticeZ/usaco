/*
ID: rookiec1
PROG: milk2
LANG: C++
*/

#include <fstream>
#include <stdlib.h>
#include <assert.h>
#include <iostream>

using namespace std;

typedef struct period
{
	int start, end;
}period;

int period_compar(const void *a, const void *b)
{
	period *pa, *pb;
	pa = (period*)a; pb = (period*)b;
	if(pa->start < pb->start)
		return -1;
	else if(pa->start == pb->start)
		return 0;
	else
		return 1;

}

int milk2()
{
	fstream in("milk2.in", fstream::in);
	fstream out("milk2.out", fstream::out);

	assert(in.is_open() && out.is_open());

	int N;
	in >> N;

	period *farmers = new period[N];
	for(int i=0; i<N; ++i)
	{
		in >> farmers[i].start >> farmers[i].end;
	}

	qsort(farmers, N, sizeof(period), period_compar);
	int max_work=farmers[0].end-farmers[0].start,
		max_rest=0, cont_work=0, cont_rest=0,
		last_start = farmers[0].start, last_end = farmers[0].end;
	int i=0;
	while(i<N-1)
	{
		// compute gap
		if(last_end<farmers[i+1].start)
		{
			cont_rest = farmers[i+1].start - last_end;
			max_rest = (cont_rest>max_rest && farmers[i+1].end>last_end)?cont_rest:max_rest;
			last_start = farmers[i+1].start;
			last_end = farmers[i+1].end;
		}
		// merge two slots
		else
		{
			last_end = farmers[i+1].end>last_end?farmers[i+1].end:last_end;
			cont_work = last_end - last_start;
			int work_period = farmers[i].end-farmers[i].start;
			if(work_period>cont_work)
			{
				cont_work = work_period;
			}
			max_work = (cont_work>max_work)?cont_work:max_work;
		}
		++i;
	}

	out << max_work << " " << max_rest << "\n";

	delete[] farmers;
	in.close();
	out.close();

	return 0;
}
