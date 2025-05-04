#pragma once
#include <iostream>

class Time {
public:
    Time() = default;
    Time(unsigned short h, unsigned short m);
    Time(const Time& t);

    friend bool operator<(const Time& lhs, const Time& rhs);
    friend std::istream& operator>>(std::istream& in, Time& t);
    friend std::ostream& operator<<(std::ostream& out, const Time& t);
    Time& operator+=(const Time& rhs);
private:
    unsigned short hour, minute;
};
