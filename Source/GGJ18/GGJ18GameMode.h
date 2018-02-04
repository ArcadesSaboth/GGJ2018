// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CardEntry.h"
#include "GGJ18GameMode.generated.h"

UCLASS(minimalapi)
class AGGJ18GameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGGJ18GameMode();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	TArray<FString> WordDabase;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FString AutoParse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FString ParseDelimiter;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	int32 UsedIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 MaxSpawns;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	float CardLifetimeMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	TArray<FCardEntry> SpawnedCards;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	int32 TotalScore;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 ScoreForMatching;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	int32 ScoreForFail;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintImplementableEvent, Category = Gameplay)
	void OnCardSpawn(const FCardEntry& entry);
	UFUNCTION(BlueprintImplementableEvent, Category = Gameplay)
	void OnCardUpdate(const FCardEntry& entry);
	UFUNCTION(BlueprintImplementableEvent, Category = Gameplay)
	void OnCardDeleted(int32 cardIndex);
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void OnTextEntry(const FString& text);
	UFUNCTION(BlueprintCallable, Category = Gameplay)
	void Score();

private:
	void AutoParseWords();
	void SpawnCards();

	void OnPreCardDelete(const FCardEntry& card, const bool addNegativeScore = true);
};
