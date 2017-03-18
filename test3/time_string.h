
#ifndef TOOL_H
#define	TOOL_H
#include <time.h>
void timeToString(time_t t, char*p);
time_t stringToTime(char *pTime);
char* getTime();
#endif