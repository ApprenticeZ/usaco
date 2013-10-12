/*
ID: rookiec1
PROG: gift1
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include "assert.h"

using namespace std;

int gift()
{
	fstream in("gift1.in", fstream::in);
	fstream out("gift1.out", fstream::out);

	assert(in.is_open() && out.is_open());

	int usernum = 0;
	in >> usernum;

	// initialize the array with 0
	int *cost_gift = new int[usernum]();
	int *receive_gift = new int[usernum]();

	map<string, int> name_idx;
	vector<string> name_seq; // maintain the order of input name
	for(int i=0; i<usernum; ++i)
	{
		string username;
		in >> username;
		name_idx[username] = i;
		name_seq.push_back(username);
	}

	for(int i=0; i<usernum; ++i)
	{
		string username;
		int usercost, receivernum;
		in >> username;
		in >> usercost >> receivernum;
		cost_gift[name_idx[username]] = usercost;

		int cost_per_user = 0;
		// avoid divide by 0
		if(receivernum)
		{
			cost_per_user = usercost/receivernum;
			receive_gift[name_idx[username]] += usercost%receivernum; // money kept by the giver
		}

		for(int j=0; j<receivernum; ++j)
		{
			string receivername;
			in >> receivername;
			receive_gift[name_idx[receivername]] += cost_per_user;
		}
	}

	// write result to output
	for(int i=0; i<usernum; ++i)
	{
		string username = name_seq[i];
		out << username << " " << (receive_gift[name_idx[username]]-cost_gift[name_idx[username]]) << "\n";
	}

	delete[] cost_gift;
	delete[] receive_gift;
	in.close();
	out.close();

	return 0;
}

