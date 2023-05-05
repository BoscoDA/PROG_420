#pragma once
#include <string>

class Item
{
private:
    std::string name;
    double price;
    int quant;

public:
    inline std::string getName() { return name; };
    inline void setName(std::string item_name) { name = item_name; }
    inline double getPrice() { return price; };
    inline void setPrice(double item_price) { price = item_price; };
    inline void setQuant(int quantity) { quant += quantity; };
    inline int getQuant() { return quant; };
};
