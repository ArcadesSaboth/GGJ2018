// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "GGJ18GameMode.h"
#include "GGJ18PlayerController.h"
#include "GGJ18Character.h"
#include "UObject/ConstructorHelpers.h"

AGGJ18GameMode::AGGJ18GameMode()
	: CardLifetimeMultiplier(2.f)
	, ParseDelimiter(TEXT(","))
	, TotalScore(0)
	, ScoreForMatching(500)
	, ScoreForFail(100)
{
	// use our custom PlayerController class
	PlayerControllerClass = AGGJ18PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AGGJ18GameMode::BeginPlay()
{
	AutoParseWords();

	Super::BeginPlay();

	SpawnCards();
}

void AGGJ18GameMode::Tick(float DeltaTime)
{
	for (int32 i = SpawnedCards.Num() - 1; i >= 0; i--)
	{
		FCardEntry& iter = SpawnedCards[i];
		iter.Tick(DeltaTime);

		OnCardUpdate(iter);

		if (iter.IsExpired())
		{
			OnPreCardDelete(iter);
			SpawnedCards.RemoveAt(i);
		}
	}

	SpawnCards();

	Super::Tick(DeltaTime);
}

void AGGJ18GameMode::AutoParseWords()
{
	if (AutoParse.IsEmpty() || ParseDelimiter.IsEmpty())
	{
		return;
	}

	AutoParse.ParseIntoArray(WordDabase, &ParseDelimiter[0], true);
}

void AGGJ18GameMode::SpawnCards()
{
	int32 spawned = SpawnedCards.Num();
	for (int32 i = spawned; i < MaxSpawns; i++)
	{
		int32 choosen = FMath::RandRange(0, WordDabase.Num() - 1);

		FCardEntry entry;
		entry.Word = WordDabase[choosen];
		entry.Index = UsedIndex++;
		entry.Lifetime = entry.Word.Len() * CardLifetimeMultiplier;

		SpawnedCards.Add(entry);

		OnCardSpawn(entry);
	}
}


void AGGJ18GameMode::OnPreCardDelete(const FCardEntry& card, const bool addNegativeScore)
{
	if (addNegativeScore && card.HighlightedCharacters > 0 && !card.Matching)
	{
		TotalScore -= ScoreForFail;
	}

	OnCardDeleted(card.Index);
}

void AGGJ18GameMode::OnTextEntry(const FString& text)
{
	bool atLeastOneCompleted = false;
	// There must be a smarter way to do this...
	for (auto&& iter : SpawnedCards)
	{
		iter.CalculateMatchingChars(text);
		iter.Matching = false;

		if (iter.HighlightedCharacters == iter.Word.Len())
		{
			atLeastOneCompleted = true;
		}
	}

	for (int32 i = 0; i < SpawnedCards.Num(); i++)
	{
		if (SpawnedCards[i].HighlightedCharacters == 0)
		{
			continue;
		}

		for (int32 j = i + 1; j < SpawnedCards.Num(); j++)
		{
			if (SpawnedCards[j].HighlightedCharacters == 0)
			{
				continue;
			}

			if (SpawnedCards[i].Word.Compare(SpawnedCards[j].Word) == 0)
			{
				SpawnedCards[i].Matching = SpawnedCards[j].Matching = true;
			}
		}
	}

	if (atLeastOneCompleted)
	{
		Score();
	}
}

void AGGJ18GameMode::Score()
{
	int32 totalAdded = 0;
	int32 totalFail = 0;
	// If a card is matching
	// 
	for (int i = SpawnedCards.Num() - 1; i >= 0; i--)
	{
		if (SpawnedCards[i].HighlightedCharacters > 0)
		{
			if (!SpawnedCards[i].Matching)
			{
				totalFail += ScoreForFail;
			}
			else if (SpawnedCards[i].HighlightedCharacters == SpawnedCards[i].Word.Len())
			{
				totalAdded += ScoreForMatching;
			}

			OnPreCardDelete(SpawnedCards[i], false);
			SpawnedCards.RemoveAt(i);
		}
	}

	// If we have at least one match, we add points and discard all the failures
	if (totalAdded > 0)
	{
		TotalScore += totalAdded;
	}
	else // However, if we have no match, then we add the total failures.
	{
		TotalScore -= totalFail;
	}
}
