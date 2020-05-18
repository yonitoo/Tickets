#ifndef EVENT_H
#define EVENT_H

#include "Ticket.h"
#include <iostream>
#include <cassert>
#include <vector>

class Event
{
    private:
        std::string name;
        Date date;
        std::vector<std::vector<Ticket*>> tickets;
        Hall hall;
        unsigned int visits;

        void copy(const Event&);
        void erase();

    public:
        Event();
        Event(const std::string&, const Date&,
              const Hall&);
        Event& operator=(const Event&);
        ~Event();

        std::string getName() const;
        Date getDate() const;
        unsigned int getBoughtTickets() const;
        unsigned int getReservedAndBoughtTickets() const;
        Ticket* getTicket(unsigned int, unsigned int);
        Hall getHall() const;
        unsigned int getVisits() const;

        void setName(const std::string);
        void setDate(const Date&);
        void setStatusAt(unsigned int, unsigned int, unsigned int);
        void setHall(const Hall&);
        void setVisits(const unsigned int);

        void print() const;
};

#endif
