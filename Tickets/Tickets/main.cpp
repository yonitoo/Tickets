#include<iostream>
#include<fstream>
#include "Hall.h"
#include "Ticket.h"
#include "Event.h"
#include "Date.h"
#include "EventsCalendar.h"

int main()
{
    Hall halls[5];
    halls[0].setNumber(1);
    halls[1].setNumber(2);
    halls[2].setNumber(3);
    halls[3].setNumber(4);
    halls[4].setNumber(5);

    halls[0].setRows(15);
    halls[1].setRows(12);
    halls[2].setRows(12);
    halls[3].setRows(8);
    halls[4].setRows(10);

    halls[0].setSeats(20);
    halls[1].setSeats(15);
    halls[2].setSeats(15);
    halls[3].setSeats(10);
    halls[4].setSeats(10);

    EventsCalendar eventim;
    Date date(12,5,2020);
    Date date2(15,5,2020);
    eventim.addEvent(date, halls[0], "Romeo i Julieta");
    std::cout<<"yo";
    eventim.addEvent(date2, halls[1], "Vuzvishenie");
    eventim.buy(5, 5, date, "Romeo i Julieta");
    eventim.buy(5, 4, date, "Romeo i Julieta");
    eventim.buy(5, 3, date, "Romeo i Julieta");
    eventim.buy(5, 2, date, "Romeo i Julieta");
    std::cout << std::boolalpha << eventim.check("12052020|001|005|005|Romeo i Julieta") << std::endl;
    eventim.getEvent(0)->print();
    return 0;
}
