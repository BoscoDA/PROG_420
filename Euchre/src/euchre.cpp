#include "euchre.h"
#include <vector>

Euchre::Euchre(){
    bot1 = Player("Bot1");
    bot2 = Player("Bot2");
    bot3 = Player("Bot3");
    bot4 = Player("Bot4");
    players.push_back(&bot1);
    players.push_back(&bot2);
    players.push_back(&bot3);
    players.push_back(&bot4);
}

void Euchre::GameLoop(){

    char temp;
    while(team1_score != 10 && team2_score != 10)
    {
        Setup();
        Bid();

        if(trump_suit!=""){
            if(trump_team == 1){

                std::cout << "\nTeam 1: Makers\nTeam 2: Defenders" << std::endl;
            }
            else{
                std::cout << "\nTeam 1: Defenders\nTeam 2: Makers" << std::endl;
            }

            PlayHand();

            std::cout << "\nSCORE ------------------------------------------------------------------------------" << std::endl;
            std::cout << "Team 1: " << team1_score << std::endl;
            std::cout << "Team 2: " << team2_score << std::endl;
            std::cout << "------------------------------------------------------------------------------------\n" << std::endl;
        }

        ResetRound();
    }

    EndGame();
}

void Euchre::Setup(){
    current_deck = new Deck();
    // Shuffle Deck
    for(int i = 0; i < 5; i++){
        current_deck->ShuffleDeck();
    }
    

    // Deal cards: 3 cards then 2 cards, 5 total
    for (int i = 0; i<4; i++)
    {
        int tempPlayerIndex = ((dealer + 1 + i)%4); 
        players[tempPlayerIndex]->SetHand(current_deck->DealCard());
        players[tempPlayerIndex]->SetHand(current_deck->DealCard());
        players[tempPlayerIndex]->SetHand(current_deck->DealCard());
    }

    for(int i = 0; i<4; i++)
    {
        int tempPlayerIndex = ((dealer + 1 + i)%4); 
        players[tempPlayerIndex]->SetHand(current_deck->DealCard());
        players[tempPlayerIndex]->SetHand(current_deck->DealCard());
    }

    
}

void Euchre::DetermineSisterSuit(){
    if(trump_suit == "Diamonds"){
        sister_suit = "Hearts";
    }

    else if(trump_suit == "Hearts")
    {
        sister_suit = "Diamonds";
    }

    else if(trump_suit == "Spades"){
        sister_suit = "Clubs";
    }

    else if(trump_suit == "Clubs")
    {
        sister_suit = "Spades";
    }
}

void Euchre::Bid(){
    Card *trump = current_deck->DealCard();
    DetermineSisterSuit();
    std::cout << "\nBID --------------------------------------------------------------------------------" << std::endl;
    std::cout << "\nBidding on trump: ";
    trump->DisplayCard();
    std::cout << "\n";

    for(int i =0; i < 4; i++){
        int tempPlayerIndex = ((dealer + 1 + i)%4); 
        std::cout<< "\n" <<players[tempPlayerIndex]->GetName() << " | ";

        double temp = players[tempPlayerIndex]->Rate_Hand(trump->GetSuit(), sister_suit);
        
        if(temp >= 0.25){
            std::cout << "Order it up!" << std::endl;
            trump_suit = trump->GetSuit();
            
            if(tempPlayerIndex == 0 || tempPlayerIndex == 2){
                trump_team = 1;
            }
            else{
                trump_team = 2;
            }

            break;
        }
        else{
            std::cout << "Pass." << std::endl;
        }
    }

    std::cout << "\n------------------------------------------------------------------------------------" << std::endl;

    DetermineSisterSuit();
    
     //set new values for each of the cards
    for(auto p : players){
        for(int i = 0; i <= 4; i++){
            int temp = p->GetHand()[i]->GetNumValue();
            if(p->GetHand()[i]->GetSuit() == trump_suit){
                int temp = p->GetHand()[i]->GetNumValue();
                if(p->GetHand()[i]->GetRank() == "Jack"){
                    p->GetHand()[i]->True_Num_Value = temp + 26;
                }
                else{
                   p->GetHand()[i]->True_Num_Value = temp + 20 ;
                }
            }

            else if(p->GetHand()[i]->GetRank() == "Jack" && p->GetHand()[i]->GetSuit() == sister_suit){
                p->GetHand()[i]->True_Num_Value = temp + 25;
            }
            else if(p->GetHand()[i]->GetSuit() == led_suit){
                p->GetHand()[i]->True_Num_Value = temp +10;
            }
            else{
                p->GetHand()[i]->True_Num_Value = temp;
            }
        }
    }
}

