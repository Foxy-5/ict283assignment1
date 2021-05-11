#include "date.h"

date::date()
{
    day = 1;
    month = 1;
    year = 2000;
}

date::date(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

void date::setDay(int d)
{
    day = d;
}

int date::getDay() const
{
    return day;
}

void date::setMonth(int m)
{
    month = m;
}

int date::getMonth() const
{
    return month;
}

void date::setYear(int y)
{
    year = y;
}

int date::getYear() const
{
    return year;
}

void date::SetDate(int d, int m, int y)
{
    day = d;
    month = m;
    year = y;
}

string date::monthConvert(int m)
{
    string MonthArray[] = {"January", "February", "March", "April", "May", "June"
                    , "July", "August", "September", "October", "November", "December"};

    return MonthArray[m-1];
}

void date::PrintDate()
{
    cout << getDay() << "/" << getMonth() << "/" << getYear() << endl;
}
istream & operator>>(istream& input, date& d)
{
    string temp;
    int tempD, tempM, tempY;
    getline(input,temp,'/');
    if(temp.length() == 0)
    {
        tempD = 0;
    }
    else
    {
        tempD = stoi(temp);
    }
    getline(input,temp,'/');
    if(temp.length() == 0)
    {
        tempM = 0;
    }
    else
    {
        tempM = stoi(temp);
    }
    getline(input,temp,' ');
    if(temp.length() == 0)
    {
        tempY = 0;
    }
    else
    {
        tempY = stoi(temp);
    }
    d.SetDate(tempD,tempM,tempY);
    return input;
}

ostream & operator<<(ostream& os, const date& d)
{
    os << d.getDay() << "/" << d.getMonth() << "/" << d.getYear() << " ";
    return os;
}
