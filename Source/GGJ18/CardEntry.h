#pragma once

#include "CardEntry.generated.h"

USTRUCT(BlueprintType)
struct FCardEntry
{
	GENERATED_BODY()

	FCardEntry();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Word;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 Index;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Lifetime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HighlightedCharacters;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool Matching;

	void Tick(float dt);
	float GetCurrentTime() const;
	float GetNormalizedLifetime() const;
	bool IsExpired() const;

	void CalculateMatchingChars(const FString& text);
private:
	float m_timer;
};
