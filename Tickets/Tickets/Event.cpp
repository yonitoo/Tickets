#include "Event.h"

void Event::copy(const Event& other)
{
    this->name = other.name;
    this->date = other.date;
    this->hall = other.hall;
    
    for(unsigned int i = 0 ; i < this->hall->getRows() ; i++)
    {
        this->tickets.push_back(std::vector<Ticket*>());
    }

    for(unsigned int i = 0 ; i < this->hall->getRows() ; i++)
    {
        for(unsigned int j = 0 ; j < this->hall->getSeats() ; j++)
        {
            this->tickets[i].push_back(other.tickets[i][j]);
        }
    }
    this->visits = other.visits;
}

void Event::erase()
{
    for(unsigned int i = 0 ; i < this->tickets.size() ; i++)
    {
        this->tickets[i].clear();
    }
    this->tickets.clear();///TODO
}

Event::Event() : name(""), date(Date()), tickets(),
                 hall(nullptr), visits(0)
{
}

Event::Event(const std::string& name, const Date& date, const Hall* hall) :
                  date(date), hall(hall), visits(0)
{
    this->name = name;
    for(unsigned int i = 0 ; i < this->hall->getRows() ; i++)
    {
        this->tickets.push_back(std::vector<Ticket*>());
        for(unsigned int j = 0 ; j < this->hall->getSeats() ; j++)
        {
            this->tickets[i].push_back(new Ticket(this->hall, this->name, this->date, i, j, Status::INSTOCK));
        }
    }
}

Event& Event::operator=(const Event& other)
{
    if(this!=&other)
    {
        erase();
        copy(other);
    }
    return *this;
}

Event::~Event()
{
    erase();
}

std::string Event::getName() const
{
    return this->name;
}

Date Event::getDate() const
{
    return this->date;
}

unsigned int Event::getSoldTickets() const
{
    unsigned int counter = 0;
    for(unsigned int i = 0 ; i < this->hall->getRows() ; i++)
    {
        for(unsigned int j = 0 ; j < this->hall->getSeats() ; j++)
        {
            if(this->tickets[i][j]->getStatus() == Status::SOLD)
            {
                counter++;
            }
        }
    }
    return counter;
}

unsigned int Event::getReservedAndSoldTickets() const
{
    unsigned int counter = 0;
    for(unsigned int i = 0 ; i < this->hall->getRows() ; i++)
    {
        for(unsigned int j = 0 ; j < this->hall->getSeats() ; j++)
        {
            if(this->tickets[i][j]->getStatus() == Status::RESERVED ||
                this->tickets[i][j]->getStatus() == Status::SOLD)
            {
                counter++;
            }
        }
    }
    return counter;
}

Ticket* Event::getTicket(unsigned int row, unsigned int seat) const
{
    assert(row < this->hall->getRows() && seat < this->hall->getSeats());
    return this->tickets[row][seat];
}

const Hall* Event::getHall() const
{
    return this->hall;
}

unsigned int Event::getVisits() const
{
    return this->getSoldTickets();
}

void Event::setName(const std::string name)
{
    this->name = name;
}

void Event::setDate(const Date& date)
{
    this->date = date;
}

void Event::setStatusAt(unsigned int row, unsigned int seat, const Status& status)
{
    assert(row < this->hall->getRows() && seat < this->hall->getSeats());
    this->tickets[row][seat]->setStatus(status);
}

void Event::setHall(const Hall* hall)
{
    this->hall = hall;
}

void Event::setVisits(const unsigned int visits)
{
    this->visits = visits;
}

void Event::print() const
{
    std::cout<< "---------------------------------" << std::endl;
    std::cout << "Ime na predstavlenieto: "
              << this->name << std::endl
              << "Data: ";
    this->date.print();
    std::cout << "Zala nomer: "
              << this->hall->getNumber() << std::endl
              << "Prodadeni bileti: "
              << this->getSoldTickets()
              << " ot obshto "
              << this->hall->getCapacity() <<std::endl;
}