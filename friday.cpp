/*
ID: rookiec1
PROG: friday
LANG: C++
*/

#include <fstream>
#include <iostream>
#include <assert.h>

using namespace std;

const int DAYS_PER_WEEK = 7; // every week has 7 days
const int MON_OFFSET = 2; // MON in hist index
const int DAYS_IN_MONTH[]={31, 28, 31, 30, 31, 30,
						 31, 31, 30, 31, 30, 31};
const int MONTH_PER_YEAR = 12;
const int DAY_OFFSET = 12; // 13th is 12 days away from 1st

const int BASE_YEAR = 1900; // start from 1900
const int CENTURY_LEAP_BASE = 400;
const int CENTURY_BASE = 100;
const int LEAP_BASE = 4;
const int MAR = 2;

int friday()
{
	int hist[DAYS_PER_WEEK] = {0};
	int days_spent = DAY_OFFSET-DAYS_IN_MONTH[MONTH_PER_YEAR-1];

	fstream in("friday.in", fstream::in);
	fstream out("friday.out", fstream::out);

	assert(in.is_open() && out.is_open());

	int N = 0;
	in >> N;

	for(int i=0; i<N; ++i)
	{
		bool leapyear;
		int cur_year = i+BASE_YEAR;

		/* A more concise expression
		 *
		 * leapyear = false;
		 * if(cur_year%400==0||(cur_year%100!=0&&cur_year%4==0))
		 *     leapyear = true;
		 */
		if(cur_year%LEAP_BASE!=0)
			leapyear = false;
		// mod by 4
		else
		{
			// leap year and century year
			if(cur_year%CENTURY_LEAP_BASE==0)
			{
				leapyear = true;
			}
			else
			{
				// leap year but not century year
				if(cur_year%CENTURY_BASE)
					leapyear = true;
				// century year but not leap year
				else
					leapyear = false;
			}
		}

		for(int j=0; j<MONTH_PER_YEAR; ++j)
		{
			days_spent += DAYS_IN_MONTH[(j+MONTH_PER_YEAR-1)%MONTH_PER_YEAR];
			// add days in FEB when we calculate Mar. 13th!
			if(leapyear && j==MAR)
				++days_spent;
			int idx = (days_spent%DAYS_PER_WEEK+MON_OFFSET)%DAYS_PER_WEEK;
			++hist[idx];
		}

	}

	// output
	for(int i=0; i<DAYS_PER_WEEK; ++i)
	{
		out << hist[i];
		if(i<DAYS_PER_WEEK-1)
			out << " ";
	}
	out << "\n";

	in.close();
	out.close();
	return 0;
}
