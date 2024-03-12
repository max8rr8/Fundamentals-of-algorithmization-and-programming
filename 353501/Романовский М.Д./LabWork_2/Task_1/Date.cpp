#include "Date.h"
#include <cstdio>
#include <iostream>
#include <stdexcept>

const long long DAYS_IN_400_YEARS = 146097;
const long long DAYS_IN_100_YEARS = 36524;
const long long DAYS_IN_4_YEARS = 1461;
const long long DAYS_IN_YEAR = 365;

const long long DAYS_SINCE_EPOCH = 306;

bool isLeapYear(int year) {
  if (year % 100 == 0)
    return year % 400 == 0;
  else
    return year % 4 == 0;
}

const int DAYS_IN_MONTH[] = {31, -1, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int getDaysInMonth(int month, bool isLeap) {
  if (month == 2) {
    return isLeap ? 29 : 28;
  } else {
    return DAYS_IN_MONTH[month - 1];
  }
}

Date::Date(int _year, int month, int day) {
  if (_year < 1 || _year > 9999)
    throw std::invalid_argument("Year is out of bounds");

  year = _year;
  bool isLeap = isLeapYear(year);

  if (month < 1 || month > 12)
    throw std::invalid_argument("Month is out of bounds");

  dayOfYear = 0;
  for (int i = 1; i < month; i++) {
    dayOfYear += getDaysInMonth(i, isLeap);
  }

  if (day < 1 || day > getDaysInMonth(month, isLeap))
    throw std::invalid_argument("Day is out of bounds");

  dayOfYear += day - 1;
}

Date::Date(int _year, int _dayOfYear) {
  year = _year;
  dayOfYear = _dayOfYear;
}

long long Date::GetDaysSinceEpoch() const {
  long long d = dayOfYear;
  long long y = year - 1;

  d += DAYS_IN_400_YEARS * (y / 400);
  y %= 400;

  d += DAYS_IN_100_YEARS * (y / 100);
  y %= 100;

  d += DAYS_IN_4_YEARS * (y / 4);
  y %= 4;

  d += y * DAYS_IN_YEAR;

  return d;
}

int Date::GetYear(int *daysSinceYear) const {
  if (daysSinceYear)
    *daysSinceYear = dayOfYear + 1;

  return year;
}

int Date::GetYear() const { return GetYear(nullptr); }

void Date::GetParts(int *_year, int *month, int *day) const {
  *_year = year;
  *month = 0;

  bool isLeap = isLeapYear(year);

  int doy = dayOfYear + 1;

  for (int i = 1; i <= 12; i++) {
    int daysIn = getDaysInMonth(i, isLeap);
    if (doy > daysIn) {
      doy -= daysIn;
    } else {
      *month = i;
      break;
    }
  }

  *day = doy;
}

Date Date::NextDay() const {
  int daysInYear = DAYS_IN_YEAR;
  if (IsLeap())
    daysInYear++;

  if (dayOfYear + 1 >= daysInYear) {
    return Date(year + 1, 0);
  }

  return Date(year, dayOfYear + 1);
}

Date Date::PreviousDay() const {
  if (dayOfYear == 0) {
    Date prev(year - 1, 0);

    int daysInYear = DAYS_IN_YEAR;
    if (prev.IsLeap())
      daysInYear++;

    prev.dayOfYear = daysInYear - 1;

    return prev;
  }

  return Date(year, dayOfYear - 1);
}

bool Date::IsLeap() const { return isLeapYear(GetYear()); }

short Date::WeekNumber() const {
  short dayOfStartWeek = (GetDaysSinceEpoch() - dayOfYear) % 7;
  return ((dayOfStartWeek + dayOfYear) / 7) + 1;
}

int Date::Duration(Date date) const {
  return date.GetDaysSinceEpoch() - GetDaysSinceEpoch();
}

Date getDateForYearLimited(int year, int month, int day) {
  if (month == 2 && day == 29 && !isLeapYear(year))
    return Date(year, 2, 28);

  return Date(year, month, day);
}

int Date::DaysTillYourBithday(Date birthdaydate) {
  bool k = false;
  if (year > 9000) {
    k = true;
    year -= 400;
  }

  int yearOfBirth, monthOfBirth, dayOfBirth;
  birthdaydate.GetParts(&yearOfBirth, &monthOfBirth, &dayOfBirth);

  Date nextBirthday = getDateForYearLimited(year, monthOfBirth, dayOfBirth);
  if (nextBirthday.dayOfYear < dayOfYear) {
    nextBirthday = getDateForYearLimited(year + 1, monthOfBirth, dayOfBirth);
  }

  int d = Duration(nextBirthday);
  if (k)
    year += 400;

  return d;
}

Date Date::FromString(std::string date) {
  if (date.size() != 10)
    throw std::invalid_argument("Invalid date, length should be 10");

  for (int i = 0; i < 10; i++) {
    if (i == 2 || i == 5) {
      if (date[i] != '.')
        throw std::invalid_argument("Invalid date, expected dot");
    } else {
      if (date[i] < '0' || date[i] > '9')
        throw std::invalid_argument("Invalid date, expected digit");
    }
  }

  int day = (date[0] - '0') * 10 + (date[1] - '0');
  int month = (date[3] - '0') * 10 + (date[4] - '0');

  int year = (date[6] - '0') * 1000;
  year += (date[7] - '0') * 100;
  year += (date[8] - '0') * 10;
  year += (date[9] - '0') * 1;

  return Date(year, month, day);
}

std::string Date::ToString() const {
  int year, month, day;
  GetParts(&year, &month, &day);

  char date[11];
  snprintf(date, 11, "%02d.%02d.%04d", day, month, year);

  return std::string(date);
}

QDate Date::ToQDate() const {
  int year, month, day;
  GetParts(&year, &month, &day);

  return QDate(year, month, day);
}

Date Date::FromQDate(QDate d) { return Date(d.year(), d.month(), d.day()); }