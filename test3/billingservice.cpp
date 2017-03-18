#include "billingservice.h"
#include "global.h"
#include<time.h>


float PayFee(Card card)
{
	float paymoney = -1;
	float ustime_min = 0;//使用时间，单位：分钟
	time_t time_on = card.tLast;
	time_t time_down = time(NULL);
	struct tm *tm_on{};
	localtime_s(tm_on, &time_on);
	struct tm *tm_down{};
	localtime_s(tm_down, &time_down);
	ustime_min = (tm_down->tm_year - tm_down->tm_year) * 365 * 24 + (tm_down->tm_yday - tm_down->tm_yday) * 24 +
		(tm_down->tm_hour - tm_on->tm_hour) + (tm_down->tm_min - tm_on->tm_min)*(1.0 / 60);

	if (tm_on->tm_wday == 0 || tm_on->tm_wday == 6)
	{
		paymoney = ustime_min*10.0;
	}
	else
	{
		paymoney = ustime_min*15.0;
	}

	return paymoney;

}

