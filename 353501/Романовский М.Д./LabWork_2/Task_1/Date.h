#include <QDate>
#include <string>

class Date {
public:
  Date(int year, int month, int day);

  long long GetDaysSinceEpoch() const;
  int GetYear(int *daysSinceYear) const;
  int GetYear() const;
  void GetParts(int *year, int *month, int *day) const;

  Date NextDay() const;
  Date PreviousDay() const;
  bool IsLeap() const;
  short WeekNumber() const;

  int Duration(Date date) const;
  int DaysTillYourBithday(Date birthdaydate);

  static Date FromString(std::string date);
  std::string ToString() const;

  QDate ToQDate() const;
  static Date FromQDate(QDate d);

private:
  Date(int year, int dayOfYear);

  int year;
  int dayOfYear;
};