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
    void Determine_Valid_Cards(std::string led_suit);
    bool validCard(Card *card);
    int Rate_Hand(std::string trump_suit, std::string sister_suit);
    inline std::string GetName() { return Name; }
    Card *PlayCard(int index);
    int ChooseCard(std::string led_suit, std::vector<Card*> in_play);
    void DiscardHand();
    int Score = 0;

private:
    std::vector<Card *> Hand;
    std::vector<Card *> Valid_Cards;
    std::string Name;
};