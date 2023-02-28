#include "deck.h" 
#include <iostream> 
#include <algorithm> 
#include <random> 
#include <chrono> 
#include <vector>
std::string Rank[] = {"Ace", "Eight", "Nine", "Ten", "Jack", "Queen", "King"}; 
std::string Suit[] = {"Clubs", "Diamonds", "Hearts", "Spades"}; 
int NumVal[] = {14, 8, 9, 10, 11, 12, 13}; 
 
// Creates a vector of 28 cards using the Rank, Suit and NumVal Arrays 
Deck::Deck() 
{ 
    for (int i = 0; i < 7; i++) 
    { 
        for (int j = 0; j < 4; j++) 
        { 
            deck.push_back(new Card(Suit[j], Rank[i], NumVal[i])); 
        } 
    } 
} 
 
// Loops through each card stored in the deck vector and calls its DisplayCard() function. 
void Deck::DisplayDeck() 
{ 
    for (auto it = deck.begin(); it != deck.end(); it++) 
    { 
        Card *temp = *it; 
        temp->DisplayCard(); 
    } 
} 
 
// Uses the algorithm, random and chrono libraries to randomly shuffle the vector being used to store the deck. 
void Deck::ShuffleDeck() 
{ 
    std::random_shuffle(deck.begin(), deck.end()); 
 
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); 
    shuffle(deck.begin(), deck.end(), std::default_random_engine(seed)); 
} 
 
// Gets the card stored at the last index of the vector and returns a pointer to it. 
Card *Deck::DealCard() 
{ 
    Card *temp = *deck.rbegin(); 
    deck.pop_back(); 
    return temp; 
    delete temp; 
} 

int Deck::DeckCap()
{
    return deck.capacity();
}