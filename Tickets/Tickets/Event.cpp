#include "Event.h"

void Event::copy(const Event& other)
{
    this->name = other.name;
    this->date = other.date;
    this->hall = other.hall;
    //this->tickets.push_back(std::vector<Ticket*>{new Ticket[this->hall.getRows()]});
    for(unsigned int i = 0 ; i < this->hall.getRows() ; i++)
    {
        this->tickets.push_back(std::vector<Ticket*>());
    }

    for(unsigned int i = 0 ; i < this->hall.getRows() ; i++)
    {
        for(unsigned int j = 0 ; j < this->hall.getSeats() ; j++)
        {
            this->tickets[i].push_back(other.tickets[i][j]); ///TODO
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
                 hall(Hall()), visits(0)
{
}

Event::Event(const std::string& name, const Date& date, const Hall& hall) :
                  date(date), hall(hall), visits(0)
{
    this->name = name;
    /*this->tickets = new Ticket*[this->hall.getRows()];
    for(unsigned int i = 0 ; i < this->hall.getRows() ; i++)
    {
        this->tickets[i] = new Ticket[this->hall.getSeats()];
    }*/

    for(unsigned int i = 0 ; i < this->hall.getRows() ; i++)
    {
        this->tickets.push_back(std::vector<Ticket*>());
        for(unsigned int j = 0 ; j < this->hall.getSeats() ; j++)
        {
            this->tickets[i].push_back(new Ticket(this->hall, this->date, i, j, 0));
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

unsigned int Event::getBoughtTickets() const
{
    unsigned int counter = 0;
    for(unsigned int i = 0 ; i < this->hall.getRows() ; i++)
    {
        for(unsigned int j = 0 ; j < this->hall.getSeats() ; j++)
        {///2 = bought
            if(this->tickets[i][j]->getStatus() == 2)
            {
                counter++;
            }
        }
    }
    return counter;
}

unsigned int Event::getReservedAndBoughtTickets() const
{
    unsigned int counter = 0;
    for(unsigned int i = 0 ; i < this->hall.getRows() ; i++)
    {
        for(unsigned int j = 0 ; j < this->hall.getSeats() ; j++)
        {///1 = reserved | 2 = bought ENUM
            if(this->tickets[i][j]->getStatus() == 1 || this->tickets[i][j]->getStatus() == 2)
            {
                counter++;
            }
        }
    }
    return counter;
}

Ticket* Event::getTicket(unsigned int row, unsigned int seat)
{
    assert(row < this->hall.getRows() && seat < this->hall.getSeats());
    return this->tickets[row][seat];
}

Hall Event::getHall() const
{
    return this->hall;
}

unsigned int Event::getVisits() const
{
    return this->getBoughtTickets();
}

void Event::setName(const std::string name)
{
    this->name = name;
}

void Event::setDate(const Date& date)
{
    this->date = date;
}

void Event::setStatusAt(unsigned int row, unsigned int seat, unsigned int status)
{
    assert(row > 0 && seat > 0 && row < this->hall.getRows() && seat < this->hall.getSeats());
    this->tickets[row][seat]->setStatus(status);
}

void Event::setHall(const Hall& hall)
{
    this->hall = hall;
}
///nz
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
    std::cout << std::endl
              << "Zala nomer: "
              << this->hall.getNumber() << std::endl
              << "Prodadeni bileti: "
              << this->getBoughtTickets()
              << " ot obshto "
              << this->hall.getCapacity() <<std::endl;
}
