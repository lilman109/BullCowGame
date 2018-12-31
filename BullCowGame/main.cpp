//
//  main.cpp
//  BullCowGame
//
//  Created by Akira Yoshida on 2018/06/17.
//  Copyright © 2018年 Akira Yoshida. All rights reserved.
//

#include <iostream>

#include "BullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
std::string GetValidGuess();
bool AskToPlayAgain();

BullCowGame BCGame; // initiate a new game

// the entry point of the game
int main()
{
    bool playAgain = false;

    do
    {
        // print introduction of game
        PrintIntro();
        
        // play game
        PlayGame();
        
        // ask to play again
        playAgain = AskToPlayAgain();
    }
    while (playAgain);

    return 0;
}

// print the introduction of the game
void PrintIntro()
{
    const int32 WORD_LENGTH = BCGame.getHiddenWordLength();
    
    std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " <<  WORD_LENGTH << " letter isogram I'm thinking of?\n";
    std::cout << std::endl;
    
    return;
}

// get guess and print back
void PlayGame()
{
    BCGame.reset();

    int32 maxTry = BCGame.getMaxTry();

    // loop while game is not won and current try is <= max try
    while (!BCGame.isGameWon() && BCGame.getCurrentTry() <= maxTry)
    {
        FText printGuess = GetValidGuess(); // TODO: make loop checking valid guess
        
        // submit valid guess to the game
        BullCowCount bullCowCount = BCGame.submitValidGuess(printGuess);
        
        // print number of bulls and cows
        std::cout << "Bulls = " << bullCowCount.bulls;
        std::cout << " Cows = " << bullCowCount.cows << "\n\n";
    }
    // TODO: summarize game
    BCGame.printGameSummary();
    return;
}

// loop until valid guess
FText GetValidGuess()
{
    FText guess = "";
    GuessStatus status = GuessStatus::INVALID_STATUS;
    do
    {
        int32 currentTry = BCGame.getCurrentTry();

        std::cout << "Try " << currentTry << " of " << BCGame.getMaxTry() << ". Enter Your Guess: ";
        std::getline(std::cin, guess);

        status = BCGame.isGuessValid(guess);
        switch(status)
        {
            case GuessStatus::NOT_ISOGRAM:
                std::cout << "Please enter a word without repeating letters.\n\n";
                break;

            case GuessStatus::WORD_LENGTH:
                std::cout << "Please enter a " << BCGame.getHiddenWordLength() << " letter word.\n\n";
                break;

            case GuessStatus::NOT_LOWERCASE:
                std::cout << "Please enter lowercase words.\n\n";
                break;

            default:
                break;
        }
    }while (status != GuessStatus::OK);
    
    return guess;
}

// ask to play again
bool AskToPlayAgain()
{
    FText response = "";
    
    std::cout << "Would you like to play again? (y/n) ";
    getline(std::cin, response);
    
    return (response[0] == 'y') || (response[0] == 'Y');
}
