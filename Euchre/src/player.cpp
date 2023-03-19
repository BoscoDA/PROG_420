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

int Player::ChooseCard(std::string led_suit, std::vector<Card*> in_play){
    bool valid_card = false;
    int choice = 7;
    Card *best = new Card("TEMP", "TEMP", 0);

    int output = 0;

    Determine_Valid_Cards(led_suit);

    //Determine best card in play
    for(auto c:in_play){
        if(best->GetNumValue()<c->GetNumValue()){
            best = c;
        }
    }

    //Determine players best valid card
    for(int i = 0; i < Valid_Cards.size(); i++){
        if(choice == 7){
            choice = i;
        }
        else if(Valid_Cards[choice]->GetNumValue() < Valid_Cards[i]->GetNumValue()){
            choice = i;
        }
    }

    //If player's best card does not beat best card in play, return lowest value valid card
    if(Valid_Cards[choice]->GetNumValue() < best->GetNumValue()){
        for(int i = 0; i < Valid_Cards.size(); i++){
            if(choice == 7){
                choice = i;
            }
            else if(Valid_Cards[choice]->GetNumValue() > Valid_Cards[i]->GetNumValue()){
            choice = i;
            }
        }
    }

    //Find card in hand
    for(int i = 0; i < Hand.size(); i++){
        if(Hand[i]->GetNumValue() == Valid_Cards[choice]->GetNumValue()){
            output = i;
        }
    }

    return output;
}

void Player::Determine_Valid_Cards(std::string led_suit){
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

int Player::Rate_Hand(std::string trump_suit, std::string sister_suit){
    int score = 0;

    for(int i = 0; i < 4; i++){
        if(Hand[i]->GetSuit() == trump_suit){
            
            if(Hand[i]->GetRank() == "Jack"){
                score += 4;
            }
            else if(Hand[i]->GetRank() == "Ace" || Hand[i]->GetRank() == "King" || Hand[i]->GetRank() == "Queen"){
                score += 3;
            }
            else{
                score += 2;
            }
        }
        else if(Hand[i]->GetSuit() == sister_suit && Hand[i]->GetRank() == "Jack"){
            score += 4;
        }
        else if(Hand[i]->GetRank() == "Ace")
        {
            score += 2;
        }
        else if(Hand[i]->GetRank() == "King" || Hand[i]->GetRank() == "Queen" || Hand[i]->GetRank() == "Jack"){
            score += 1;
        }
    }

    return score;
}

void Player::DiscardHand(){
    for (auto d : Hand){
        delete d;
    }

    Hand.clear();
}