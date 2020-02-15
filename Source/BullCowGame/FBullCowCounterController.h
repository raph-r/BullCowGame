#pragma once
#include "CoreMinimal.h"

class FBullCowCounterController
{
    public:
    int32 BullCount = 0;
    int32 CowCount = 0;
    TArray<int32> IndexGuessAndHiddenWordWithBull;
    TArray<int32> IndexHiddenWordWithCow;
    void Update(const FString& Guess, const FString& HiddenWord)
    {
        // Execute in this sequence
        this->ResetAttr();
        this->UpdateBull(Guess, HiddenWord);
        this->UpdateCow(Guess, HiddenWord);
    }

    private:
    void UpdateBull(const FString& Guess, const FString& HiddenWord)
    {
        const int32& HiddenWordLen = HiddenWord.Len();

        for (int32 IndexGuess = 0; IndexGuess < Guess.Len(); IndexGuess++)
        {
            if (IndexGuess < HiddenWordLen && Guess[IndexGuess] == HiddenWord[IndexGuess])
            {
                this->BullCount++;
                this->IndexGuessAndHiddenWordWithBull.Emplace(IndexGuess);
            }
        }
    }

    void UpdateCow(const FString& Guess, const FString& HiddenWord)
    {
        for (int32 IndexGuess = 0; IndexGuess < Guess.Len(); IndexGuess++)
        {
            if(!this->IndexGuessAndHiddenWordWithBull.Contains(IndexGuess))
            {
                for (int32 IndexHiddenWord = 0; IndexHiddenWord < HiddenWord.Len(); IndexHiddenWord++)
                {
                    if(
                        !this->IndexGuessAndHiddenWordWithBull.Contains(IndexHiddenWord) 
                        && !this->IndexHiddenWordWithCow.Contains(IndexHiddenWord) 
                        && Guess[IndexGuess] == HiddenWord[IndexHiddenWord]
                        )
                    {
                        this->CowCount++;
                        this->IndexHiddenWordWithCow.Emplace(IndexHiddenWord);
                        break;
                    }
                }
            }
        }
    }

    void ResetAttr()
    {
        this->BullCount = 0;
        this->CowCount = 0;
        this->IndexGuessAndHiddenWordWithBull.Reset();
        this->IndexHiddenWordWithCow.Reset();
    }
};