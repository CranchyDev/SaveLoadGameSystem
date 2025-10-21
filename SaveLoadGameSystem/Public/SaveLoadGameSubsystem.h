// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameFramework/SaveGame.h"
#include "SaveLoadGameSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveCompletedDynamic, bool, bSuccess);


/**
 * Simple Subsystem that Saves/Loads the game from a Save Game Class File.
 * 
 * Serialization is handled within this Subsystem (for each variable that must be saved),
 * and the Save Game Class is also directly referenced herein for simplicity's sake.
 */
UCLASS()
class SAVELOADGAMESYSTEM_API USaveLoadGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	/**
	* This function is called within the GameInstance after AfterPostLogin() (from ISaveLoadGameInterface)
	* function is called.
	* 
	* Afterwards, this function will handle any Loading Save Game File if it exists,
	* and cache any variables therein into the Subsystem for later usage.
	* 
	*/
	virtual void LoadGameAfterSuccessfulPostLogin(APlayerController* PlayerC);

	// Used to set the Player Name that has been handled from Player Input within Widget environment.
	UFUNCTION(BlueprintCallable, Category = "PlayerData|PlayerName")
	void SetPlayerName(FText InputPlayerName);

	// Auto Saving function handler for Asynchronous saving only.
	void HandleAutoSave_Async_Start();
	void HandleAutoSave_Async_End(const FString& SlotName, const int32 UserIndex, bool bSuccess);

	// Auto Saving function handler for Synchronous saving only.
	// Usually meant to be called within Blueprint environment.
	UFUNCTION(BlueprintCallable, Category = "SaveLoadGameSystem|Saving")
	void HandleAutoSave_Sync();

	// Manual Load function handler for Asyncrhonous Loading only.
	void HandleLoad_Async_Start();
	void HandleLoad_Async_End(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData);

	// Manual Load function handler for Syncrhonous Loading only.
	// Usually meant to be called within Blueprint environment.
	UFUNCTION(BlueprintCallable, Category = "SaveLoadGameSystem|Loading")
	void HandleLoad_Sync();

	/**
	* Save the Save Game as an FString that can be edited by user input.
	* Note: If default value hasn't been changed, it'll use SaveGame0.
	* 
	* WARNING: Do not let this value be empty, else, all saves/loads will silently fail.
	*/
	UPROPERTY(BlueprintReadWrite)
	FString SaveSlotName = TEXT("SaveGame0");

	// Save the Player Controller Index
	UPROPERTY()
	int32 PlayerControllerIndex;

	// Player Name to be saved from a Widget, from player input.
	UPROPERTY(BlueprintReadWrite)
	FText PlayerName = FText::FromString(TEXT("None"));

	// Boolean to set to True when Saving or Auto Saving,
	// and then False to when Saving has been complete.
	bool IsSaving;

	// Boolean to set to True when Loading or Auto Loading.
	// Useful to prevent Loading from the Save Game too many times in a row.
	bool IsLoading;

	// Creates a Multi-Cast delegate to be able to Assign when the Game was Loaded.
	// Assignable in Blueprints.
	UPROPERTY(BlueprintAssignable, Category = "SaveLoadGameSystem|Loading")
	FOnSaveCompletedDynamic OnLoadComplete;

	// This function is called whenever Loading the game was sucessful.
	void BroadcastLoadingWasSuccessful(bool Success);
};
