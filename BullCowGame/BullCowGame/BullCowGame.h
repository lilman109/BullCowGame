//
//  BullCowGame.h
//  BullCowGame
//
//  Created by Akira Yoshida on 2018/06/23.
//  Copyright © 2018年 Akira Yoshida. All rights reserved.
//

#ifndef BullCowGame_h
#define BullCowGame_h

#include <string>

using FString = std::string;
using int32 = int;

struct BullCowCount
{
    int32 bulls = 0;
    int32 cows = 0;
};

enum class GuessStatus
{
    INVALID_STATUS,
    OK,
    NOT_ISOGRAM,
    WORD_LENGTH,
    NOT_LOWERCASE
};

class BullCowGame
{
public:
    // constructor
    BullCowGame();

    int32 getMaxTry() const;
    int32 getCurrentTry() const;
    int32 getHiddenWordLength() const;

    GuessStatus isGuessValid(FString) const;
    // provide a method to count bulls and cows and increase turn count assuming valid guess
    bool isGameWon() const;
    void printGameSummary();

    void reset(); //TODO: make a more rich return value
    BullCowCount submitValidGuess(FString);

private:
    int32 myCurrentTry;
    FString myHiddenWord;
    bool gameIsWon;

    bool isIsogram(FString) const;
    bool isLowercase(FString) const;
};

#endif /* BullCowGame_h */
