//
// Created by musoroprovod && TURAL on 17.02.23.
//

#ifndef _DATABAZA_
#define _DATABAZA_

#include "stock.h"
#include <fstream>

struct database {
    int count;
    int maxsize;
    int ID;
    Stock* data;
};

void addRecord(database& DB);
void printData(database& DB);
void loadData(database& DB);
void saveData(database& DB);
void deleteStock(database& DB);
void clearData(database& DB);
void domData(database& DB);
void exportData(database& DB);
void quickSortDate(database& DB);
void quickSortPrice(database& DB);

#endif
