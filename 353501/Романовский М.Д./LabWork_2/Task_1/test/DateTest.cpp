#include "../Date.h"
#include "gtest/gtest.h"
#include <stdexcept>

// TEST(basic, creation_works) {
//   Date d(888888);
//   EXPECT_EQ(d.GetDaysSinceEpoch(), 888888);
// }

TEST(basic, restore) {
  Date d(1880, 2, 29);
  EXPECT_EQ(d.GetDaysSinceEpoch(), 686349);
}

TEST(error, invalid) {
  EXPECT_THROW({ Date d(-50, 8, 2); }, std::invalid_argument);
  EXPECT_THROW({ Date d(2024, 22, 2); }, std::invalid_argument);
  EXPECT_THROW({ Date d(2023, 2, 29); }, std::invalid_argument);
}

TEST(basic, getYear) {
  {
    Date d(1880, 2, 29);
    int daysSinceYear;
    EXPECT_EQ(d.GetYear(), 1880);
    EXPECT_EQ(d.GetYear(&daysSinceYear), 1880);
    EXPECT_EQ(daysSinceYear, 60);
  }

  {
    Date d(2024, 1, 1);
    int daysSinceYear;
    EXPECT_EQ(d.GetYear(), 2024);
    EXPECT_EQ(d.GetYear(&daysSinceYear), 2024);
    EXPECT_EQ(daysSinceYear, 1);
  }
}

TEST(basic, getParts) {
  Date d(1880, 2, 29);
  int year, month, day;
  d.GetParts(&year, &month, &day);
  EXPECT_EQ(year, 1880);
  EXPECT_EQ(month, 2);
  EXPECT_EQ(day, 29);
}

TEST(basic, weekNumber) {
  for (int i = 3; i <= 9; i++) {
    Date d(2025, 2, i);
    short weekNumber = d.WeekNumber();
    EXPECT_EQ(weekNumber, 6);
  }
}

TEST(brute, weekNumber) {
  for (int i = 2000; i <= 2048; i++) {
    Date d(i, 1, 8);
    short weekNumber = d.WeekNumber();
    EXPECT_EQ(weekNumber, 2);
  }
}

TEST(brute, duration) {
  Date src(2006, 4, 2);
  for (int i = 10; i <= 15; i++) {
    Date d(2024, 8, i);
    int daysBetween = src.Duration(d);
    EXPECT_EQ(daysBetween, 6705 - 10 + i);
  }
}

TEST(brute, next) {
  Date src(1999, 12, 28);
  for (int i = 0; i <= 64; i++) {
    EXPECT_EQ(src.GetDaysSinceEpoch(), 730115 + i);
    src = src.NextDay();
  }
}

TEST(brute, prev) {
  Date src(1000, 3, 1);
  for (int i = 0; i <= 64; i++) {
    EXPECT_EQ(src.GetDaysSinceEpoch(), 364936 - i);
    src = src.PreviousDay();
  }
}

TEST(brute, daysBirthday) {
  Date src(2008, 2, 29);
  Date d(2024, 2, 25);

  int answers[] = {4, 3, 2, 1, 0, 364, 363, 362};
  for (int i = 0; i < 8; i++) {
    int daysBetween = d.DaysTillYourBithday(src);
    // std::cout << daysBetween << " ";
    EXPECT_EQ(daysBetween, answers[i]);

    d = d.NextDay();
  }
}

TEST(string, simpleParse) {
  Date src(2008, 2, 29);
  Date d = Date::FromString("29.02.2008");

  EXPECT_EQ(src.GetDaysSinceEpoch(), src.GetDaysSinceEpoch());
}

TEST(string, power) {
  int curDay = 0;
  for (int i = 8888; i < 20; i++) {
    Date src(2008, 2, 29);
    std::string s = src.ToString();
    Date parsed = Date::FromString(s);

    EXPECT_EQ(src.GetDaysSinceEpoch(), parsed.GetDaysSinceEpoch());
  }
}

TEST(wierd, day732656) {
  QDate qbirthday(2006, 11, 8);
  Date birthday = Date::FromQDate(qbirthday);
  int year, month, day;
  birthday.GetParts(&year, &month, &day);

  EXPECT_EQ(year, 2006);
  EXPECT_EQ(month, 11);
  EXPECT_EQ(day, 8);
}

TEST(wierd, millenia) {
  Date birthday(2000, 1, 1);
  EXPECT_EQ(birthday.GetDaysSinceEpoch(), 730119);

  Date birthday2(2000, 3, 20);
  EXPECT_EQ(birthday2.GetDaysSinceEpoch(), 730198);
}

TEST(wierd, year400) {
  Date birthday(400, 12, 31);
  EXPECT_EQ(birthday.GetDaysSinceEpoch(), 146096);
}

TEST(wierd, decembro) {
  QDate qbirthday(2000, 12, 31);
  Date birthday = Date::FromQDate(qbirthday);
  int year, month, day;
  birthday.GetParts(&year, &month, &day);

  EXPECT_EQ(year, 2000);
  EXPECT_EQ(month, 12);
  EXPECT_EQ(day, 31);
}