#pragma once
#include <vector>
#include "card.h"
#include <string>

class Player
{
public:
    Player(std::string name);
    Player(const Player &)
    {
        // std::cout << "Copied Player" << std::endl;
    }
    ~Player()
    {
        for (auto d : Hand)
        {
            // std::cout << "Deleted Player" << std::endl;
            delete d;
        }
    }
    std::vector<Card *> GetHand() { return this->Hand; }
    void SetHand(Card *card);
    void DisplayHand();
    inline std::string GetName() { return Name; }

private:
    std::vector<Card *> Hand;
    std::string Name;
};