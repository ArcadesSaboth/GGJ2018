// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "GGJ18GameMode.h"
#include "GGJ18PlayerController.h"
#include "GGJ18Character.h"
#include "UObject/ConstructorHelpers.h"

AGGJ18GameMode::AGGJ18GameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AGGJ18PlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	ParseDelimiter = TEXT(",");
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

		if (iter.IsExpired())
		{
			OnCardDeleted(iter.Index);
		}

		SpawnedCards.RemoveAt(i);
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
		int32 choosen = FMath::RandRange(0, WordDabase.Num());

		FCardEntry entry;
		entry.Word = WordDabase[choosen];
		entry.Index = UsedIndex++;
		entry.Lifetime = entry.Word.Len() * 2.f;

		SpawnedCards.Add(entry);

		OnCardSpawn(entry);
	}
}
