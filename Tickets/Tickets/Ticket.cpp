#include <cstring>
#include <cassert>
#include <iostream>
#include "Ticket.h"
#include "Hall.h"
#include "Date.h"

void Ticket::copy(const Ticket& other)
{
    this->code = other.code;
    this->eventName = eventName;
    this->row = other.row;
    this->seat = other.seat;
    this->status = other.status;
}

Ticket::Ticket() : code("Default"), eventName(""), hall(nullptr), date(Date()),
                   row(0), seat(0), status(Status::INSTOCK)
{
}

Ticket::Ticket(const Hall* hall, const std::string& eventName, const Date& date, unsigned int row,
               unsigned int seat, const Status& status) :
               row(row), seat(seat), status(Status::INSTOCK)
{
    assert(row < hall->getRows() && seat < hall->getSeats());
    this->hall = hall;
    this->date = date;
    char codeX[21];
    codeX[0] = '0' + this->date.getDay() / 10;
    codeX[1] = '0' + this->date.getDay() % 10;

    codeX[2] = '0' + this->date.getMonth() / 10;
    codeX[3] = '0' + this->date.getMonth() % 10;

    codeX[4] = '0' + this->date.getYear() / 1000;
    codeX[5] = '0' + (this->date.getYear() / 100) % 10;
    codeX[6] = '0' + (this->date.getYear() / 10) % 10;
    codeX[7] = '0' + this->date.getYear() % 10;

    codeX[8] = '|';

    codeX[9] = '0' + this->hall->getNumber() / 100;
    codeX[10] = '0' + (this->hall->getNumber() / 10) % 10;
    codeX[11] = '0' + this->hall->getNumber() % 10;

    codeX[12] = '|';

    codeX[13] = '0' + this->row / 100;
    codeX[14] = '0' + (this->row / 10) % 10;
    codeX[15] = '0' + this->row % 10;

    codeX[16] = '|';

    codeX[17] = '0' + this->seat / 100;
    codeX[18] = '0' + (this->seat / 10) % 10;
    codeX[19] = '0' + this->seat % 10;

    codeX[20] = '|';

    this->eventName = eventName;

    this->code = codeX;
    this->code += this->eventName;
}

Ticket& Ticket::operator=(const Ticket& other)
{
    if(this!=&other)
    {
        copy(other);
    }
    return *this;
}

std::string Ticket::getCode() const
{
    return this->code;
}

std::string Ticket::getEventName() const
{
    return this->eventName;
}

const Hall* Ticket::getHall() const
{
    return this->hall;
}

Date Ticket::getDate() const
{
    return this->date;
}

const unsigned int Ticket::getRow() const
{
    return this->row;
}

const unsigned int Ticket::getSeat() const
{
    return this->seat;
}

Status Ticket::getStatus() const
{
    return this->status;
}

void Ticket::setCode(const std::string code)
{
    this->code = code;
}

void Ticket::setEventName(const std::string eventName)
{
    this->eventName = eventName;
}

void Ticket::setHall(const Hall* hall)
{
    this->hall = hall;
}

void Ticket::setDate(const Date& date)
{
    this->date = date;
}

void Ticket::setRow(unsigned int row)
{
    this->row = row;
}

void Ticket::setSeat(unsigned int seat)
{
    this->seat = seat;
}

void Ticket::setStatus(const Status& status)
{
    this->status = status;
}

void Ticket::print() const
{
    std::cout << "Bilet za predstavlenie: "
              << this->eventName << std::endl
              << "data: ";
    this->date.print();
    std::cout << "zala: "
              << this->hall->getNumber() << std::endl
              << "red: "
              << this->row << std::endl
              << "mqsto: "
              << this->seat << std::endl;
}