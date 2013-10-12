/*
ID:rookiec1
PROG:namenum
LANG:C++
 */

#include <fstream>
#include <vector>
#include <map>
// #include <iostream>
#include <cstdlib>
#include <assert.h>

using namespace std;

const int KEYNUM = 3;
string dictname_to_number(string dict_name)
{
	int len = dict_name.length();
	string num_name;
	for(int i=0; i<len; ++i)
	{
		int offset = (dict_name[i]-'A');
		offset = offset>17?offset-1:offset;
		num_name.push_back(offset/KEYNUM+'2');
	}
	return num_name;
}

int compar(const void *a, const void *b)
{
	string *ptra = (string*)a;
	string *ptrb = (string*)b;
	return ((ptra)->compare(*ptrb));
}

int namenum()
{
	fstream in("namenum.in", fstream::in);
	fstream out("namenum.out", fstream::out);
	fstream namedict("dict.txt", fstream::in);

	assert(in.is_open() && out.is_open() && namedict.is_open());

	string digit_name;
	in >> digit_name;

	// build hashtable for namedict
	string sorted_name[100];
	int i=0;
	map<string, char> dict;
	string valid_name;
	while(namedict >> valid_name)
	{
		if(valid_name.length() == digit_name.length())
		{
			string valid_numname = dictname_to_number(valid_name);
			if(digit_name.compare(valid_numname)==0)
				sorted_name[i++] = valid_name;
		}
	}

	if(i>0)
	{
		qsort(sorted_name, i, sizeof(digit_name), compar);
		for(int j=0; j<i; ++j)
			out << sorted_name[j] << "\n";
	}
	else
		out << "NONE" << '\n';

	in.close();
	out.close();
	namedict.close();

	return 0;
}
