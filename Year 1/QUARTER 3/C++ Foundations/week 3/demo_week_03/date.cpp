#include "date.h"
#include <stdexcept>
#include "utils.h"
#include <sstream>

bday_calendar::Date::Date(std::string date)
{
//    "yyyy-mm-dd"
    std::istringstream iss{date};
    char del{};
    int year, month, day;
    if (iss >> year >> del >> month >> del >> day)
    {
        // no validation of the date here, a bit bad
        std::tm time
        {
            .tm_mday = day,
            .tm_mon = month - 1,
            .tm_year = year - 1900,
            .tm_isdst = -1
        };

        time_ = std::mktime(&time);
    }
}

bday_calendar::Date::Date() : // initilialize with now
    time_{ std::time( nullptr ) }
{}

bday_calendar::Date::Date(int year, int month, int day)
{
    if (year  < 0)
    {
        throw std::invalid_argument{"`year` must be positive."};
    }

    if (month < 1 || month > 12)
    {
        throw std::invalid_argument{"`month` must be between 1 and 12."};
    }

    if (month == 2 && !is_leap_year(year) && day == 29)
    {
        // special case - we treat setting 29 for February in a non-leap year as a logic error, just for fun;)
        throw std::logic_error{"February is a short month this year."};
    }

    if (day < 1 || day > days_in_month(year, month) )
    {
        throw std::invalid_argument{std::string{"`day` is wrong, should be at least 1 and less than: " + std::to_string(days_in_month(year, month))}};
    }


    std::tm time{ .tm_mday = day,
                  .tm_mon = month - 1,
                  .tm_year = year - 1900,
                  .tm_isdst = -1
    };

    time_ = std::mktime(&time);
}

void bday_calendar::Date::year(int year) {
    if (year  < 0)
    {
        throw std::invalid_argument{"`year` must be positive"};
    }
    std::tm local_time = *std::localtime(&time_);
    local_time.tm_year = year - 1900;
    time_ = std::mktime(&local_time);
}

void bday_calendar::Date::month(int month) {
    if (month < 1 || month > 12)
    {
        throw std::invalid_argument{"`month` must be between 1 and 12."};
    }
    auto local_time = *std::localtime(&time_);
    local_time.tm_mon = month - 1;
    // Notice it might be illegal in some circumstances, e.g. if the previous date was 2024-03-31 and we set month to 2
    time_ = std::mktime(&local_time);
}

void bday_calendar::Date::day(int day) {

    auto local_time = *std::localtime(&time_);
    auto year = local_time.tm_year + 1900;
    auto month = local_time.tm_mon + 1;

    if (day < 1 || day > days_in_month(year, month) )
    {
        throw std::invalid_argument{std::string{"`day` is wrong, should be at least 1 and less than: " + std::to_string(days_in_month(year, month))}};
    }
    local_time.tm_mday = day;
    time_ = std::mktime(&local_time);
}

int bday_calendar::Date::year() const {
    std::tm local_time = *std::localtime(&time_);
    return local_time.tm_year + 1900;
}

int bday_calendar::Date::month() const {
    std::tm local_time = *std::localtime(&time_);
    return local_time.tm_mon + 1;
}

int bday_calendar::Date::day() const {
    return std::localtime(&time_)->tm_mday;
}

std::string bday_calendar::Date::str() const {
    char buffer[64] {};
    std::strftime(buffer, sizeof(buffer), "%F", std::localtime(&time_));
    return std::string{&buffer[0]};
}