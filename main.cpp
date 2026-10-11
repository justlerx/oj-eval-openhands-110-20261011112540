#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
const int month_days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

class Date
{
private:
    int _year;
    int _month;
    int _day;

    // Helper function to check if a year is leap year
    bool isLeapYear(int year) const {
        if (year % 4 != 0) return false;
        if (year % 100 != 0) return true;
        return (year % 400 == 0);
    }

    // Helper function to get days in a month
    int getDaysInMonth(int year, int month) const {
        if (month == 2 && isLeapYear(year)) {
            return 29;
        }
        return month_days[month];
    }

    // Helper function to validate date
    bool isValidDate(int year, int month, int day) const {
        if (year < 1900 || year > 2030) return false;
        if (month < 1 || month > 12) return false;
        if (day < 1 || day > getDaysInMonth(year, month)) return false;
        return true;
    }

    // Convert date to days since 1900-01-01 for calculations
    int convertToDays() const {
        int days = 0;
        
        // Add days for complete years
        for (int y = 1900; y < _year; y++) {
            days += isLeapYear(y) ? 366 : 365;
        }
        
        // Add days for complete months in current year
        for (int m = 1; m < _month; m++) {
            days += getDaysInMonth(_year, m);
        }
        
        // Add days in current month
        days += _day - 1; // -1 because 1900-01-01 should be day 0
        
        return days;
    }

    // Convert days since 1900-01-01 back to date
    void convertFromDays(int totalDays) {
        _year = 1900;
        _month = 1;
        _day = 1;
        
        // Find year
        while (totalDays >= (isLeapYear(_year) ? 366 : 365)) {
            totalDays -= (isLeapYear(_year) ? 366 : 365);
            _year++;
        }
        
        // Find month
        while (totalDays >= getDaysInMonth(_year, _month)) {
            totalDays -= getDaysInMonth(_year, _month);
            _month++;
        }
        
        // Find day
        _day += totalDays;
    }

public:
    // Default constructor: 1900-1-1
    Date() : _year(1900), _month(1), _day(1) {}

    // Parameterized constructor with validation
    Date(int yy, int mm, int dd) {
        if (isValidDate(yy, mm, dd)) {
            _year = yy;
            _month = mm;
            _day = dd;
        } else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }

    // Prefix ++ operator
    Date& operator++() {
        _day++;
        if (_day > getDaysInMonth(_year, _month)) {
            _day = 1;
            _month++;
            if (_month > 12) {
                _month = 1;
                _year++;
            }
        }
        return *this;
    }

    // Postfix ++ operator
    Date operator++(int) {
        Date temp = *this;
        ++(*this);
        return temp;
    }

    // Prefix -- operator
    Date& operator--() {
        _day--;
        if (_day < 1) {
            _month--;
            if (_month < 1) {
                _month = 12;
                _year--;
            }
            _day = getDaysInMonth(_year, _month);
        }
        return *this;
    }

    // Postfix -- operator
    Date operator--(int) {
        Date temp = *this;
        --(*this);
        return temp;
    }

    // Date + int operator
    Date operator+(int days) const {
        Date result = *this;
        int totalDays = result.convertToDays() + days;
        result.convertFromDays(totalDays);
        return result;
    }

    // Date - int operator
    Date operator-(int days) const {
        Date result = *this;
        int totalDays = result.convertToDays() - days;
        result.convertFromDays(totalDays);
        return result;
    }

    // Date - Date operator (absolute difference in days)
    int operator-(const Date& other) const {
        int days1 = this->convertToDays();
        int days2 = other.convertToDays();
        return abs(days1 - days2);
    }

    // < operator (returns 1 or 0 as specified)
    int operator<(const Date& other) const {
        if (_year < other._year) return 1;
        if (_year > other._year) return 0;
        if (_month < other._month) return 1;
        if (_month > other._month) return 0;
        if (_day < other._day) return 1;
        return 0;
    }

    // Output stream operator
    friend ostream& operator<<(ostream& os, const Date& date) {
        os << date._year << "-" << date._month << "-" << date._day;
        return os;
    }

    // Alternative output function (as mentioned in problem)
    void out() const {
        cout << _year << "-" << _month << "-" << _day << endl;
    }
};

void Test()
{
    int op;
    cin >> op;
    int yy, mm, dd;
    if (op == 1 || op == 0)
    {
        Date d0;
        Date d1(2000, 2, 29);
        Date d2(1900, 2, 29);
        cout << d0 << endl;
        cout << d1 << endl;
        cout << d2 << endl;
        //d0.out(); d1.out(); d2.out();
    }
    if (op == 2 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        for (int i=0;i<5;++i) cout << ++d0 << endl; //(++d0).out();
        for (int i=0;i<5;++i) cout << d0++ << endl; //(d0++).out();
        for (int i=0;i<5;++i) cout << d0-- << endl; //(d0--).out();
        for (int i=0;i<2;++i) cout << --d0 << endl; //(--d0).out();
        cout << d0 << endl;
        //d0.out();
    }
    if (op == 3 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        cout << d0 + 100 << endl;
        // (d0+100).out();
        cout << d0 - 1000 << endl;
        // (d0-1000).out();
    }
    if (op == 4 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(2020, 12, 21);
        cout << (d0 < d1) << endl;
    }
    if (op == 5 || op == 0)
    {
        cin >> yy >> mm >> dd;
        Date d0(yy, mm, dd);
        Date d1(1912, 6, 23);
        cout << d0 - d1 << endl;
    }
}
int main()
{
    Test();
    return 0;
}