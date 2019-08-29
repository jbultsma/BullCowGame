/* The game logic (no view code or direct user interaction)
The game is a simple guess the word game based on mastermind */

#pragma once

#include <string>

// To make syntax more Unreal Engine friendly 
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Incorrect_Number_Of_Letters,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // Contructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;

	EGuessStatus CheckGuessValidity(FString) const;

	FBullCowCount SubmitValidGuess(FString);

	void Reset();
	FString GetHiddenWord();



	// ^^ please try to ignore the Private section and focus on the public section! ^^
private:
	// See constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

};
