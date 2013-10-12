/*
ID: rookiec1
PROG: beads
LANG: C++
*/

#include <fstream>
#include <string>
#include "assert.h"

using namespace std;

int beads()
{
	fstream in("beads.in", fstream::in);
	fstream out("beads.out", fstream::out);

	assert(in.is_open() && out.is_open());

	int N; // number of beads
	string beads;
	in >> N;
	in >> beads;

	beads += beads; // transform the circle into a line
	int back=0, front=0, max=0, white=0;
	char cur_color = beads[0];
	for(int i=0; i<(2*N); ++i)
	{
		if(beads[i] == 'w')
		{
			++front; ++white;
		}
		else if(cur_color == beads[i])
		{
			++front;
			white = 0;
		}
		else
		{
			if(front+back>max)
			{
				max = front+back;
			}
			back = front - white;
			front = white+1;
			cur_color = beads[i];
			white = 0;
		}
	}
	if(front+back>max)
		max = front+back;

	if(max>N)
		max = N;

	out << max << '\n';

	in.close();
	out.close();

	return 0;
}
