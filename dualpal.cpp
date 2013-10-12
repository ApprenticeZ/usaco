/*
ID:rookiec1
PROG:dualpal
LANG:C++
*/

#include <fstream>
#include <assert.h>

using namespace std;

const unsigned int MAX = 0xFFFFFFFF;

/*
 * Input number as string
 * check if the string is palsquare
 */
bool isPalsquare(string numstr)
{
	if(numstr.length()<2)
	{
		return true;
	}
	else
	{
		int p=0, q=numstr.length()-1;
		while(p<q)
		{
			if(numstr[p++] != numstr[q--])
				return false;
		}
		return true;
	}
}

/*
 * transform the number in dex into other base
 */
string base_transform(int num, int base)
{
	string numstr;
	int tmp = num;
	while (tmp != 0)
	{
		int mod = tmp % base;
		char c = (mod<=9)?(mod+'0'):(mod-10+'A');
		numstr.insert(0, 1, c);
		tmp /= base;
	}
	return numstr;
}

int main()
{
	fstream in("dualpal.in", fstream::in);
	fstream out("dualpal.out", fstream::out);

	assert(in.is_open() && out.is_open());

	int N, S;
	in >> N >> S;

	unsigned int *pal = new unsigned int[N];
	int top = 0;
	for(unsigned int num=S+1; num<MAX; ++num)
	{
		int count=0;
		for(int base=2; base<11; ++base)
		{
			string numstr = base_transform(num, base);
			if(isPalsquare(numstr))
				++count;
			if(count>1)
				break;
		}

		if(count >= 2)
			pal[top++] = num;
		if(top>N-1)
			break;
	}

	for(int i=0; i<top; ++i)
		out << pal[i] << endl;

	delete[] pal;

	in.close();
	out.close();

	return 0;
}
