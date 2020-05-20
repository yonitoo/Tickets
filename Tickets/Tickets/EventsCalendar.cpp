#include "EventsCalendar.h"
#include <iterator>
#include <cassert>

void EventsCalendar::copy(const EventsCalendar& other)
{
    for(unsigned int i = 0 ; i < other.events.size() ; i++)
    {
        this->events.push_back(other.events[i]);
    }
}

void EventsCalendar::erase()
{
    this->events.clear();
}

EventsCalendar& EventsCalendar::removeEvent(const std::string name)
{
    for(unsigned int i = 0 ; i < events.size() ; i++)
    {
        if(this->events[i]->getName() == name)
        {
            this->events.erase(this->events.begin() + i);
        }
    }
    return *this;
}
EventsCalendar::EventsCalendar() : events()
{
}

EventsCalendar::EventsCalendar(const EventsCalendar& eventsCalendar)
{
    for(unsigned int i = 0 ; i < eventsCalendar.events.size() ; i++)
    {
        this->events.push_back(eventsCalendar.events[i]);
    }
}

EventsCalendar& EventsCalendar::operator=(const EventsCalendar& other)
{
    if(this!=&other)
    {
        erase();
        copy(other);
    }
    return *this;
}

EventsCalendar::~EventsCalendar()
{
    erase();
}

Event* EventsCalendar::getEvent(const unsigned int& index)
{
    return this->events[index];
}

EventsCalendar& EventsCalendar::addEvent(const Date& date, const Hall& hall, const std::string name)
{
    bool isFree = true;
    for(unsigned int i = 0 ; i < this->events.size() ; i++)
    {
        if(this->events[i]->getDate() == date &&
           this->events[i]->getHall().getNumber() == hall.getNumber())
        {
            isFree = false;
        }
    }

    if(isFree == false)
    {
        std::cout << "Veche ima predstavlenie za tazi data v zala nomer "
                  << hall.getNumber() << "!" << std::endl;
    }
    else
    {
        this->events.push_back(new Event(name, date, hall));
    }
    return *this;
}

unsigned int EventsCalendar::freeseats(const Date& date, const std::string name)
{
    for(unsigned int i = 0 ; i < this->events.size() ; i++)
    {
        if(this->events[i]->getName() == name && this->events[i]->getDate() == date)
        {
            return (this->events[i]->getHall().getCapacity()
                    - this->events[i]->getReservedAndBoughtTickets());
        }
    }
    std::cout<<"Predstavlenie s takova ime na tazi data ne sushtestvuva!"<<std::endl;
    return 0;
}

void EventsCalendar::book(const unsigned int row, const unsigned int seat,
                          const Date& date, const std::string name, const std::string note)
{
    for(unsigned int i = 0 ; i < this->events.size() ; i++)
    {
        if(this->events[i]->getName() == name && this->events[i]->getDate() == date)
        {
            assert(row < this->events[i]->getHall().getRows());
            assert(seat < this->events[i]->getHall().getSeats());
            if (this->events[i]->getTicket(row, seat)->getStatus() == 1 ||
                this->events[i]->getTicket(row, seat)->getStatus() == 2)
            {
                std::cout << "This ticket is already booked or sold!" << std::endl;
            }
            else
            {
                this->events[i]->setStatusAt(row, seat, 1);
                this->events[i]->setStatusAt(row, seat, 1);
            }
        }
    }
    std::cout << note << std::endl;
}

void EventsCalendar::unbook(const unsigned int row, const unsigned int seat,
                            const Date& date, const std::string name)
{
    for(unsigned int i = 0 ; i < this->events.size() ; i++)
    {
        if(this->events[i]->getName() == name && this->events[i]->getDate() == date 
            && this->events[i]->getTicket(row, seat)->getStatus() == 1)
        {
            (row < this->events[i]->getHall().getRows());
            assert(seat < this->events[i]->getHall().getSeats());
            this->events[i]->setStatusAt(row, seat, 0);
            this->events[i]->setStatusAt(row, seat, 0);
        }
        else
        {
            std::cout << "Biletut ne sushtestvuva ili ne e bil rezerviran!" << std::endl;
        }
    }
}

void EventsCalendar::buy(const unsigned int row, const unsigned int seat,
                         const Date& date, const std::string name)
{
    for(unsigned int i = 0 ; i < this->events.size() ; i++)
    {
        if(this->events[i]->getName() == name && this->events[i]->getDate() == date)
        {
            assert(row < this->events[i]->getHall().getRows());
            assert(seat < this->events[i]->getHall().getSeats());
            if (this->events[i]->getTicket(row, seat)->getStatus() == 2)
            {
                std::cout << "This ticket is already sold!" << std::endl;
            }
            else
            {
                this->events[i]->setStatusAt(row, seat, 2);
                this->events[i]->setStatusAt(row, seat, 2);
            }
        }
    }
}

void EventsCalendar::bookings(const Date& date, const std::string name) const
{
    int index = -1;
    for(unsigned int i = 0 ; i < this->events.size() ; i++)
    {
        if(this->events[i]->getName() == name && this->events[i]->getDate() == date)
        {
            index = i;
            break;
        }
    }

    if(index == -1)
    {
        return;
    }
    else
    {
        std::cout << "Bookings:" << std::endl;
        for(unsigned int i = 0 ; i < this->events[index]->getHall().getRows() ; i++)
        {
            for(unsigned int j = 0 ; j < this->events[index]->getHall().getRows() ; j++)
            {
                if(this->events[index]->getTicket(i, j)->getStatus() == 1)
                {
                    this->events[index]->getTicket(i, j)->print();
                }
            }
        }
    }
}

