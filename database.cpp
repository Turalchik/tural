#include "database.h"


void addRecord(database& DB) {
    if (DB.count >= DB.maxsize) {
        DB.maxsize = DB.maxsize > 0 ? 2 * DB.maxsize : 1;
        Stock* tmp = new Stock[DB.maxsize];
        for (int i = 0; i < DB.count; ++i)
            tmp[i] = DB.data[i];
        if (DB.data)
            delete[] DB.data;
        DB.data = tmp;
    }

    Stock A;

    try {
        std::cin >> A;
    }
    catch (int value) {
        std::cout << value;
        return;
    }
    catch (...) {
        return;
    }

    quickSortPrice(DB);
    if (A.order) {
        int index = 0;
        while (A.amount > 0 && index < DB.count) {
            if (DB.data[index].price <= A.price) {
                if (!DB.data[index].order && tickerEqual(A.ticker, DB.data[index].ticker)) {
                    int tmp = (A.amount > DB.data[index].amount) ? DB.data[index].amount : A.amount;
                    A.amount -= tmp;
                    DB.data[index].amount -= tmp;
                }
            }
            else {
                break;
            }
            ++index;
        }
    }
    else {
        int index = DB.count - 1;
        while (A.amount > 0 && index >= 0) {
            if (DB.data[index].price >= A.price) {
                if (DB.data[index].order && tickerEqual(A.ticker, DB.data[index].ticker)) {
                    int tmp = (A.amount > DB.data[index].amount) ? DB.data[index].amount : A.amount;
                    A.amount -= tmp;
                    DB.data[index].amount -= tmp;
                }
            }
            else {
                break;
            }
            --index;
        }
    }

    A.id = ++DB.ID;
    DB.data[DB.count++] = A;
}

void printData(database& DB) {
    quickSortDate(DB);

    for (int index = 0; index < DB.count; ++index) {
        std::cout << DB.data[index];
    }
}

