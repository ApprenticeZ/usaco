/*
ID:rookiec1
PROG:palsquare
LANG:C++
 */


#include <fstream>
#include <iostream>
#include <assert.h>

using namespace std;

const int MAX = 300;


/*
 * Input number as string
 * check if the string is palsquare
 */

/*
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
*/

/*
 * transform the number in dex into other base
 */
/*
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
*/

int palsquare()
{
	fstream in("palsquare.in", fstream::in);
	fstream out("palsquare.out", fstream::out);

	assert(in.is_open() && out.is_open());

	int B;
	in >> B;
	assert(B>=2 && B <= 20);

	for(int num=1; num<MAX; ++num)
	{
		string numstr = base_transform(num, B);
		string square_str = base_transform(num*num, B);

		if(isPalsquare(square_str))
			out << numstr << " " << square_str << '\n';

	}

	in.close();
	out.close();

	return 0;
}

