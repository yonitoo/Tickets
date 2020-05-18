#include "Date.h"
#include<iostream>
#include<cassert>

Date::Date() : day(0), month(0), year(5000)
{
}

Date::Date(unsigned int day, unsigned int month, unsigned int year)
                               : day(day), month(month), year(year)
{
}

Date& Date::operator=(const Date& other)
{
    if(this!=&other)
    {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
    }
    return *this;
}

bool Date::operator==(const Date& other)
{
    return (this->day == other.day && this->month == other.month && this->year == other.year);
}

bool Date::operator>=(const Date& other)
{
    if(this->year < other.year)
    {
        return false;
    }
    else if(this->year > other.year)
    {
        return true;
    }
    else
    {
        if(this->month < other.month)
        {
            return false;
        }
        else if(this->month > other.month)
        {
            return true;
        }
        else
        {
            if(this->day < other.day)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}

bool Date::isEndOfMonth() const
{
    if(this->month == 1 || this->month == 3
                        || this->month == 5
                        || this->month == 7
                        || this->month == 8
                        || this->month == 10
                        || this->month == 12)
    {
        return this->day == 31;
    }
    else if(this->month == 2)
    {
        if(this->year % 4 != 0 || (this->year%100 == 0 && this->year%400 != 0))
        {
            return this->day == 28;
        }
        else
        {
            return this->day == 29;
        }
    }
    else
    {
        return this->day == 30;
    }
}

Date& Date::operator++()
{

    if(this->isEndOfMonth())
    {
        if(this->month == 12)
        {
            this->month = 1;
            this->day = 1;
            this->year++;
        }
        else
        {
            this->day = 1;
            this->month++;
        }
    }
    else
    {
        this->day++;
    }
    return *this;
}

Date::~Date()
{
}

unsigned int Date::getDay() const
{
    return this->day;
}

unsigned int Date::getMonth() const
{
    return this->month;
}

unsigned int Date::getYear() const
{
    return this->year;
}

void Date::setDay(const unsigned int day)
{
    assert(day > 0);
    if(this->month == 1 || this->month == 3
                        || this->month == 5
                        || this->month == 7
                        || this->month == 8
                        || this->month == 10
                        || this->month == 12)
    {
        assert(day < 32);
    }
    else if(this->month == 2)
    {
        if(this->year % 4 != 0 || (this->year%100 == 0 && this->year%400 != 0))
        {
            assert(day < 29);
        }
        else
        {
            assert(day < 30);
        }
    }
    else
    {
        assert(day < 31);
    }
    this->day = day;
}
void Date::setMonth(const unsigned int month)
{
    assert(month < 13 && month > 0);
    this->month = month;
}
void Date::setYear(const unsigned int year)
{
    assert(year < 2030);
    this->year = year;
}

void Date::print() const
{
    std::cout << this->day
              << "/"
              << this->month
              << "/"
              << this->year
              << std::endl;
}

bool operator>=(const Date& first, const Date& second)
{
    if(first.year < second.year)
    {
        return false;
    }
    else if(first.year > second.year)
    {
        return true;
    }
    else
    {
        if(first.month < second.month)
        {
            return false;
        }
        else if(first.month > second.month)
        {
            return true;
        }
        else
        {
            if(first.day < second.day)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
    }
}