#ifndef TICKET_H
#define TICKET_H

#include "Hall.h"
#include "Date.h"
#include <string>

class Ticket
{
    private:
        std::string code; ///eventName_Date_hallNumber_row_seat
        std::string eventName;
        Hall hall;
        Date date;
        unsigned int row, seat, status; /// = {0 = in stock,1 = reserved,2 = bought};

        void copy(const Ticket&);

    public:
        Ticket();
        Ticket(const Hall&, const Date&, unsigned int, unsigned int, unsigned int);
        Ticket& operator=(const Ticket&);

        std::string getCode() const;
        std::string getEventName() const;
        Hall getHall() const;
        Date getDate() const;
        unsigned int getRow() const;
        unsigned int getSeat() const;
        unsigned int getStatus() const;

        void setCode(const std::string);
        void setEventName(const std::string);
        void setHall(const Hall&);
        void setDate(const Date&);
        void setRow(unsigned int);
        void setSeat(unsigned int);
        void setStatus(unsigned int);

        void print() const;
};

#endif
