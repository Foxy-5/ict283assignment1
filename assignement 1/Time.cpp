#include "Time.h"
#include <string>

Time::Time()
{
    hour = 0;
    minute = 0;
}

Time::Time(int h, int m)
{
    if(h >= 0 && h <= 23)
    {
        hour = h;
    }
    else
    {
        hour = 0;
    }
    if(m >= 0 && m <= 59)
    {
        minute = m;
    }
    else
    {
        minute = 0;
    }
}

void Time::SetHour(int h)
{
    if(h >= 0 && h <= 23)
    {
        hour = h;
    }
    else
    {
        hour = 0;
    }
}

void Time::SetMinute(int m)
{
    if(m >= 0 && m <= 59)
    {
        minute = m;
    }
    else
    {
        minute = 0;
    }
}

int Time::GetHour() const
{
    return hour;
}

int Time::GetMinute() const
{
    return minute;
}

istream & operator>>(istream& input, Time& t)
{
    string temp;
    int tempHour, tempMin;
    getline(input,temp,':');
    if(temp.length() == 0)
    {
        tempHour = 0;
    }
    else
    {
        tempHour = stoi(temp);
    }
    getline(input,temp,',');
    if(temp.length() == 0)
    {
        tempMin = 0;
    }
    else
    {
        tempMin = stoi(temp);
    }
    t.SetHour(tempHour);
    t.SetMinute(tempMin);
    return input;
}

ostream & operator<<(ostream& os, const Time& t)
{
    os << t.GetHour() << ":" << t.GetMinute() << " ";
    return os;
}
