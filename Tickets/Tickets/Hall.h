#ifndef HALL_H
#define HALL_H

#include <iostream>
#include <vector>

class Hall
{
    private:
        unsigned int number, rows, seats;

    public:
        Hall();
        Hall(unsigned int, unsigned int, unsigned int);
        Hall(const Hall&);
        Hall& operator=(const Hall&);

        unsigned int getNumber() const;
        unsigned int getRows() const;
        unsigned int getSeats() const;
        unsigned int getCapacity() const;

        void setNumber(unsigned int);
        void setRows(unsigned int);
        void setSeats(unsigned int);
};

#endif