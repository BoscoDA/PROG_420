#include "player.h"

Player::Player(std::string name){
    Name = name;
}

void Player::DisplayHand(){
    std::cout << "Hand: [";
    for (auto it = Hand.begin(); it != Hand.end(); it++)
    {
        Card *temp = *it;
        temp->DisplayCard();
        std::cout << ", ";
    }
    std::cout << "]" << std::endl;
}

void Player::SetHand(Card *card){
    Hand.push_back(card);
}

Card *Player::PlayCard(int index){
    Card *temp = Hand[index];
    Hand.erase(Hand.begin()+index);
    return temp;
    delete temp;
}

int Player::ChooseCard(std::string led_suit){
    bool valid_card = false;
    int choice;
    DetermineValidCards(led_suit);

    while (!valid_card)
    {
        std::cout << "Enter the index of the card you would like to play: ";
        std::cin >> choice;
        std::cout << "" << std::endl;

        if(choice > Hand.size())
        {
            std::cout << "Not a valid choice!" << std::endl;
        }
        else if(!validCard(Hand[choice-1])){
            std::cout << "Not a valid choice!" << std::endl;
        }

        else{
            valid_card = true;
        }
    }

    return choice - 1;
}

void Player::DetermineValidCards(std::string led_suit){
    Valid_Cards.clear();

    for(auto c : Hand){
        if(c->GetSuit() == led_suit){
            Valid_Cards.push_back(c);
        }
    }

    if(Valid_Cards.size() == 0){
        Valid_Cards = Hand;
    }
}

bool Player::validCard(Card *card){

    for(auto c : Valid_Cards)
    {
        if(c == card){
            return true;
        }
    }

    return false;
}