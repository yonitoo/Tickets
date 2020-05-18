#ifndef EVENTSCALENDAR_H
#define EVENTSCALENDAR_H

#include "Event.h"
#include <vector>

class EventsCalendar
{
    private:
       std::vector<Event*> events;

       void copy(const EventsCalendar&);
       void erase();
       EventsCalendar& removeEvent(const std::string);

    public:
        EventsCalendar();
        EventsCalendar(const EventsCalendar&);
        EventsCalendar& operator=(const EventsCalendar&);
        ~EventsCalendar();

        Event* getEvent(const unsigned int&);

        EventsCalendar& addEvent(const Date&, const Hall&, const std::string);
        unsigned int freeseats(const Date&, const std::string);
        void book(const unsigned int, const unsigned int, const Date&, const std::string, const std::string);
        void unbook(const unsigned int, const unsigned int, const Date&, const std::string);
        void buy(const unsigned int, const unsigned int, const Date&, const std::string);
        void bookings(const Date& date = Date(0,0,0), const std::string name = nullptr) const;
        bool check(const std::string);
        void report(const Date&, const Date&, const Hall& hall = Hall());
        void printPopular() const;
        //Event* printUnpopular(const Date&, const Date&);

};

#endif
