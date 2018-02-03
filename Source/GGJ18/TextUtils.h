// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TextUtils.generated.h"

/**
 * 
 */
UCLASS()
class GGJ18_API UTextUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = TextUtils)
	static int32 CountSimilarTextes(const FString& first, const FString& second);
};
