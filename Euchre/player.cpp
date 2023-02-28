#include "player.h"

Player::Player(std::string name)
{
    Name = name;
}

void Player::DisplayHand()
{
    for (auto it = Hand.begin(); it != Hand.end(); it++)
    {
        Card *temp = *it;
        temp->DisplayCard();
    }
}
void Player::SetHand(Card *card)
{
    Hand.push_back(card);
}