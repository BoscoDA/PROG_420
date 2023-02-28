#include "euchre.h"
Euchre::Euchre()
{
    Bot1 = Player("Bot1");
    Bot2 = Player("Bot2");
    Bot3 = Player("Bot3");
    Bot4 = Player("Bot4");

    CurrentDeck = new Deck();
    
}

void Euchre::GameLoop()
{
    Setup();
}

void Euchre::Setup()
{
    CurrentDeck->ShuffleDeck();

    Bot1.SetHand(CurrentDeck->DealCard());
    Bot1.SetHand(CurrentDeck->DealCard());
    Bot1.SetHand(CurrentDeck->DealCard());

    Bot2.SetHand(CurrentDeck->DealCard());
    Bot2.SetHand(CurrentDeck->DealCard());
    Bot2.SetHand(CurrentDeck->DealCard());

    Bot3.SetHand(CurrentDeck->DealCard());
    Bot3.SetHand(CurrentDeck->DealCard());
    Bot3.SetHand(CurrentDeck->DealCard());

    Bot4.SetHand(CurrentDeck->DealCard());
    Bot4.SetHand(CurrentDeck->DealCard());
    Bot4.SetHand(CurrentDeck->DealCard());

    Bot1.SetHand(CurrentDeck->DealCard());
    Bot1.SetHand(CurrentDeck->DealCard());

    Bot2.SetHand(CurrentDeck->DealCard());
    Bot2.SetHand(CurrentDeck->DealCard());

    Bot3.SetHand(CurrentDeck->DealCard());
    Bot3.SetHand(CurrentDeck->DealCard());

    Bot4.SetHand(CurrentDeck->DealCard());
    Bot4.SetHand(CurrentDeck->DealCard());

    CurrentDeck->DisplayDeck();

}
