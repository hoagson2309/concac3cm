#ifndef DEMO_WEEK_03_DATE_H
#define DEMO_WEEK_03_DATE_H

#include <ctime>
#include <string>

namespace bday_calendar {

class Date {
public:
    Date(); // default constructor
    Date(int year, int month, int day);
    Date(std::string date);

    // modifiers
    void year(int year);
    void month(int month);
    void day(int day);

    // accessors
    int year() const;
    int month() const;
    int day() const;

    std::string str() const;

private:
    std::time_t time_;
};

} // bday_calendar

#endif //DEMO_WEEK_03_DATE_H
