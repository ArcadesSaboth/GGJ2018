// Fill out your copyright notice in the Description page of Project Settings.

#include "TextUtils.h"


int32 UTextUtils::CountSimilarTextes(UPARAM(ref) FString& first, UPARAM(ref) FString& second)
{
	const int32 firstLength = first.Len();
	const int32 secondLength = second.Len();

	int32 retval = 0;
	for (int i = 0, j = 0; i < firstLength && j < secondLength; i++, j++)
	{
		if (first[i] == second[j])
		{
			retval++;
		}
		else
		{
			break;
		}
	}

	return retval;
}
