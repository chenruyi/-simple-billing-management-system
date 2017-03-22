#include "writeusinginfo.h"
#include <iostream>
#include"struct.h"

#include "time_string.h"
#include"writeusinginfo.h"
#include <fstream>
#include<iomanip>
#include"global.h"
#include"writeusinginfo.h"
using namespace std;

bool writeusinginfo(usingInfo info)
{
	ofstream fout("usinginfo.txt", ios::app);
	if (!fout.is_open())
	{
		return false;
	}
	char time[TIMELENGTH];
	timeToString(info.operate_time, time);
	fout << info.aName << '\t' << info.operatekind << '\t' 
		<< setiosflags(ios::fixed) << setprecision(2) 
		<< info.fBalance << '\t' << time << '\n';
	return true;
}


