/*	This is the console executable, that makes use of the BullCow class
	This acts as the view in a MVC patter, and is responsible for all user interaction.
	For game logic, see the FBullCowGame class.	*/

#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

	// to make syntax Unreal Engine friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();

FText GetValidGuess();
FText PrintBack();
FText Guess = "";
FText Response = "";

FBullCowGame BCGame; // Instantiate a new game, which is reused across plays


// The entry point for our application.
int main()
{
	std::cout << BCGame.GetCurrentTry();

	do
	{
		PrintIntro();
		PlayGame();
		AskToPlayAgain();
	} while ((Response[0] == 'y') || (Response[0] == 'Y'));

	return 0;
}


// Introduction to the game.
void PrintIntro()
{
	BCGame.GetHiddenWord();

	std::cout << "\n\nWelcome To Bulls and Cows, a word game.\n\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n\n\n";
}


// Main Game
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop for number of turns asking for guesses
	// While game is NOT won and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		GetValidGuess();

		// Submit Valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << " Cows = " << BullCowCount.Cows << std::endl;

		PrintBack();
	}

	PrintGameSummary();

	return;
}


// Ask's user if they want to play the game again or to exit the game.
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)? ";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}


// Loop continually until the user gives a valid guess
FText GetValidGuess()
{
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Incorrect_Number_Of_Letters:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;

		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n\n";
			break;

		case EGuessStatus::Not_Lowercase:
			std::cout << "Please only use lowercase letters.\n\n";
			break;

		default:
			//assuming guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // Keep looping untill we get valid input
	return Guess;
}


// Function printing that guess back to the user.
FText PrintBack()
{
	std::cout << std::endl;
	return Guess;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "Congratulations, you have won the game!\n\n";
	}

	else
	{
		std::cout << "Better luck next time.\n\n";
	}
}
