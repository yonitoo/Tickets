#ifndef TICKET_H
#define TICKET_H

#include "Hall.h"
#include "Date.h"
#include "Status.h"
#include <string>

class Ticket
{
    private:
        std::string code;
        std::string eventName;
        const Hall* hall;
        Date date;
        unsigned int row, seat;
        Status status; /// = {0 = in stock,1 = reserved,2 = bought};

        void copy(const Ticket&);

    public:
        Ticket();
        Ticket(const Hall*, const std::string&, const Date&, unsigned int, unsigned int, const Status&);
        Ticket& operator=(const Ticket&);

        std::string getCode() const;
        std::string getEventName() const;
        const Hall* getHall() const;
        Date getDate() const;
        const unsigned int getRow() const;
        const unsigned int getSeat() const;
        Status getStatus() const;

        void setCode(const std::string);
        void setEventName(const std::string);
        void setHall(const Hall*);
        void setDate(const Date&);
        void setRow(unsigned int);
        void setSeat(unsigned int);
        void setStatus(const Status&);

        void print() const;
};

#endif
