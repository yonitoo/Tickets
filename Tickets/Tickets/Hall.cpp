#include "Hall.h"
#include <cassert>

Hall::Hall() : number(0), rows(0), seats(0)
{
}

Hall::Hall(unsigned int number, unsigned int rows, unsigned int seats) 
            : number(number), rows(rows), seats(seats)
{
}

Hall::Hall(const Hall& other)
{
    this->number = other.number;
    this->rows = other.rows;
    this->seats = other.seats;
}

Hall& Hall::operator=(const Hall& other)
{
    if(this!=&other)
    {
        this->number = other.number;
        this->rows = other.rows;
        this->seats = other.seats;
    }
    return *this;
}

unsigned int Hall::getNumber() const
{
    return this->number;
}

unsigned int Hall::getRows() const
{
    return this->rows;
}

unsigned int Hall::getSeats() const
{
    return this->seats;
}

unsigned int Hall::getCapacity() const
{
    return this->rows * this->seats;
}

void Hall::setNumber(unsigned int number)
{
    assert(number > 0 && number < 1000);
    this->number = number;
}

void Hall::setRows(unsigned int rows)
{
    assert(rows > 0 && rows < 1000);
    this->rows = rows;
}

void Hall::setSeats(unsigned int seats)
{
    assert(seats > 0 && rows < 1000);
    this->seats = seats;
}