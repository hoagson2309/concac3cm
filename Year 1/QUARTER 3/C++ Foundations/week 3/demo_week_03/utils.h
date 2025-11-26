#ifndef DEMO_WEEK_03_UTILS_H
#define DEMO_WEEK_03_UTILS_H

#include <stdexcept>

/**
 * Checks if a year is a leap year
 * @param year to check
 * @return true if year is a leap year
 * @throws std::invalid_argument if year is negative
 */
[[nodiscard]]
inline bool is_leap_year(int year)
{
    if (year < 0)
    {
        throw std::invalid_argument{ "year should be non-negative."};
    }
    return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

/**
 * Returns the number of days in a month
 * @param year year to check
 * @param month month to check
 * @return number of days in the month
 * @throws std::invalid_argument if year is negative or month is not between 1 and 12
 */
[[nodiscard]]
inline int days_in_month(int year, int month)
{
    if (year < 0)
    {
        throw std::invalid_argument{ "year should be non-negative."};
    }
    if (month < 1 || month > 12) {
        throw std::invalid_argument(std::string{"month should be between 1 and 12, received: " + std::to_string(month)});
    }

    if (month == 2) {
        return is_leap_year(year) ? 29 : 28;
    }

    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }

    return 31;
}

#endif //DEMO_WEEK_03_UTILS_H
