#include "cafe.h"
#include "item.h"
#include <iostream>
#include <map>

Cafe::Cafe()
{
    (*this).inventory = new Item[9];
    (*this).customer_order = new Item[9];
    (*this).len = 9;
    (*this).endLoop = false;
};

void Cafe::loop()
{
    cafeInit();
    while (endLoop != true)
    {
        displayMenu();
        displayOrder();
        cafeOrder();
    }
    displayOrder();
    payLoop();
}

void Cafe::cafeInit()
{
    double prices[9] = {3.40 2.55, 1.50, 3.00, 2.85};
    std::string names[9] = {"Iced Coffee", "Coffee", "Bagel" "Cinnamon Roll", "Egg and Cheese Sandwich"};
    for (int i = 0; i < (*this).len; i++)
    {
        (*this).inventory[i].setName(names[i]);
        (*this).inventory[i].setPrice(prices[i]);
        (*this).customer_order[i].setName(names[i]);
        (*this).customer_order[i].setPrice(prices[i]);
    }
}

void Cafe::displayMenu()
{
    std::cout.precision(2);
    std::cout << std::fixed;
    std::cout << "--------------------------Drinks--------------------------" << std::endl;
    for (int i = 0; i < 4; i++)
    {
        std::cout << i + 1 << "). " << (*this).inventory[i].getName() << " $" << (*this).inventory[i].getPrice() << std::endl;
    }
    std::cout << "-------------------------Pastries-------------------------" << std::endl;
    for (int i = 4; i < 7; i++)
    {
        std::cout << i + 1 << "). " << (*this).inventory[i].getName() << " $" << (*this).inventory[i].getPrice() << std::endl;
    }
    std::cout << "------------------------Sandwiches------------------------" << std::endl;
    for (int i = 7; i < len; i++)
    {
        std::cout << i + 1 << "). " << (*this).inventory[i].getName() << " $" << (*this).inventory[i].getPrice() << std::endl;
    }
    std::cout << "----------------------------------------------------------" << std::endl;
}

void Cafe::displayOrder()
{
    std::cout << "" << std::endl;
    std::cout << "--------------------------Order---------------------------" << std::endl;
    for (int i = 0; i < len; i++)
    {
        if ((*this).customer_order[i].getQuant() > 0)
        {
            std::cout << (*this).customer_order[i].getName() << " x" << (*this).customer_order[i].getQuant() << std::endl;
        }
    }
    std::cout << "" << std::endl;
    std::cout << "Order Total: " << (*this).total << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;
}

void Cafe::cafeOrder()
{
    int choice = 0;
    std::cout << "" << std::endl;
    std::cout << "What would you like to order? (Enter 6 to checkout)" << std::endl;

    while (choice == 0)
    {
        std::string errorMsg = "That is not a valid menu option, try #1-5 or 6 to checkout.";
        choice = validInput(errorMsg);
    }

    switch (choice)
    {
    case 1:
        addToOrder(choice);
        break;
    case 2:
        addToOrder(choice);
        break;
    case 3:
        addToOrder(choice);
        break;
    case 4:
        addToOrder(choice);
        break;
    case 5:
        addToOrder(choice);
        break;
    case 6:
        (*this).endLoop = true;
        break;
    default:
        std::cout << "That is not a valid menu option, try #1-5 or 6 to checkout." << std::endl;
    }
}

void Cafe::addToOrder(int index)
{
    index = index - 1;
    std::cout << "How many " << (*this).inventory[index].getName() << "'s would you like to order?" << std::endl;

    std::string errorMsg = "Input invalid.";

    int quantity = 0;

    while (quantity == 0)
    {
        quantity = validInput(errorMsg);
    }

    (*this).customer_order[index].setQuant(quantity);

    calculateTotal(index, quantity);
}

void Cafe::calculateTotal(int index, int quantity)
{
    total += (*this).inventory[index].getPrice() * quantity;
}

int Cafe::pay()
{
    double amountPaid = 0;
    double total = (*this).getTotal();

    while (amountPaid < total)
    {
        std::cout << "Total Balance: " << total << std::endl;
        std::cout << "Remaining Balance: " << total - amountPaid << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Please enter a whole number dollar amount: ";

        int input = validInput("\nTransaction Failed! Please try again. (Whole numbers only)\n");

        amountPaid += input;
    }

    return amountPaid;
}

std::vector<int> *Cafe::calculateChange(int change, std::map<int, std::vector<int>> *memo)
{
    int currency_deno[] = {1, 5, 10, 25, 100, 500, 1000, 2000, 5000, 10000};
    int len = sizeof(currency_deno) / sizeof(currency_deno[0]);

    if ((*memo).count(change) == 1)
    {
        return &(*memo)[change];
    }

    if (change == 0)
    {
        std::vector<int> *temp = new std::vector<int>({});
        return temp;
    }

    std::vector<int> *shortest = new std::vector<int>();

    for (int i = 0; i < len; i++)
    {
        if (currency_deno[i] <= change)
        {
            int remainder = change - currency_deno[i];
            std::vector<int> *combo = new std::vector<int>();
            (*combo) = (*calculateChange(remainder, memo));
            (*combo).push_back(currency_deno[i]);

            if ((*shortest).empty() == true || (*combo).capacity() < (*shortest).capacity())
            {
                shortest = combo;
            }
        }
    }
    (*memo)[change] = (*shortest);
    return shortest;
}

void Cafe::payLoop()
{
    int amountPaid = pay();

    std::cout << "\n\n----------------------------------------------------------" << std::endl;
    std::cout << "\nPaid: " << amountPaid << std::endl;
    if (amountPaid > total)
    {
        double change = amountPaid - total;
        int changeInt = (change)*100;

        std::cout << "\nTotal Change: " << change << std::endl;
        std::cout << "\n----------------------------------------------------------" << std::endl;

        std::map<int, std::vector<int>> memo;
        std::vector<int> *temp = calculateChange(changeInt, &memo);

        std::cout << "\nDispensing Change...\n";
        for (auto it = (*temp).begin(); it != (*temp).end(); it++)
        {
            double temp = (double)*it;
            temp = temp / 100;
            std::cout << "$" << temp << std::endl;
        }
    }
    else
    {

        std::cout << "Change: 0.00" << std::endl;
    }
}

int Cafe::validInput(std::string errorMessage)
{
    double input;
    if (!(std::cin >> input))
    {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << errorMessage << std::endl;
        std::cin.clear();
        return input = 0;
    }
    else if (input < 0 || (input - (int)input) > 0)
    {
        std::cout << errorMessage << std::endl;
        return input = 0;
    }
    else
    {
        return input;
    }
}