void quickSortDate(database& DB) {

    if (DB.count == 0) return;

    int N = DB.count, size = 1;
    while (N > 0) {
        N >>= 1;
        ++size;
    }

    size += 2;

    int* stackLeft = new int[size];
    int* stackRight = new int[size];
    int topInStack = -1;

    ++topInStack; stackLeft[topInStack] = 0; stackRight[topInStack] = DB.count - 1;

    while (topInStack > -1) {
        int from = stackLeft[topInStack];
        int to = stackRight[topInStack];
        --topInStack;

        int left = from, right = to;
        int pindex = (left + right) / 2;
        Stock p = DB.data[pindex];
        while (left < right) {
            while (true) {
                if (DB.data[left].jd < p.jd) {
                    ++left;
                }
                else if (DB.data[left].jd == p.jd) {
                    if (DB.data[left].seconds < p.seconds) {
                        ++left;
                    }
                    else if (DB.data[left].seconds == p.seconds) {
                        if (DB.data[left].id < p.id) {
                            ++left;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            while (true) {
                if (DB.data[right].jd > p.jd) {
                    --right;
                }
                else if (DB.data[right].jd == p.jd) {
                    if (DB.data[right].seconds > p.seconds) {
                        --right;
                    }
                    else if (DB.data[right].seconds == p.seconds) {
                        if (DB.data[right].id > p.id) {
                            --right;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            if (left < right) {
                Stock tmp = DB.data[left];
                DB.data[left] = DB.data[right];
                DB.data[right] = tmp;
                ++left;
                --right;
            }
            else if (left == right) {
                ++left;
                --right;
            }
        }

        if ((left + right) / 2 < left) {
            if (right > from) {
                ++topInStack;
                stackLeft[topInStack] = from;
                stackRight[topInStack] = right;
            }
            if (left < to) {
                ++topInStack;
                stackLeft[topInStack] = left;
                stackRight[topInStack] = to;
            }
        }
        else {
            if (left < to) {
                ++topInStack;
                stackLeft[topInStack] = left;
                stackRight[topInStack] = to;
            }
            if (right > from) {
                ++topInStack;
                stackLeft[topInStack] = from;
                stackRight[topInStack] = right;
            }
        }

    }

    delete[] stackLeft;
    delete[] stackRight;
}

void quickSortPrice(database& DB) {

    if (DB.count == 0) return;

    int N = DB.count, size = 1;
    while (N > 0) {
        N >>= 1;
        ++size;
    }

    size += 2;

    int* stackLeft = new int[size];
    int* stackRight = new int[size];
    int topInStack = -1;

    ++topInStack; stackLeft[topInStack] = 0; stackRight[topInStack] = DB.count - 1;

    while (topInStack > -1) {
        int from = stackLeft[topInStack];
        int to = stackRight[topInStack];
        --topInStack;

        int left = from, right = to;
        int pindex = (left + right) / 2;
        Stock p = DB.data[pindex];
        while (left < right) {
            while (true) {
                if (DB.data[left].price > p.price) {
                    ++left;
                }
                else if (DB.data[left].price == p.price) {
                    if (DB.data[left].id < p.id) {
                        ++left;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            while (true) {
                if (DB.data[right].price < p.price) {
                    --right;
                }
                else if (DB.data[right].price == p.price) {
                    if (DB.data[right].id > p.id) {
                        --right;
                    }
                    else {
                        break;
                    }
                }
                else {
                    break;
                }
            }
            if (left < right) {
                Stock tmp = DB.data[left];
                DB.data[left] = DB.data[right];
                DB.data[right] = tmp;
                ++left;
                --right;
            }
            else if (left == right) {
                ++left;
                --right;
            }
        }

        if ((left + right) / 2 < left) {
            if (right > from) {
                ++topInStack;
                stackLeft[topInStack] = from;
                stackRight[topInStack] = right;
            }
            if (left < to) {
                ++topInStack;
                stackLeft[topInStack] = left;
                stackRight[topInStack] = to;
            }
        }
        else {
            if (left < to) {
                ++topInStack;
                stackLeft[topInStack] = left;
                stackRight[topInStack] = to;
            }
            if (right > from) {
                ++topInStack;
                stackLeft[topInStack] = from;
                stackRight[topInStack] = right;
            }
        }

    }

    delete[] stackLeft;
    delete[] stackRight;
}

void loadData(database& DB) {

    skipSpacer(std::cin);
    char filename[32];
    std::cin >> filename;
    std::ifstream inFile(filename);

    while (inFile.peek() != EOF) {

        if (DB.count >= DB.maxsize) {
            DB.maxsize = DB.maxsize > 0 ? 2 * DB.maxsize : 1;
            Stock* tmp = new Stock[DB.maxsize];
            for (int i = 0; i < DB.count; ++i)
                tmp[i] = DB.data[i];
            if (DB.data)
                delete[] DB.data;
            DB.data = tmp;
        }

        inFile >> DB.data[DB.count++];
    }

    inFile.close();
}

void saveData(database& DB) {

    skipSpacer(std::cin);
    char filename[32];
    std::cin >> filename;
    std::ofstream outFile(filename);

    for (int index = 0; index < DB.count; ++index) {
        outFile << DB.data[index];
        if (index != DB.count - 1) {
            outFile << std::endl;
        }
    }

    outFile.close();
}

void deleteStock(database& DB) {

    int id;
    std::cin >> id;

    int index = 0;
    for (; index < DB.count; ++index) {
        if (DB.data[index].id == id) break;
    }

    --DB.count;
    for (; index < DB.count; ++index) {
        DB.data[index] = DB.data[index + 1];
    }
}

void clearData(database& DB) {

    int i = 0;
    for (; i < DB.count; ++i) {
        if (DB.data[i].amount == 0) {
            int j = i + 1;
            while (DB.data[j].amount == 0 && j < DB.count) ++j;
            if (j != DB.count) {
                DB.data[i] = DB.data[j];
                DB.data[j].amount = 0;
            }
            else {
                break;
            }
        }
    }
    DB.count = i;
}

void exportData(database& DB) {
    skipSpacer(std::cin);
    char filename[32];
    std::cin >> filename;
    std::ofstream outFile(filename);

    quickSortDate(DB);
    for (int index = 0; index < DB.count; ++index) {
        outFile << DB.data[index];
        if (index != DB.count - 1) {
            outFile << std::endl;
        }
    }
}


void domData(database& DB) {

    if (DB.count == 0) return;

    int N = DB.count, size = 1;
    while (N > 0) {
        N >>= 1;
        ++size;
    }

    size += 2;

    int* stackLeft = new int[size];
    int* stackRight = new int[size];
    int topInStack = -1;

    ++topInStack; stackLeft[topInStack] = 0; stackRight[topInStack] = DB.count - 1;

    while (topInStack > -1) {
        int from = stackLeft[topInStack];
        int to = stackRight[topInStack];
        --topInStack;

        int left = from, right = to;
        int pindex = (left + right) / 2;
        Stock p = DB.data[pindex];
        while (left < right) {
            while (true) {
                if (DB.data[left].price > p.price) {
                    ++left;
                }
                else if (DB.data[left].price == p.price) {
                    if (DB.data[left].order == p.order) {
                        if (DB.data[left].order) {
                            if (DB.data[left].jd < p.jd) {
                                ++left;
                            }
                            else if (DB.data[left].jd == p.jd) {
                                if (DB.data[left].seconds < p.seconds) {
                                    ++left;
                                }
                                else if (DB.data[left].seconds == p.seconds) {
                                    if (DB.data[left].id < p.id) {
                                        ++left;
                                    }
                                    else {
                                        break;
                                    }
                                }
                                else {
                                    break;
                                }
                            }
                            else {
                                break;
                            }

                        }
                        else {
                            if (DB.data[left].jd > p.jd) {
                                ++left;
                            }
                            else if (DB.data[left].jd == p.jd) {
                                if (DB.data[left].seconds > p.seconds) {
                                    ++left;
                                }
                                else if (DB.data[left].seconds == p.seconds) {
                                    if (DB.data[left].id < p.id) {
                                        ++left;
                                    }
                                    else {
                                        break;
                                    }
                                }
                                else {
                                    break;
                                }
                            }
                            else {
                                break;
                            }
                        }
                    }
                    else {
                        if (DB.data[left].order) {
                            break;
                        }
                        else {
                            ++left;
                        }
                    }
                }
                else {
                    break;
                }

            }
            while (true) {
                if (DB.data[right].price < p.price) {
                    --right;
                }
                else if (DB.data[right].price == p.price) {
                    if (DB.data[right].order == p.order) {
                        if (DB.data[right].order) {
                            if (DB.data[right].jd > p.jd) {
                                --right;
                            }
                            else if (DB.data[right].jd == p.jd) {
                                if (DB.data[right].seconds > p.seconds) {
                                    --right;
                                }
                                else if (DB.data[right].seconds == p.seconds) {
                                    if (DB.data[right].id > p.id) {
                                        --right;
                                    }
                                    else {
                                        break;
                                    }
                                }
                                else {
                                    break;
                                }
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            if (DB.data[right].jd < p.jd) {
                                --right;
                            }
                            else if (DB.data[right].jd == p.jd) {
                                if (DB.data[right].seconds < p.seconds) {
                                    --right;
                                }
                                else if (DB.data[right].seconds == p.seconds) {
                                    if (DB.data[right].id > p.id) {
                                        --right;
                                    }
                                    else {
                                        break;
                                    }
                                }
                                else {
                                    break;
                                }
                            }
                            else {
                                break;
                            }
                        }
                    }
                    else {
                        if (DB.data[right].order) {
                            --right;
                        }
                        else {
                            break;
                        }
                    }
                }
                else {
                    break;
                }
            }
            if (left < right) {
                Stock tmp = DB.data[left];
                DB.data[left] = DB.data[right];
                DB.data[right] = tmp;
                ++left;
                --right;
            }
            else if (left == right) {
                ++left;
                --right;
            }
        }

        if ((left + right) / 2 < left) {
            if (right > from) {
                ++topInStack;
                stackLeft[topInStack] = from;
                stackRight[topInStack] = right;
            }
            if (left < to) {
                ++topInStack;
                stackLeft[topInStack] = left;
                stackRight[topInStack] = to;
            }
        }
        else {
            if (left < to) {
                ++topInStack;
                stackLeft[topInStack] = left;
                stackRight[topInStack] = to;
            }
            if (right > from) {
                ++topInStack;
                stackLeft[topInStack] = from;
                stackRight[topInStack] = right;
            }
        }

    }

    delete[] stackLeft;
    delete[] stackRight;

    skipSpacer(std::cin);
    char ticker[16];
    std::cin >> ticker;

    for (int index = 0; index < DB.count; ++index) {
        if (tickerEqual(ticker, DB.data[index].ticker)) {
            std::cout << DB.data[index];
        }
    }
}