// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SaveLoadGameInterface.h"
#include "DefaultGameInstance.h"
#include "ExtraDefaultPawn.h"
#include "DefaultPlayerController.h"
#include "SaveLoadGameSubsystem.h"
#include "DefaultGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SAVELOADGAMESYSTEM_API ADefaultGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADefaultGameMode();

	// BeginPlay
	virtual void BeginPlay() override;

	// Function inherited from the Game Mode.
	virtual void PostLogin(APlayerController* NewPlayer) override;

public:
	// Caches the SaveLoadGameSubsystem for later usage.
	virtual void CacheSaveSubsystem();

	UPROPERTY()
	USaveLoadGameSubsystem* CachedSaveSubsystem;

private:
	// Timer to BeginAutoSave() every X seconds (default is 60).
	FTimerHandle AutoSaveTimer;

	// Calls the function HandleAutoSave_Async_Start() within SaveLoadGameSubsystem.
	void BeginAutoSave();

};
