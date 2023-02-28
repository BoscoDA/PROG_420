#pragma once
#include <iostream>
#include "deck.h"
#include "player.h"

class Euchre
{
public:
    Euchre();
    Euchre(const Euchre &)
    {
        // std::cout << "Copied Game" << std::endl;
    }
    ~Euchre()
    {
        delete CurrentDeck;
    }
    void Setup();
    void GameLoop();

private:
    Player Bot1 = Player("NULL");
    Player Bot2 = Player("NULL");
    Player Bot3 = Player("NULL");
    Player Bot4 = Player("NULL");
    Deck *CurrentDeck;
};
