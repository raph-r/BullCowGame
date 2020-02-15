// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    this->Isograms = this->GetValidWords(Words);
    this->SetupGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (this->bGameOver)
    {
        ClearScreen();
        this->SetupGame();
    }
    else
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    this->HiddenWord = this->Isograms[FMath::RandRange(0, this->Isograms.Num() - 1)];
    this->Lives = this->HiddenWord.Len();
    this->bGameOver = false;
    this->WelcomeMsg();
}

bool UBullCowCartridge::IsInputLenEqualToHiddenWordLen(const FString& Input) const
{
    return Input.Len() == this->HiddenWord.Len();
}

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int32 Index = 0; Index < Word.Len() - 1; Index++)
    {
        for (int32 IndexToCompare = Index + 1; IndexToCompare < Word.Len(); IndexToCompare++)
        {
            if (Word[Index] == Word[IndexToCompare])
            {
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::WelcomeMsg() const
{
    PrintLine(TEXT("Welcome to Bull Cow Game!!!"));
    PrintLine(TEXT("Guess the %i letter word!"), this->HiddenWord.Len());
    PrintLine(TEXT("You have %i lives!"), this->Lives);
    PrintLine(TEXT("Type in your guess and press Enter..."));
}

void UBullCowCartridge::EndGame()
{
    this->bGameOver = true;
    PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
    PrintLine(TEXT("Press Enter to play again..."));
}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess == this->HiddenWord)
    {
        PrintLine(TEXT("You Win!!!"));
        this->EndGame();
        return;
    }

    if (--this->Lives < 1)
    {
        PrintLine(TEXT("You have no lives left!!!"));
        this->EndGame();
        return;
    }

    this->BullCowCounter.Update(Guess, this->HiddenWord);
    PrintLine(TEXT("You have %i Bulls and %i Cows!"), this->BullCowCounter.BullCount, this->BullCowCounter.CowCount);
    PrintLine(TEXT("Try guessing again, you have %i lives\nremaining!"), this->Lives);

    if (!this->IsInputLenEqualToHiddenWordLen(Guess))
    {
        PrintLine(TEXT("The hidden word is %i letter long!"), this->HiddenWord.Len());
        return;
    }

    if (!this->IsIsogram(Guess))
    {
        PrintLine(TEXT("Guess is not a Isogram!"));
    }

}

TArray<FString> UBullCowCartridge::GetValidWords(const TArray<FString>& WordList) const
{
    TArray<FString> ValidWords;
    for (const auto& Word : WordList)
    {
        if (Word.Len() >= 4 && Word.Len() <= 8 && this->IsIsogram(Word)) 
        {
            ValidWords.Emplace(Word);
        }
    }
    return ValidWords;
}
