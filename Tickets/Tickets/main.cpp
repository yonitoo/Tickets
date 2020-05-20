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
    halls[2].setRows(3);
    halls[3].setRows(8);
    halls[4].setRows(10);

    halls[0].setSeats(20);
    halls[1].setSeats(15);
    halls[2].setSeats(3);
    halls[3].setSeats(10);
    halls[4].setSeats(10);

    EventsCalendar eventim;
    Date date(12,5,2020);
    Date date2(15,5,2020);
    eventim.addEvent(date, halls[0], "Romeo i Julieta");
    eventim.addEvent(date2, halls[1], "Vuzvishenie");
    eventim.buy(5, 5, date, "Romeo i Julieta");
    eventim.buy(5, 4, date, "Romeo i Julieta");
    eventim.buy(5, 3, date, "Romeo i Julieta");
    eventim.buy(5, 2, date, "Romeo i Julieta");
    std::cout << std::boolalpha << eventim.check("12052020|001|005|002|Romeo i Julieta") << std::endl;
    eventim.book(3, 7, date, "Romeo i Julieta");
    eventim.bookings(date, "Romeo i Julieta");
    eventim.buy(5, 5, date2, "Vuzvishenie");
    eventim.getEvent(1)->print();
    eventim.printUnpopular();
    eventim.addEvent(date, halls[2], "Dqdo vadi rqpa");
    eventim.buy(1, 1, date, "Dqdo vadi rqpa");
    eventim.buy(2, 1, date, "Dqdo vadi rqpa");
    eventim.buy(0, 1, date, "Dqdo vadi rqpa");
    eventim.buy(0, 0, date, "Dqdo vadi rqpa");
    eventim.buy(0, 2, date, "Dqdo vadi rqpa");
    eventim.buy(2, 2, date, "Dqdo vadi rqpa");
    eventim.buy(1, 2, date, "Dqdo vadi rqpa");
    eventim.buy(2, 0, date, "Dqdo vadi rqpa");
    eventim.printPopular();
    eventim.report(halls[0]);
    return 0;

    ///TODO test na report
    ///TODO moje bi popravka na default stoinostite za red i mesta
    ///TODO ICommand pattern
}