std::vector<Card*> Euchre::Trick(){
    std::vector<Card*> trickCards;
    Card *temp;

    
    for(int i = 0; i < 4; i++)
    {
        int tempPlayerIndex = ((firstPlayer + i)%4);

        int card = players[tempPlayerIndex]->ChooseCard(led_suit, trickCards);

        if(i == 0){
            led_suit = players[tempPlayerIndex]->GetHand()[card]->GetSuit();
            UpdateCardValues();
        }

        temp = players[tempPlayerIndex]->PlayCard(card);
        trickCards.push_back(temp);

        std::cout << players[tempPlayerIndex]->GetName() << " plays the ";
        temp->DisplayCard();
        std::cout << "" <<std::endl;
    }

    std::cout << "\nCards played: [";
    for(auto cards : trickCards){
        cards->DisplayCard();
        std::cout << ", ";
    }
    std::cout << "]\n" << std::endl;

    return trickCards;
}

void Euchre::ScoreTrick(std::vector<Card*> playedCards){
    Card *WinningCard = playedCards[0];
    int winIndex = firstPlayer;

    for(int i = 1; i < 4; i++)
    {
        if(playedCards[i]->GetNumValue() > WinningCard->GetNumValue())
        {
            WinningCard = playedCards[i];
            winIndex = (firstPlayer+i)%4;
        }
    }

    players[winIndex]->Score++;
    std::cout << players[winIndex]->GetName() << " won the trick!"<<std::endl;
    firstPlayer = winIndex;
}

void Euchre::ScoreHand(){

    int team1_tricks_won = players[0]->Score + players[2]->Score;
    int team2_tricks_won = players[1]->Score + players[3]->Score;
    if(trump_team == 1)
    {
        if(team1_tricks_won >= 3){
            std::cout<<"\nTeam 1 has won the hand!" << std::endl;
            team1_score++;
        }
        else{
            std::cout<<"\nTeam 2 has won the hand!" << std::endl;
            team2_score++;
            if(team1_score > 0){
                team1_score--;
            }
            
        }
    }

    if(trump_team == 2)
    {
        if(team2_tricks_won >= 3){
            std::cout<<"Team 2 has won the hand!" << std::endl;
            team2_score++;
        }
        else{
            std::cout<<"Team 1 has won the hand!" << std::endl;
            team1_score++;
            if(team2_score>0){
                team2_score--;
            }
            
        }
    }
}

void Euchre::PlayHand(){
    for(int i = 0; i < 5; i++){
            std::cout << "\nTrick " << i+1 << " ----------------------------------------------------------------------------"<<std::endl;
            ScoreTrick(Trick());
            std::cout << "------------------------------------------------------------------------------------" <<std::endl;
        }

    ScoreHand();

    if(dealer < 4){ dealer++; }
    else{ dealer = 0; }
}

void Euchre::UpdateCardValues(){
    
    //set new values for each of the cards
    for(auto p : players){
        for(int i = 0; i < p->GetHand().size(); i++){
            int temp = p->GetHand()[i]->GetNumValue();

            if(p->GetHand()[i]->GetSuit() == led_suit){
                p->GetHand()[i]->True_Num_Value = temp +10;
            }
        }
    }
}

void Euchre::ResetRound(){
    for(auto p : players){
        p->DiscardHand();
    }

    current_deck->GetDeck().clear();

    trump_suit = "";
    sister_suit = "";
}

void Euchre::EndGame(){
    if(team1_score == 10){
        std::cout << "\nTeam 1 won the game!" << std::endl;
    }
    else{
        std::cout << "\nTeam 2 won the game!" << std::endl;
    }
}