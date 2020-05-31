#include "EventsCalendar.h"
#include <iterator>
#include <cassert>

void EventsCalendar::copy(const EventsCalendar& other)
{
    for(unsigned int i = 0 ; i < other.events.size() ; i++)
    {
        this->events.push_back(other.events[i]);
    }

    for (unsigned int i = 0; i < other.halls.size(); i++)
    {
        this->halls.push_back(other.halls[i]);
    }
}

void EventsCalendar::erase()
{
    for (unsigned int i = 0; i < this->events.size(); i++)
    {
        delete this->events[i];
    }
    this->events.clear();
    this->halls.clear();
}

void EventsCalendar::addHall(Hall* hall)
{
    this->halls.push_back(hall);
}

Hall* EventsCalendar::getHall(const unsigned int index) const
{
    return this->halls[index];
}

unsigned int EventsCalendar::getHallsSize() const
{
    return this->halls.size();
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
EventsCalendar::EventsCalendar() : events(), halls()
{
}

EventsCalendar::EventsCalendar(const EventsCalendar& eventsCalendar)
{
    for(unsigned int i = 0 ; i < eventsCalendar.events.size() ; i++)
    {
        this->events.push_back(eventsCalendar.events[i]);
    }
    for (unsigned int i = 0; i < eventsCalendar.halls.size(); i++)
    {
        this->halls.push_back(eventsCalendar.halls[i]);
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

EventsCalendar& EventsCalendar::addEvent(const Date& date, Hall* hall, const std::string name)
{
    bool isFree = true;
    for(unsigned int i = 0 ; i < this->events.size() ; i++)
    {
        if(this->events[i]->getDate() == date &&
           this->events[i]->getHall()->getNumber() == hall->getNumber())
        {
            isFree = false;
        }
    }

    if(isFree == false)
    {
        std::cout << "Veche ima predstavlenie za tazi data v zala nomer "
                  << hall->getNumber() << "!" << std::endl;
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
            return (this->events[i]->getHall()->getCapacity()
                    - this->events[i]->getReservedAndSoldTickets());
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
            assert(row < this->events[i]->getHall()->getRows());
            assert(seat < this->events[i]->getHall()->getSeats());
            if (this->events[i]->getTicket(row, seat)->getStatus() == Status::RESERVED ||
                this->events[i]->getTicket(row, seat)->getStatus() == Status::SOLD)
            {
                std::cout << "This ticket is already booked or sold!" << std::endl;
            }
            else
            {
                this->events[i]->setStatusAt(row, seat, Status::RESERVED);
                this->events[i]->setStatusAt(row, seat, Status::RESERVED);
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
            && this->events[i]->getTicket(row, seat)->getStatus() == Status::RESERVED)
        {
            (row < this->events[i]->getHall()->getRows());
            assert(seat < this->events[i]->getHall()->getSeats());
            this->events[i]->setStatusAt(row, seat, Status::INSTOCK);
            this->events[i]->setStatusAt(row, seat, Status::INSTOCK);
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
            assert(row < this->events[i]->getHall()->getRows());
            assert(seat < this->events[i]->getHall()->getSeats());
            if (this->events[i]->getTicket(row, seat)->getStatus() == Status::SOLD)
            {
                std::cout << "This ticket is already sold!" << std::endl;
            }
            else
            {
                this->events[i]->setStatusAt(row, seat, Status::SOLD);
                this->events[i]->setStatusAt(row, seat, Status::SOLD);
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

    if (name == "")
    {
        if (date.getDay() == 0)
        {
            for (unsigned int i = 0; i < this->events.size(); i++)
            {
                this->events[i]->print();
            }
        }
        else
        {
            for (unsigned int i = 0; i < this->events.size(); i++)
            {
                if (this->events[i]->getDate() == date)
                {
                    this->events[i]->print();
                }
            }
        }
    }
    else
    {
        std::cout << "Bookings:" << std::endl;
        for(unsigned int i = 0 ; i < this->events[index]->getHall()->getRows() ; i++)
        {
            for(unsigned int j = 0 ; j < this->events[index]->getHall()->getRows() ; j++)
            {
                if(this->events[index]->getTicket(i, j)->getStatus() == Status::RESERVED)
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
            this->events[i]->getHall()->getNumber() == hallNumber &&
            this->events[i]->getHall()->getRows() >= row &&
            this->events[i]->getHall()->getSeats() >= seat &&
            this->events[i]->getTicket(row, seat)->getStatus() == Status::SOLD &&
            this->events[i]->getName() == codeName)
        {
            return true;
        }
    }

    std::cout << "Bilet s takuv kod ne sushtestvuva!";
    return false;
}
void EventsCalendar::report(const Date& from, const Date& to, const Hall* hall)
{
    assert(to >= from);
    if(hall == nullptr)
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
        std::cout << "Informaciq za vsichki predstavleniq  v zala " 
                  << hall->getNumber() << std::endl << " ot: ";
        from.print();
        std::cout << " do: ";
        to.print();
        std::cout << std::endl;

        for(unsigned int i = 0 ; i < this->events.size() ; i++)
        {
            if(this->events[i]->getHall()->getNumber() == hall->getNumber() &&
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
                    (double)this->events[i]->getHall()->getCapacity()) > 0.8)
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
                (double)this->events[i]->getHall()->getCapacity()) < 0.1)
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

void EventsCalendar::write(std::ostream& out) const
{
    ///broi zali
    ///nomer, redove, mesta
    ///broi subitiq
    ///ime, data, zala, bileti status, poseshteniq
    out << halls.size() << std::endl;
    for (unsigned int i = 0; i < this->halls.size(); i++)
    {
        out << this->halls[i]->getNumber() << std::endl;
        out << this->halls[i]->getRows() << std::endl;
        out << this->halls[i]->getSeats() << std::endl;
    }

    out << events.size() << std::endl;
    for (unsigned int i = 0; i < this->events.size(); i++)
    {
        out << this->events[i]->getName() << std::endl;
        out << this->events[i]->getDate().getDay() << std::endl;
        out << this->events[i]->getDate().getMonth() << std::endl;
        out << this->events[i]->getDate().getYear() << std::endl;
        out << this->events[i]->getHall()->getNumber() << std::endl;
        out << this->events[i]->getHall()->getRows() << std::endl;
        out << this->events[i]->getHall()->getSeats() << std::endl;
        Status status;
        for (unsigned int row = 0; row < this->events[i]->getHall()->getRows(); row++)
        {
            for (unsigned seat = 0; seat < this->events[i]->getHall()->getSeats(); seat++)
            {
                status = this->events[i]->getTicket(row, seat)->getStatus();
                if (status == Status::INSTOCK)
                {
                    out << 0 << std::endl;
                }
                else if(status == Status::RESERVED)
                {
                    out << 1 << std::endl;
                }
                else if(status == Status::SOLD)
                {
                    out << 2 << std::endl;
                }
            }
        }
        out << this->events[i]->getVisits() << std::endl;
    }
}

bool EventsCalendar::read(std::istream& in)
{
    if (!in)
    {
        return false;
    }

    unsigned int eventsNumber, day, month, year, number, rows, seats, ticketStatus, visits,
                 hallsSize, hallNumber, hallRows, hallSeats;
    std::string name;
    Event* event = nullptr;
    in >> hallsSize;
    for (unsigned int i = 0; i < hallsSize ; i++)
    {
        in >> hallNumber;
        in >> hallRows;
        in >> hallSeats;
        this->halls.push_back(new Hall(hallNumber, hallRows, hallSeats));
    }
    in >> eventsNumber;
    in.ignore(1024, '\n');
    for (unsigned int i = 0 ; i < eventsNumber; i++)
    {
        std::getline(in, name);
        in >> day;
        in >> month;
        in >> year;
        in >> number;
        in >> rows;
        in >> seats;
        for (unsigned int j = 0; j < this->halls.size(); j++)
        {
            if (this->halls[j]->getNumber() == number)
            {
                event = new Event(name, Date(day, month, year), this->halls[j]);
            }
        }

        for (unsigned int row = 0; row < rows; row++)
        {
            for (unsigned int seat = 0; seat < seats ; seat++)
            {
                in >> ticketStatus;
                Status status = static_cast<Status>(ticketStatus);
                event->setStatusAt(row, seat, status);
            }
        }
        in >> visits;
        event->setVisits(visits);
        this->events.push_back(event);
    }
    return true;
}