#include <iostream>
#include <cstring>
#include "database.h"

int main() {

    database DB = { 0, 0, 0, nullptr };

    do {
        std::cout << '>';
        char arr[32];
        std::cin >> arr;

        if (!strcmp(arr, "add")) {
            addRecord(DB);
        }
        else if (!strcmp(arr, "print")) {
            printData(DB);
        }
        else if (!strcmp(arr, "delete")) {
            deleteStock(DB);
        }
        else if (!strcmp(arr, "load")) {
            loadData(DB);
        }
        else if (!strcmp(arr, "save")) {
            saveData(DB);
        }
        else if (!strcmp(arr, "clear")) {
            clearData(DB);
        }
        else if (!strcmp(arr, "clear")) {
            clearData(DB);
        }
        else if (!strcmp(arr, "dom")) {
            domData(DB);
        }
        else if (!strcmp(arr, "export")) {
            exportData(DB);
        }
        else if (!strcmp(arr, "quit")) {
            delete[] DB.data;
            break;
        }
        std::cin.clear();
    } while (true);

    return 0;
}