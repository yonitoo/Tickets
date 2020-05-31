#ifndef EVENTSCALENDAR_H
#define EVENTSCALENDAR_H

#include "Event.h"
#include <vector>

class EventsCalendar
{
    private:
       std::vector<Event*> events;
       std::vector<Hall*> halls;

       void copy(const EventsCalendar&);
       EventsCalendar& removeEvent(const std::string);

    public:
        EventsCalendar();
        EventsCalendar(const EventsCalendar&);
        EventsCalendar& operator=(const EventsCalendar&);
        ~EventsCalendar();

        void erase();
        void addHall(Hall*);
        Hall* getHall(const unsigned int) const;
        unsigned int getHallsSize() const;
        Event* getEvent(const unsigned int&);

        EventsCalendar& addEvent(const Date&, Hall*, const std::string);
        unsigned int freeseats(const Date&, const std::string);
        void book(const unsigned int, const unsigned int, const Date&, const std::string, const std::string note = "");
        void unbook(const unsigned int, const unsigned int, const Date&, const std::string);
        void buy(const unsigned int, const unsigned int, const Date&, const std::string);
        void bookings(const Date& date = Date(0,0,0), const std::string name = "") const;
        bool check(const std::string);
        void report(const Date& from = Date(0, 0, 0), const Date& to = Date(31, 12, 9999), const Hall* hall = nullptr);
        void printPopular() const;
        EventsCalendar& printUnpopular(const Date& from = Date(0, 0, 0), const Date& to = Date(31, 12, 9999));
        
        void write(std::ostream&) const;
        bool read(std::istream&);
};

#endif
