// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "DefaultSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class SAVELOADGAMESYSTEM_API UDefaultSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FText Saved_PlayerName = FText::FromString(TEXT("None"));

	UPROPERTY()
	FString Saved_SaveSlotName = TEXT("SaveGame0");

	UPROPERTY()
	int32 SomeRandomInteger;
};
