#pragma once

#include "item.h"
#include <vector>
#include <map>

class Cafe
{
private:
    Item *inventory;
    Item *customer_order;
    double total;
    int len;
    bool endLoop;

    void displayMenu();
    void displayOrder();

    double getTotal() { return total; };
    Item *getInventory() { return inventory; };
    double setTotal(double price) { return total += price; };

    void cafeInit();
    void cafeOrder();
    void addToOrder(int index);
    void calculateTotal(int index, int quantity);
    void payLoop();
    int pay();
    std::vector<int> *calculateChange(int change, std::map<int, std::vector<int>> *memo);

    int validInput(std::string errorMessage);

public:
    Cafe();
    inline ~Cafe() { delete[] inventory; };
    void loop();
};
