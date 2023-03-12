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
    void DetermineValidCards(std::string led_suit);
    bool validCard(Card *card);
    inline std::string GetName() { return Name; }
    Card *PlayCard(int index);
    int ChooseCard(std::string led_suit);
    int Score = 0;

private:
    std::vector<Card *> Hand;
    std::vector<Card *> Valid_Cards;
    std::string Name;
};