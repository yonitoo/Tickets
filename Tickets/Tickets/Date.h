#ifndef DATE_H
#define DATE_H

class Date
{
    private:
        unsigned int day, month, year;

    public:
        Date();
        Date(unsigned int, unsigned int, unsigned int);
        Date& operator=(const Date&);
        bool operator==(const Date&);
        bool operator>=(const Date&);
        Date& operator++();
        ~Date();

        unsigned int getDay() const;
        unsigned int getMonth() const;
        unsigned int getYear() const;

        void setDay(const unsigned int);
        void setMonth(const unsigned int);
        void setYear(const unsigned int);

        bool isEndOfMonth() const;
        void print() const;

        friend bool operator>=(const Date&, const Date&);
};

#endif
