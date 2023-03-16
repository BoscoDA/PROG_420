#pragma once 
#include <string> 
#include <iostream> 
class Card 
{ 
public: 
    Card(std::string suit, std::string rank, int value); 
    Card(const Card &) 
    { 
        std::cout << "Copied Card" << std::endl; 
    }

    std::string GetSuit() { return Suit; } 
    std::string GetRank() { return Rank; } 
    int GetNumValue() { return NumValue; } 
    void SetNumValue(int val) { NumValue = val; } 
    void DisplayCard(); 
    int True_Num_Value;
 
private: 
    std::string Suit; 
    std::string Rank; 
    int NumValue;
}; 