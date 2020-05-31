#include<iostream>
#include<fstream>
#include "Hall.h"
#include "Ticket.h"
#include "Event.h"
#include "Date.h"
#include "EventsCalendar.h"
#include "Helper.h"

int main()
{
    EventsCalendar eventsCalendar;

    std::string command;
    std::fstream currentFile;
    std::string currentFileName;
    std::string currentstring;
    std::pair<bool, std::string> isOpen = { false, "" };
    while (std::getline(std::cin, command))
    {
        std::vector<std::string> words = splitLine(command);
        //open
        if (words.size() >= 1 && words[0] == "open")
        {
            if (words.size() > 2 || isOpen.first == true)
            {
                continue;
            }
            currentFileName = words[1];
            currentFile.open(currentFileName, std::fstream::in);
            currentFile.seekg(0, currentFile.beg);
            isOpen.first = true;
            isOpen.second = currentFileName;
            if (eventsCalendar.read(currentFile))
            {
                std::cout << "Successfully opened " << currentFileName << std::endl;
            }
            else
            {
                std::cout << "Reading failed!" << std::endl;
            }
        }
        //close
        else if (words.size() == 1 && words[0] == "close")
        {
            if (isOpen.first == false)
            {
                continue;
            }
            isOpen.first = false;
            currentFile.close();
            eventsCalendar.erase();
            std::cout << "Successfully closed " << currentFileName << std::endl;
        }
        //save
        else if (words.size() == 1 && words[0] == "save")
        {
            if (!isOpen.first)
            {
                continue;
            }
            currentFile.open(currentFileName, std::fstream::out);
            eventsCalendar.write(currentFile);
            currentFile.close();
            std::cout << "Successfully saved " << currentFileName << std::endl;
        }
        //save as
        else if (words.size() >= 2 && words[0] == "save" && words[1] == "as")
        {
            if (words.size() > 3)
            {
                continue;
            }
            std::fstream in;
            in.open(words[2], std::fstream::out);
            in.seekg(0, in.beg);
            eventsCalendar.write(in);
            in.close();
            std::cout << "Successfully saved as " << words[2] << std::endl;
        }
        //help
        else if (words.size() == 1 && words[0] == "help")
        {
            std::cout << "The following commands are supported :" << std::endl;
            std::cout << "open <file>                              opens <file>" << std::endl;
            std::cout << "close                                    closes currently opened file" << std::endl;
            std::cout << "save <file>                              saves the currently open file" << std::endl;
            std::cout << "save as <file>                           saves the currently open file in <file>" << std::endl;
            std::cout << "help                                     prints this information" << std::endl;
            std::cout << "addevent <date> <hall> <name>            adds event on <date> in <hall> called <name>" << std::endl;
            std::cout << "freeseats <date> <name>                  returns the number of free seats for the event on <date> called <name>" << std::endl;
            std::cout << "book <row> <seat> <date> <name> <note>   books a ticket" << std::endl;
            std::cout << "unbook <row> <seat> <date> <name> <note> unbooks a ticket" << std::endl;
            std::cout << "buy <row> <seat> <date> <name> <note>    buys a ticket" << std::endl;
            std::cout << "bookings[<date>][<name>]                 shows bookings on [<date>] for event called [<name>]" << std::endl;
            std::cout << "report <from> <to> [<hall>]              reports the events between <from> and <to> in [<hall>]" << std::endl;
            std::cout << "print popular                            prints unpopular events with more than 80% attendancy" << std::endl;
            std::cout << "print unpopular                          prints unpopular events with less than 10% attendancy" << std::endl;
            std::cout << "exit                                     exits the program" << std::endl;
        }
        //exit
        else if (words.size() == 1 && words[0] == "exit")
        {
            std::cout << "Exiting the program..." << std::endl;
            return 0;
        }
        else if (words.size() == 6 && words[0] == "addevent")
        {
            //addevent <date> <hall> <name>
            unsigned int day = std::stoi(words[1]);
            unsigned int month = std::stoi(words[2]);
            unsigned int year = std::stoi(words[3]);
            unsigned int hallNumber = std::stoi(words[4]);
            Hall* hall = new Hall;
            for (unsigned int i = 0; i < eventsCalendar.getHallsSize(); i++)
            {
                if (hallNumber == eventsCalendar.getHall(i)->getNumber())
                {
                    hall = eventsCalendar.getHall(i);
                }
            }
            eventsCalendar.addEvent(Date(day, month, year), hall, words[5]);
        }
        else if (words.size() >= 4 && words[0] == "freeseats")
        {
            //freeseats <date> <name>
            unsigned int day = std::stoi(words[1]);
            unsigned int month = std::stoi(words[2]);
            unsigned int year = std::stoi(words[3]);
            std::string eventName;
            for (unsigned int i = 4; i < words.size(); i++)
            {
                eventName += words[i];
                if (i != words.size() - 1)
                {
                    eventName += ' ';
                }
            }
            std::cout << eventsCalendar.freeseats(Date(day, month, year), eventName) << std::endl;
        }
        else if (words.size() >= 7 && words[0] == "book")
        {
            //book <row> <seat> <date> <name> <note>
            unsigned int row = std::stoi(words[1]);
            unsigned int seat = std::stoi(words[2]);
            unsigned int day = std::stoi(words[3]);
            unsigned int month = std::stoi(words[4]);
            unsigned int year = std::stoi(words[5]);
            std::string eventName;
            for (unsigned int i = 6; i < words.size() - 1; i++)
            {
                eventName += words[i];
                if (i != words.size() - 2)
                {
                    eventName += ' ';
                }
            }
            eventsCalendar.book(row, seat, Date(day, month, year), eventName, words[words.size() - 1]);
        }
        else if (words.size() >= 6 && words[0] == "unbook")
        {
            //unbook <row> <seat> <date> <name>
            unsigned int row = std::stoi(words[1]);
            unsigned int seat = std::stoi(words[2]);
            unsigned int day = std::stoi(words[3]);
            unsigned int month = std::stoi(words[4]);
            unsigned int year = std::stoi(words[5]);
            std::string eventName;
            for (unsigned int i = 6; i < words.size() - 1; i++)
            {
                eventName += words[i];
                if (i != words.size() - 2)
                {
                    eventName += ' ';
                }
            }
            eventsCalendar.unbook(row, seat, Date(day, month, year), eventName);
        }
        else if (words.size() >= 6 && words[0] == "buy")
        {
            //buy <row> <seat> <date> <name>
            unsigned int row = std::stoi(words[1]);
            unsigned int seat = std::stoi(words[2]);
            unsigned int day = std::stoi(words[3]);
            unsigned int month = std::stoi(words[4]);
            unsigned int year = std::stoi(words[5]);
            std::string eventName;
            for (unsigned int i = 6; i < words.size() - 1; i++)
            {
                eventName += words[i];
                if (i != words.size() - 2)
                {
                    eventName += ' ';
                }
            }
            eventsCalendar.buy(row, seat, Date(day, month, year), eventName);
        }
        else if ((words.size() >= 1 || words.size() >= 4) && words[0] == "bookings")
        {
            //bookings[<date>][<name>]
            if (words.size() == 1)
            {
                eventsCalendar.bookings();
            }
            else if (words.size() == 4)
            {
                unsigned int day = std::stoi(words[1]);
                unsigned int month = std::stoi(words[2]);
                unsigned int year = std::stoi(words[3]);
                eventsCalendar.bookings(Date(day, month, year));
            }
            else if (words.size() >= 5)
            {
                unsigned int day = std::stoi(words[1]);
                unsigned int month = std::stoi(words[2]);
                unsigned int year = std::stoi(words[3]);
                std::string eventName;
                for (unsigned int i = 4; i < words.size(); i++)
                {
                    eventName += words[i];
                    if (i != words.size() - 1)
                    {
                        eventName += ' ';
                    }
                }
                eventsCalendar.bookings(Date(day, month, year), eventName);
            }
        }
        else if (words.size() >= 2 && words[0] == "check")
        {
            std::string code;
            for (unsigned int i = 0; i < words.size(); i++)
            {
                code += words[i];
                if (i != words.size() - 1)
                {
                    code += ' ';
                }
            }
            eventsCalendar.check(code);
        }
        else if ((words.size() == 7 || words.size() == 8) && words[0] == "report")
        {
            if (words.size() == 7)
            {
                unsigned int fromDay = std::stoi(words[1]);
                unsigned int fromMonth = std::stoi(words[2]);
                unsigned int fromYear = std::stoi(words[3]);
                unsigned int toDay = std::stoi(words[4]);
                unsigned int toMonth = std::stoi(words[5]);
                unsigned int toYear = std::stoi(words[6]);
                eventsCalendar.report(Date(fromDay, fromMonth, fromYear), Date(toDay, toMonth, toYear));
            }
            else
            {
                unsigned int fromDay = std::stoi(words[1]);
                unsigned int fromMonth = std::stoi(words[2]);
                unsigned int fromYear = std::stoi(words[3]);
                unsigned int toDay = std::stoi(words[4]);
                unsigned int toMonth = std::stoi(words[5]);
                unsigned int toYear = std::stoi(words[6]);
                unsigned int hallNumber = std::stoi(words[7]);
                Hall* hall = new Hall;
                for (unsigned int i = 0; i < eventsCalendar.getHallsSize(); i++)
                {
                    if (hallNumber == eventsCalendar.getHall(i)->getNumber())
                    {
                        hall = eventsCalendar.getHall(i);
                    }
                }
                eventsCalendar.report(Date(fromDay, fromMonth, fromYear), Date(toDay, toMonth, toYear), hall);
            }
        }
        else if (words.size() == 2 && words[0] == "print" && words[1] == "popular")
        {
            eventsCalendar.printPopular();
        }
        else if (words.size() == 2 && words[0] == "print" && words[1] == "unpopular")
        {
            eventsCalendar.printUnpopular();
        }
    }
    return 0;

    //Hall halls[5];
    //halls[0].setNumber(1);
    //halls[1].setNumber(2);
    //halls[2].setNumber(3);
    //halls[3].setNumber(4);
    //halls[4].setNumber(5);

    //halls[0].setRows(15);
    //halls[1].setRows(12);
    //halls[2].setRows(3);
    //halls[3].setRows(8);
    //halls[4].setRows(10);

    //halls[0].setSeats(20);
    //halls[1].setSeats(15);
    //halls[2].setSeats(3);
    //halls[3].setSeats(10);
    //halls[4].setSeats(10);

    //EventsCalendar eventim;
    //for (unsigned int i = 0; i < 5; i++)
    //{
    //    eventim.addHall(&halls[i]);
    //}

    //Date date(12,5,2020);
    //Date date2(15,5,2020);
    //eventim.addEvent(date, eventim.getHall(0), "Romeo i Julieta");
    //eventim.addEvent(date2, eventim.getHall(1), "Vuzvishenie");
    //eventim.buy(5, 5, date, "Romeo i Julieta");
    //eventim.buy(5, 4, date, "Romeo i Julieta");
    //eventim.buy(5, 3, date, "Romeo i Julieta");
    //eventim.buy(5, 2, date, "Romeo i Julieta");
    //std::cout << std::boolalpha << eventim.check("12052020|001|005|002|Romeo i Julieta") << std::endl;
    //eventim.book(3, 7, date, "Romeo i Julieta");
    //eventim.bookings(date, "Romeo i Julieta");
    //eventim.buy(5, 5, date2, "Vuzvishenie");
    //eventim.getEvent(1)->print();
    //eventim.printUnpopular();
    //eventim.addEvent(date, eventim.getHall(2), "Dqdo vadi rqpa");
    //eventim.buy(1, 1, date, "Dqdo vadi rqpa");
    //eventim.buy(2, 1, date, "Dqdo vadi rqpa");
    //eventim.buy(0, 1, date, "Dqdo vadi rqpa");
    //eventim.buy(0, 0, date, "Dqdo vadi rqpa");
    //eventim.buy(0, 2, date, "Dqdo vadi rqpa");
    //eventim.buy(2, 2, date, "Dqdo vadi rqpa");
    //eventim.buy(1, 2, date, "Dqdo vadi rqpa");
    //eventim.buy(2, 0, date, "Dqdo vadi rqpa");
    //eventim.printPopular();
    //eventim.report(halls[0]);
    //std::ofstream out;
    //out.open("EventsCalendar.txt", std::ios::out | std::ios::trunc);
    //eventim.write(out);
    //out.close();
    //return 0;

    ///TODO moje bi popravka na default stoinostite za red i mesta
    ///TODO ICommand pattern
    ///read i write vuv file

    /*
    std::ofstream outputFile("Players.bin", std::ios::out | std::ios::binary | std::ios::trunc);

    if (!outputFile.is_open())
    {
        std::cout << "The output file Players.bin cannot be opened!" << std::endl;
        return false;
    }

    outputFile.write(reinterpret_cast<const char*>(&playersCount), sizeof(unsigned int));

    if (existenceIndex != -1)
    {
        for (unsigned int i = 0; i < playersCount; i++)
        {
            if (i != existenceIndex)
            {
                p[i].storeInBin(outputFile);
            }
            else
            {
                currentPlayer.storeInBin(outputFile);
            }
        }
    }
    else
    {
        for (unsigned int i = 0; i < playersCount - 1; i++)
        {
            p[i].storeInBin(outputFile);
        }
        currentPlayer.storeInBin(outputFile);
    }

    if (outputFile.good())
    {
        std::cout << "All changes are saved successfully in the file!" << std::endl;
    }
    outputFile.close();*/
}