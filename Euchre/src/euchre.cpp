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

    current_deck = new Deck();
}

void Euchre::GameLoop(){

        Setup();
        Bid();

        if(trump_suit!=""){
            for(int i = 0; i < 5; i++)
            {
                ScoreTrick(Trick());
            }

            for(auto p : players)
            {
                std::cout << p->GetName() << " score: " << p->Score << std::endl;
            }
        }

        ScoreHand();
    
}

void Euchre::Setup(){
    // Shuffle Deck
    current_deck->ShuffleDeck();

    // Deal cards: 3 cards then 2 cards, 5 total
    for (auto p : players)
    {
        p->SetHand(current_deck->DealCard());
        p->SetHand(current_deck->DealCard());
        p->SetHand(current_deck->DealCard());
    }

    for(auto p : players)
    {
        p->SetHand(current_deck->DealCard());
        p->SetHand(current_deck->DealCard());
    }
}

void Euchre::Bid(){
    Card *trump = current_deck->DealCard();
    std::cout << "Bidding on trump: " << trump->GetSuit() <<std::endl;

    for(int i = 0; i < 4; i++)
    {
        char response;
        std::cout<< "\n" <<players[i]->GetName() << " call trump? y/n" <<std::endl;
        std::cin >> response;

         while(response != 'y' && response != 'n' && response != 'Y' && response != 'N')
         {
             std::cout << "That is not a valid input!" << std::endl;
             std::cout<< players[i]->GetName() << " call trump? y/n" <<std::endl;
             std::cin >> response;
         }

        if(response == 'y' || response == 'Y')
        {
            std::cout << "Trump Called!" << std::endl;
            trump_suit = trump->GetSuit();

            if(i == 0 || i == 2){
                trump_team = 1;
            }
            else{
                trump_team = 2;
            }
            break;
        }
        else
        {
            std::cout << players[i]->GetName() << " passed." << std::endl;
        }
    }

    
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

std::vector<Card*> Euchre::Trick(){
    std::vector<Card*> trickCards;
    Card *temp;

    for(int i = 0; i < 4; i++)
    {
        std::cout << "-------------------------------------------------------------------------------------------------" <<std::endl;
        // Display cards already played
        std::cout << "Cards played: [";
        for(auto cards : trickCards){
            cards->DisplayCard();
            std::cout << ", ";
        }
        std::cout << "]\n" << std::endl;

        int tempPlayerIndex = ((firstPlayer + i)%4); 
        std::cout << players[tempPlayerIndex]->GetName() <<std::endl;
        players[tempPlayerIndex]->DisplayHand();
        int card = players[tempPlayerIndex]->ChooseCard(led_suit);

        temp = players[tempPlayerIndex]->PlayCard(card);
        trickCards.push_back(temp);

        if(i == 0){
            led_suit = temp->GetSuit();
        }
        std::cout << players[tempPlayerIndex]->GetName() << " plays the ";
        temp->DisplayCard();
        std::cout << "" <<std::endl;
        std::cout << "-------------------------------------------------------------------------------------------------" <<std::endl;

    }
    return trickCards;
}

void Euchre::ScoreTrick(std::vector<Card*> playedCards){
    Card *WinningCard = playedCards[0];
    int winIndex = firstPlayer;

    for(int i = 0; i < 4; i++)
    {
        int temp = playedCards[i]->GetNumValue();

        if(playedCards[i]->GetSuit() == trump_suit){
            int temp = playedCards[i]->GetNumValue();
            if(playedCards[i]->GetRank() == "Jack"){
                playedCards[i]->SetNumValue(playedCards[i]->GetNumValue()+26);
            }
            else{
                playedCards[i]->SetNumValue(temp+20);
            }
        }

        else if(playedCards[i]->GetRank() == "Jack" && playedCards[i]->GetSuit() == sister_suit)
        {
            playedCards[i]->SetNumValue(temp+25);
        }

        else if(playedCards[i]->GetSuit() == led_suit)
        {
            playedCards[i]->SetNumValue(temp+10);
        }
    }

    for(int i = 1; i < 4; i++)
    {
        std::cout << WinningCard->GetNumValue() << " > " << playedCards[i]->GetNumValue() << std::endl;
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
            team1_score++;
        }
        else{
            team2_score++;
            team1_score--;
        }
    }

    if(trump_team == 2)
    {
        if(team2_tricks_won >= 3){
            team2_score++;
        }
        else{
            team1_score++;
            team2_score--;
        }
    }

    for(auto p : players){
        p->Score = 0;
    }
}