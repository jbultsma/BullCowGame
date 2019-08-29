/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on mastermind */

#pragma once

#include "FBullCowGame.h"
#include <map>
#include <time.h>

// To make syntax Unreal Engine friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap <int32, int32> WordLengthToMaxTries{ {3,6}, {4,8}, {5,10}, {6,12} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

FString FBullCowGame::GetHiddenWord()
{
	FString HIDDEN_WORD[] = { "planet", "cat", "brick", "house", "basket", "mask", "video", "dog", "tea", "dream", "radio", "crypt", "guts", "trophy", "night" };
	srand(time(NULL));
	MyHiddenWord = HIDDEN_WORD[rand() % 19];

	return MyHiddenWord;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // if the guess isnt an isogram
	{
		return EGuessStatus::Not_Isogram;
	}

	else if (!IsLowercase(Guess)) // if the guess isnt all lowercase 
	{
		return EGuessStatus::Not_Lowercase;
	}

	else if (Guess.length() != GetHiddenWordLength()) // If the guess length is wrong
	{
		return EGuessStatus::Incorrect_Number_Of_Letters;
	}

	else
	{
		return EGuessStatus::OK;
	}
}


// Receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// Loop through all leters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{
		// Compare letters against guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{
			if (Guess[GChar] == MyHiddenWord[MHWChar]) // if they match then
			{
				if (MHWChar == GChar) // if they're in the same place 
				{
					BullCowCount.Bulls++;	// incriment bulls
				}
				else // if they're not in the same place 
				{
					BullCowCount.Cows++;	// Must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

// loop that compares the guess to the alphabet
bool FBullCowGame::IsIsogram(FString Word) const
{

	// Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// setup map
	TMap <char, bool> LetterSeen;

	for (auto Letter : Word)	// for all letters of the word
	{
		Letter = tolower(Letter);	// handle mixed case

		//loop through all letters of the word
		if (LetterSeen[Letter])	// if letter is in the map
		{
			return false;	// We do NOT have an Isogram
		}

		else
		{
			LetterSeen[Letter] = true;	// add letter to map as seen
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (isupper(Letter))
		{
			return false;
		}
	}

	return true;
}
