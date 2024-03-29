#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "deck.h"
#include "card.h"
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
        delete current_deck;
    }
    void GameLoop();
    void Setup();
    void Bid();
    void ScoreTrick();
    void ScoreHand();
    std::vector<Card*> Trick();
    void ScoreTrick(std::vector<Card*> playedCards);
    void PlayHand();
    void UpdateCardValues();
    void DetermineSisterSuit();
    void ResetRound();
    void EndGame();

private:
    Player bot1 = Player("NULL");
    Player bot2 = Player("NULL");
    Player bot3 = Player("NULL");
    Player bot4 = Player("NULL");
    Deck *current_deck;
    std::vector<Player*> players;
    std::string trump_suit = "";
    std::string sister_suit = "";
    std::string led_suit = "";
    int trump_team;
    int team1_score = 0;
    int team2_score = 0;
    int firstPlayer = 0;
    int dealer = 3;
};
