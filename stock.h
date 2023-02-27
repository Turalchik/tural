//
// Created by musoroprovod && TURAL on 17.02.23.
//

#ifndef BAZASEREGI_STOCK_H
#define BAZASEREGI_STOCK_H


#include <iostream>
#include <fstream>

struct Stock {
    long jd;
    int seconds;
    int id;
    int amount;
    double price;
    char ticker[16];
    bool order;
};

void skipSpacer(std::istream& in);
long getJD(char buf[]);
int getTime(char buf[]);
bool tickerEqual(const char left[], const char right[]);
void outputNumber(std::ostream& out, int number);
void outputNumber(std::ofstream& out, int number);

std::istream& operator>>(std::istream& in, Stock& stock);
std::ostream& operator<<(std::ostream& out, Stock& stock);
std::ifstream& operator>>(std::ifstream& in, Stock& stock);
std::ofstream& operator<<(std::ofstream& out, Stock& stock);

#endif //BAZASEREGI_STOCK_H
