/*This is the game logic and the code in this header file doesn't interact
with the user in any way. This game is a simple guess the word game and this
is the digital version of the old paper and pen game Bulls and Cows.*/

#pragma once
#include <string>

using FString = std::string;
using int32 = int;

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_An_Isogram,
	Wrong_Word_Length,
	Not_Lowercase,
};

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

class FBullCowGame
{
public:
	FBullCowGame();
	int32 GetCurrentTry() const;
	int32 GetMaxTries() const;
	int32 GetHiddenWordLength() const;
	EGuessStatus CheckGuessValidity(FString Guess) const;
	bool bIsGameWon() const;

	void Reset();
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
	bool bIsIsogram(FString) const;
	bool bIsLowercase(FString) const;
};