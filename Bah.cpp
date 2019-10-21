#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int; 

void PrintIntro();
FText GetValidGuess();
void PlayGame();
void PrintGameSummary();
bool bAskToPlayAgain();

FBullCowGame BCGame;

int main()
{
	bool bWantsToPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bWantsToPlayAgain = bAskToPlayAgain();
	} 
	while (bWantsToPlayAgain);
	return 0;
}

void PrintIntro()
{
	std::cout << " _           _ _                     _ " << std::endl;
	std::cout << "| |         | | |                   | |" << std::endl;
	std::cout << "| |__  _   _| | |___  __ _ _ __   __| | ___ _____      _____ " << std::endl;
	std::cout << "| '_ \\| | | | | / __|/ _` | '_ \\ / _` |/ __/ _ \\ \\ /\\ / / __|" << std::endl;
	std::cout << "| |_) | |_| | | \\__ \\ (_| | | | | (_| | (_| (_) \\ V  V /\\__ \\" << std::endl;
	std::cout << "|_.__/ \\__,_|_|_|___/\\__,_|_| |_|\\__,_|\\___\\___/ \\_/\\_/ |___/" << std::endl;

	std::cout << "\n\nWelcome to Bulls and Cows!" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter word without repeating any letters?" << std::endl;
	std::cout << std::endl;
	return;
}

FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do { 
	int32 CurrentTry = BCGame.GetCurrentTry();
	std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
	std::cout << ". Enter your guess: ";
	std::getline(std::cin, Guess);

	Status = BCGame.CheckGuessValidity(Guess);

		switch (Status)
		{
		case EGuessStatus::Wrong_Word_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		case EGuessStatus::Not_An_Isogram:
			std::cout << "Please enter a word without repeating any letters.\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter ALL letters in lowercase.\n\n";
			break;
		default:
			// assume guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK);
	return Guess;
}

void PlayGame()
{
	BCGame.Reset();
	
	int32 MaxTries = BCGame.GetMaxTries();
	// loop through the guesses while game
	// ISN'T won and tries are still remaining
	while (!BCGame.bIsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << ". Cows: " << BullCowCount.Cows << "\n\n";
	};

	PrintGameSummary();
	return;
}

void PrintGameSummary()
{
	if (BCGame.bIsGameWon())
	{
		std::cout << "CONGRATULATIONS! - YOU WON THE GAME!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n\n";
	}
	return;
}

bool bAskToPlayAgain()
{
	FText Response = "";
	std::cout << "Do you want to play again with the same hidden word (y/n) ";
	std::getline(std::cin, Response);
	std::cout << std::endl;

	if (Response != "y")
	{
		std::cout << "Please play again next time :)" << std::endl;
	}

	return (Response[0] == 'y') || (Response[0] == 'Y');
}