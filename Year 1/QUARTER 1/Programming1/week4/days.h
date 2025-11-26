/// Determines if a given year is a leap year.
/// @param year The year to check.
/// @return true if the year is a leap year, false otherwise.
bool is_leap_year(int year);

/// Determines the number of days in a given month of a given year.
/// @param month The month (1-12) to check.
/// @param year The year to check.
/// @return The number of days in the given month of the given year.
int days_in_month(int month, int year);

/// Calculates the day in the year for a given date.
/// @param day The day of the month (1-31).
/// @param month The month (1-12).
/// @param year The year.
/// @return The day in the year for the given date.
int day_in_year(int day, int month, int year);

/// Calculates the number of days remaining in the year for a given date.
/// @param day The day of the month (1-31).
/// @param month The month (1-12).
/// @param year The year.
/// @return The number of days remaining in the year for the given date.
int remaining_days_in_year(int day, int month, int year);

/// Calculates the number of days between two dates.
/// @param day1 The day of the first date (1-31).
/// @param month1 The month of the first date (1-12).
/// @param year1 The year of the first date.
/// @param day2 The day of the second date (1-31).
/// @param month2 The month of the second date (1-12).
/// @param year2 The year of the second date.
/// @return The number of days between the two dates.
int days_between_dates(int day1, int month1, int year1, int day2, int month2, int year2);

