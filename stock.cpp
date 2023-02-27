#include <iomanip>
#include "stock.h"


void skipSpacer(std::istream& in) {
    while (in.peek() == ' ') {
        in.ignore();
    }
}


long getJD(char buf[]) {

    int day = 0;
    int month = 0;
    int year = 0;
    int tmp = 0;

    for (int index = 0; buf[index] != '\0'; ++index) {
        if ((buf[index] >= '0') && (buf[index] <= '9')) {
            tmp *= 10;
            tmp += buf[index] - '0';
        }
        else if (buf[index] == '.') {
            if (day == 0) {
                day = tmp;
            }
            else if (month == 0) {
                month = tmp;
            }
            tmp = 0;
        }
        else {
            return -1;
        }
    }

    if (tmp > 0) {
        year = tmp;
    }
    else {
        return -1; //format
    }

    if (month > 12 || month < 1) {
        return -2; // wrong month
    }

    if ((day < 1) || (day > 31) || (month == 2 && !(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)) && day >= 29) || (month == 2 && (year % 4 != 0) && day > 28)) {
        return -3;
    }

    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;

    return day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;

}
int getTime(char buf[]) {

    int hour = 0;
    int min = 0;
    int sec = 0;
    int cut = 0;

    for (int index = 0; buf[index] != '\0'; ++index) {
        if ((buf[index] >= '0') && (buf[index] <= '9')) {
            switch (cut) {
            case 0:
                hour = hour * 10 + (static_cast<int>(buf[index]) - '0');
                break;
            case 1:
                min = min * 10 + (static_cast<int>(buf[index]) - '0');
                break;
            case 2:
                sec = sec * 10 + (static_cast<int>(buf[index]) - '0');
                break;
            default:
                return -1;
            }
        }
        else if (buf[index] == ':' && cut < 2) {
            ++cut;
        }
        else {
            return -1;
        }
    }
    return  hour * 3600 + min * 60 + sec;
}

std::istream& operator>>(std::istream& in, Stock& stock) {
    char buf[16];

    skipSpacer(in);
    in.getline(buf, 15, ' ');
    buf[in.gcount()] = '\0';
    stock.jd = getJD(buf);
    int index = 0;
    int value = 0;

    switch (stock.jd) {
    case -1:
        std::cout << "Wrong date format: " << buf;
        throw;

    case -2:
        while (buf[index++] != '.');
        std::cout << "Month value is invalid: ";

        do {
            value = value * 10 + static_cast<int>(buf[index]) - '0';

        } while (buf[++index] != '.');
        throw value;

    case -3:
        std::cout << "Day value is invalid: ";
        do {
            value = value * 10 + static_cast<int>(buf[index]) - '0';

        } while (buf[++index] != '.');
        throw value;
    }

    skipSpacer(in);
    in.getline(buf, 15, ',');
    buf[in.gcount()] = '\0';
    stock.seconds = getTime(buf);

    switch (stock.seconds) {
    case -1:
        std::cout << "Wrong time format: " << buf;
        return in;
    case -2:
        std::cout << "Time value is invalid: " << buf;
        return in;
    }

    //ticker
    skipSpacer(in);
    in.getline(stock.ticker, 15, ',');
    stock.ticker[in.gcount()] = '\0';

    //order
    skipSpacer(in);
    stock.order = in.get() == 'b';
    while (in.peek() != ' ') {
        in.ignore();
    }

    //amount
    in >> stock.amount;

    in.ignore();

    //price
    in >> stock.price;

    return in;
}

bool tickerEqual(const char left[], const char right[]) {
    int index = 0;
    while (left[index] != '\0' && right[index] != '\0') {
        if ((left[index] | 32) != (right[index] | 32)) return false;
        ++index;
    }
    if (left[index] == '\0' && right[index] == '\0') return true;
    else return false;
}

std::ostream& operator<<(std::ostream& out, Stock& stock) {
    int a = stock.jd + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - (146097 * b) / 4;
    int d = (4 * c + 3) / 1461;
    int e = c - (1461 * d) / 4;
    int m = (5 * e + 2) / 153;

    int day = e - (153 * m + 2) / 5 + 1;
    int month = m + 3 - 12 * (m / 10);
    int year = 100 * b + d - 4800 + (m / 10);

    out << year;
    out << '.';
    outputNumber(out, month);
    out << '.';
    outputNumber(out, day);
    out << ' ';



    int hour = stock.seconds / 3600;
    int minutes = (stock.seconds % 3600) / 60;
    int seconds = stock.seconds % 60;

    outputNumber(out, hour);
    out << ':';
    outputNumber(out, minutes);
    out << ':';
    outputNumber(out, seconds);
    out << ", ";

    out << stock.ticker << ", ";
    if (stock.order) {
        out << "buy, ";
    }
    else {
        out << "sell, ";
    }
    out << stock.amount << ", ";
    out << std::fixed << std::setprecision(2) << stock.price << std::endl;

    return out;
}


std::ofstream& operator<<(std::ofstream& out, Stock& stock) {
    int a = stock.jd + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - (146097 * b) / 4;
    int d = (4 * c + 3) / 1461;
    int e = c - (1461 * d) / 4;
    int m = (5 * e + 2) / 153;

    int day = e - (153 * m + 2) / 5 + 1;
    int month = m + 3 - 12 * (m / 10);
    int year = 100 * b + d - 4800 + (m / 10);

    out << year;
    out << '.';
    outputNumber(out, month);
    out << '.';
    outputNumber(out, day);
    out << ' ';



    int hour = stock.seconds / 3600;
    int minutes = (stock.seconds % 3600) / 60;
    int seconds = stock.seconds % 60;

    outputNumber(out, hour);
    out << ':';
    outputNumber(out, minutes);
    out << ':';
    outputNumber(out, seconds);
    out << ", ";

    out << stock.ticker << ", ";
    if (stock.order) {
        out << "buy, ";
    }
    else {
        out << "sell, ";
    }
    out << stock.amount << ", ";
    out << std::fixed << std::setprecision(2) << stock.price;

    return out;
}

void outputNumber(std::ostream& out, int number) {
    if (number > 9) {
        out << number;
    }
    else {
        out << '0' << number;
    }
}

void outputNumber(std::ofstream& out, int number) {
    if (number > 9) {
        out << number;
    }
    else {
        out << '0' << number;
    }
}

std::ifstream& operator>>(std::ifstream& in, Stock& stock) {
    int day;
    int month;
    int year;

    in >> year;
    in.ignore();
    in >> month;
    in.ignore();
    in >> day;

    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;

    stock.jd = day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045;

    int hour;
    int minutes;
    int seconds;

    in >> hour;
    in.ignore();
    in >> minutes;
    in.ignore();
    in >> seconds;

    stock.seconds = hour * 3600 + minutes * 60 + seconds;

    in.ignore(2);
    in.getline(stock.ticker, 15, ',');
    stock.ticker[in.gcount()] = '\0';

    in.ignore();
    stock.order = (in.get() == 'b') ? true : false;
    while (in.get() != ' ');

    in >> stock.amount;

    in.ignore();
    in >> stock.price;

    return in;
}