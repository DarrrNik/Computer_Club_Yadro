#include <iomanip>

#include "Time.hpp"

Time::Time(unsigned short h, unsigned short m) : hour(h), minute(m) {}
Time::Time(const Time& t) : hour(t.hour), minute(t.minute) {}

bool operator<(const Time& lhs, const Time& rhs) { return lhs.hour <= rhs.hour && lhs.minute < rhs.minute; }
bool operator==(const Time& lhs, const Time& rhs) { return !(lhs < rhs && rhs < lhs); }
bool operator>(const Time& lhs, const Time& rhs) { return rhs < lhs; }
bool operator<=(const Time& lhs, const Time& rhs) { return !(lhs > rhs); }
bool operator>=(const Time& lhs, const Time& rhs) { return !(lhs < rhs); }

std::istream& operator>>(std::istream& in, Time& t) {
    char c;
    in >> t.hour >> c >> t.minute;
    return in;
}
std::ostream& operator<<(std::ostream& out, const Time& t) {
    out << std::setfill('0') << std::setw(2) << t.hour;
    out << ':';
    out << std::setfill('0') << std::setw(2) << t.minute;
    return out;
}

Time& Time::operator+=(const Time& rhs) {
    hour = (hour + rhs.hour + (minute + rhs.minute) / 60) % 24;
    minute = (minute + rhs.minute) % 60;
    return *this;
}