bool EventsCalendar::check(const std::string code)
{
    if(code.size() < 21)
    {
        std::cout << "Bilet s takuv kod ne sushtestvuva!";
        return false;
    }

    if((code[0] < '0' || code[0] > '9') ||
       (code[3] < '0' || code[3] > '9'))
    {
        std::cout << "Bilet s takuv kod ne sushtestvuva!";
        return false;
    }

    unsigned int day = (code[0] - '0')*10 + (code[1] - '0');

    if((code[2] < '0' || code[2] > '9') ||
       (code[3] < '0' || code[3] > '9'))
    {
        std::cout << "Bilet s takuv kod ne sushtestvuva!";
        return false;
    }
    unsigned int month = (code[2] - '0')*10 + (code[3] - '0');

    if((code[4] < '0' || code[4] > '9') ||
       (code[5] < '0' || code[5] > '9') ||
       (code[6] < '0' || code[6] > '9') ||
       (code[7] < '0' || code[7] > '9'))
    {
        std::cout << "Bilet s takuv kod ne sushtestvuva!";
        return false;
    }
    unsigned int year = (code[4] - '0')*1000 + (code[5] - '0')*100 +
                        (code[6] - '0')*10 + (code[7] - '0') ;
    if(code[8] != '|' || code[12] != '|' || code[16] != '|' || code[20] != '|')
    {
        std::cout << "Bilet s takuv kod ne sushtestvuva!";
        return false;
    }

    unsigned int hallNumRowSeat[3], j = 0;
    for(unsigned int i = 9 ; i < 20 ; i = i + 4)
    {
        if((code[i] < '0' || code[i] > '9') ||
           (code[i + 1] < '0' || code[i + 1] > '9') ||
           (code[i + 2] < '0' || code[i + 2] > '9'))
        {
            std::cout << "Bilet s takuv kod ne sushtestvuva!";
            return false;
        }
            hallNumRowSeat[j] =
            (code[i] - '0')*100 + (code[i + 1] - '0')*10 + (code[i + 2] - '0');
        j++;
    }
    unsigned int hallNumber = hallNumRowSeat[0];
    unsigned int row = hallNumRowSeat[1];
    unsigned int seat = hallNumRowSeat[2];

    std::string codeName;
    codeName = code.substr(21);

    for(unsigned int i = 0 ; i < this->events.size() ; i++)
    {
        if (this->events[i]->getDate().getDay() == day &&
            this->events[i]->getDate().getMonth() == month &&
            this->events[i]->getDate().getYear() == year &&
            this->events[i]->getHall().getNumber() == hallNumber &&
            this->events[i]->getHall().getRows() >= row &&
            this->events[i]->getHall().getSeats() >= seat &&
            this->events[i]->getTicket(row, seat)->getStatus() == 2 &&
            this->events[i]->getName() == codeName)
        {
            return true;
        }
    }

    std::cout << "Bilet s takuv kod ne sushtestvuva!";
    return false;
}
void EventsCalendar::report(const Hall& hall, const Date& from, const Date& to)
{
    assert(to >= from);
    if(hall.getNumber() == 0)
    {
        std::cout << "Informaciq za vsichki predstavleniq ot ";
        from.print();
        std::cout << " do ";
        to.print();
        std::cout << std::endl;

        for(unsigned int i = 0 ; i < this->events.size() ; i++)
        {
            if(this->events[i]->getDate() >= from &&
               to >= this->events[i]->getDate())
            {
                this->events[i]->print();
            }
        }
    }
    else
    {
        std::cout << "Informaciq za vsichki predstavleniq  v zala " << hall.getNumber() << " ot ";
        from.print();
        std::cout << " do ";
        to.print();
        std::cout << std::endl;

        for(unsigned int i = 0 ; i < this->events.size() ; i++)
        {
            if(this->events[i]->getHall().getNumber() == hall.getNumber() &&
               this->events[i]->getDate() >= from &&
               to >= this->events[i]->getDate())
            {
                this->events[i]->print();
            }
        }
    }
}

///nad 80% gledaemost predstavleniq
void EventsCalendar::printPopular() const
{
    for(unsigned int i = 0 ; i < this->events.size() ; i++)
    {
        if((double)((double)this->events[i]->getVisits()/
                    (double)this->events[i]->getHall().getCapacity()) > 0.8)
        {
            this->events[i]->print();
        }
    }
}

EventsCalendar& EventsCalendar::printUnpopular(const Date& from, const Date& to)
{
    assert(to >= from);
    for (unsigned int i = 0; i < this->events.size(); i++)
    {
        if (this->events[i]->getDate() >= from &&
            to >= this->events[i]->getDate())
        {
            if ((double)((double)this->events[i]->getVisits() /
                (double)this->events[i]->getHall().getCapacity()) < 0.1)
            {
                this->events[i]->print();
            }
        }
    }
    std::cout << "Jelaete li da premahnete nqkoe subitie ot kalendara? (da/ne)" << std::endl;
    char answer[3];
    std::string ans;
    do
    {
        std::cin.getline(answer, 3);
        ans = answer;
    } 
    while (ans != "da" && ans != "ne");
    if (ans == "da")
    {
        std::cout << "Posochete imeto na subitieto, koeto jelaete da iztriete:";
        char name[51];
        std::cin.getline(name, 51, '\n');
        std::string ans2str = name;
        this->removeEvent(name);
    }
    return *this;
}