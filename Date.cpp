#include "date.h"



Date::Date()
{
    day = 0;
    month = 0;
    year = 0;
}

Date::Date(unsigned d, unsigned mon, unsigned y)
{
    day = d;
    month = mon;
    year = y;
}

void Date::SetDay(unsigned d)
{
    day = d;
}

unsigned Date::GetDay() const
{
    return day;
}

void Date::SetMonth(unsigned mon)
{
    month = mon;
}

unsigned Date::GetMonth() const
{
    return month;
}

void Date::SetYear(unsigned y)
{
    year = y;
}

unsigned Date::GetYear() const
{
    return year;
}



string Date::ConvertMonthToString(const int num){ //Converts a numeric month value into string

    string MonthString;

    switch(num){ //Switch case which takes a numeric value from 1-12 and converts into string

    case 1: MonthString = "January"; // 1 is January
        break;
    case 2: MonthString = "February"; // 2 is February
        break;
    case 3: MonthString = "March"; // 3 is March
        break;
    case 4: MonthString = "April"; // 4 is April
        break;
    case 5:MonthString = "May"; // 5 is May
        break;
    case 6: MonthString = "June"; // 6 is June
        break;
    case 7: MonthString = "July"; // 7 is July
        break;
    case 8: MonthString = "August"; // 8 is August
        break;
    case 9: MonthString = "September"; // 9 is September
        break;
    case 10: MonthString = "October"; // 10 is October
        break;
    case 11: MonthString = "November"; // 11 is November
        break;
    default:MonthString = "December"; // 12 is December
        break;
    }
    return MonthString; // returns the month value as string
}
