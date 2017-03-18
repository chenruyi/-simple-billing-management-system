#include <time.h>
#include<iostream>
#include"global.h"
#include<string.h>
#include<Windows.h>
using namespace std;
//将time_t转化为字符串
void timeToString(time_t t, char *pBuf)
{
	struct tm pTimeInfo;

	localtime_s(&pTimeInfo, &t);

	strftime(pBuf, 50, "%Y-%m-%d %H:%M:%S", &pTimeInfo);

}
char* getTime()
{
	SYSTEMTIME st;
	GetLocalTime(&st);
	char *time = (char *)st.wYear + '\\' + st.wMonth + '\\' + st.wDay + ' ' + st.wHour + ':' + st.wMinute + ':' + st.wSecond;
	return time;
}
time_t stringToTime(char *pTime)
{
	time_t t = time(NULL);
	struct tm s;
	sscanf_s(pTime, "%d-%d-%d %d:%d:%d", &s.tm_year, &s.tm_mon, &s.tm_mday, &s.tm_hour, &s.tm_min, &s.tm_sec);
	s.tm_year -= 1900;
	s.tm_mon -= 1;
	t = mktime(&s);

	return t;
}