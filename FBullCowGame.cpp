#pragma once
#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::bIsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{ 
	TMap <int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 5}, {5, 7}, {6, 10}, {7, 15} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HiddenWord = "isogram";
	MyHiddenWord = HiddenWord;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!bIsIsogram(Guess)) // If Guess isn't isogram
	{
		return EGuessStatus::Not_An_Isogram;
	}
	else if (!bIsLowercase(Guess)) // If Guess isn't all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())  // If Guess length is wrong
	{
		return EGuessStatus::Wrong_Word_Length;
	}
	else 
	{
		return EGuessStatus::OK; 
	}
	
	// Then Give an error
	 // else 
	// return Ok
	 
	return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();
	
	// loops through letters typed
	for (int32 MHWChar = 0; MHWChar < HiddenWordLength; MHWChar++)
	{
		for (int32 GChar = 0; GChar < HiddenWordLength; GChar++)
		{
			if(Guess[GChar] == MyHiddenWord[MHWChar])
			{
				if (MHWChar == GChar)
				{
					BullCowCount.Bulls++; // increment Bulls
				}
			   else
				{
				BullCowCount.Cows++; // Increment cows
				}
			}
		}
	}
	if (BullCowCount.Bulls == HiddenWordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::bIsIsogram(FString Word) const
{
	// treat 0 and 1 letter words as isograms

	if (Word.length() <= 1) { return true; }
	TMap<char, bool> LetterSeen; // setup map
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); // handle mixed case
		// loop through all the letters in the word
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false; // we do not have an isogram
		}
		else // otherwise
		{
			LetterSeen[Letter] = true;// Add letter to the map as seen 
		}
	}
	return true; // in cases when /0 is returned
}

bool FBullCowGame::bIsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower (Letter)) // if letter not lowercase
		{
			return false;
		}
		
	}
	return true;
}