//
//  BullCowGame.cpp
//  BullCowGame
//
//  Created by Akira Yoshida on 2018/06/23.
//  Copyright © 2018年 Akira Yoshida. All rights reserved.
//

#include <iostream>

#include "BullCowGame.h"

#include <map>
#define TMAP std::map

using FString = std::string;
using int32 = int;

BullCowGame::BullCowGame()
{
    this->reset();
}

void BullCowGame::reset()
{
    const FString HIDDEN_WORD = "donkey";
    myHiddenWord = HIDDEN_WORD;
    myCurrentTry = 1;
    gameIsWon = false;

    return;
}

// returns max try count
int32 BullCowGame::getMaxTry() const
{
    TMAP<int, int> wordLengthToMaxTries
    {
        { 3, 4  },
        { 4, 7  },
        { 5, 9  },
        { 6, 11 }
    };

    return wordLengthToMaxTries[myHiddenWord.length()];
}

// returns current try count
int32 BullCowGame::getCurrentTry() const
{
    return myCurrentTry;
}

// return hidden word length
int32 BullCowGame::getHiddenWordLength() const
{
    return myHiddenWord.length();
}

// checks if game is won or loss
bool BullCowGame::isGameWon() const
{
    return gameIsWon;
}

void BullCowGame::printGameSummary()
{
    // print game summary
    if (isGameWon())
    {
        std::cout << "WELL DONE - YOU WON!\n";
    }
    else
    {
        std::cout << "BETTER LUCK NEXT TIME....\n";
    }

    return;
}

bool BullCowGame::isIsogram(FString word) const
{
    // treat 0 and 1 letter words as isogram
    if (word.length() <= 1) { return true; }

    //setup map
    TMAP<char, bool> letterSeen;
    // loop through all the letters
    for (auto letter : word)
    {
        letter = tolower(letter);

        if (letterSeen[letter])         // if the letter is in the map
        {
            return false;               // it is not an isogram
        }
        else
        {
            letterSeen[letter] = true;  // add it to map
        }
    }

    return true;
}

bool BullCowGame::isLowercase(FString word) const
{
    TMAP<char, bool> lowercase;
    for (auto letter : word)
    {
        if (!islower(letter))
        {
            return false;
        }
    }
    return true;
}

GuessStatus BullCowGame::isGuessValid(FString guess) const
{
    // if guess isn't an isogram
    if (!isIsogram(guess))
    {
        return GuessStatus::NOT_ISOGRAM;
    }
    // if guess isn't all lowercase
    else if (!isLowercase(guess))
    {
        return GuessStatus::NOT_LOWERCASE;
    }
    // if guess isn't correct length
    else if (getHiddenWordLength() != guess.length())
    {
        return GuessStatus::WORD_LENGTH;
    }
    // otherwise
    else
    {
        return GuessStatus::OK;
    }
}

// receives a Valid guess and increments turn and return count
BullCowCount BullCowGame::submitValidGuess(FString guess)
{
    // increment try number
    myCurrentTry++;

    // setup a return variable
    BullCowCount bullCowCount;

    // loop through all letters
    int32 wordLength = myHiddenWord.length();
    for (int32 myHiddenWordCharacter = 0; myHiddenWordCharacter < wordLength; myHiddenWordCharacter++)
    {
        // compare letters against the hidden word
        for (int32 myHiddenGuessCharacter = 0; myHiddenGuessCharacter < wordLength; myHiddenGuessCharacter++)
        {
            // if they match
            if (myHiddenWord[myHiddenWordCharacter] == guess[myHiddenGuessCharacter])
            {
                if (myHiddenWordCharacter == myHiddenGuessCharacter)
                {
                    // increment bulls when they're in the right place
                    bullCowCount.bulls++;
                }
                else
                {
                    // increment cows when they're not
                    bullCowCount.cows++;
                }
            }
        }
    }

    if (bullCowCount.bulls == wordLength)
    {
        gameIsWon = true;
    }
    else
    {
        gameIsWon = false;
    }

    return bullCowCount;
}
