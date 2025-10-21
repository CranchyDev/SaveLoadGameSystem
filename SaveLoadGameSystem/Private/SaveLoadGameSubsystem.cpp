// Fill out your copyright notice in the Description page of Project Settings.


#include "SaveLoadGameSubsystem.h"
#include "GameFramework/PlayerState.h"
#include "GameFramework/PlayerController.h"
#include "DefaultSaveGame.h"
#include "Kismet/GameplayStatics.h"

void USaveLoadGameSubsystem::LoadGameAfterSuccessfulPostLogin(APlayerController* NewPlayer)
{
	APlayerState* TempPState = NewPlayer->PlayerState;
	PlayerControllerIndex = TempPState->GetPlayerId();

	// Loads Game if it exists
	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, PlayerControllerIndex))
	{
		if (UDefaultSaveGame* SaveGame = Cast<UDefaultSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, PlayerControllerIndex)))
		{
			// Handle data within this Subsystem from the Save Game file.
			PlayerName = SaveGame->Saved_PlayerName;
			SaveSlotName = SaveGame->Saved_SaveSlotName;

			UE_LOG(LogTemp, Warning, TEXT("Game successfully loaded."));

			BroadcastLoadingWasSuccessful(true);
		}
	}
}

void USaveLoadGameSubsystem::SetPlayerName(FText InputPlayerName)
{
	PlayerName = InputPlayerName;
}

void USaveLoadGameSubsystem::HandleAutoSave_Async_Start()
{
	if (!IsSaving)
	{
		IsSaving = true; // Sets the boolean 'IsSaving' to true, to prevent any further potential Auto/Manual Saves.

		if (UDefaultSaveGame* SGInst = Cast<UDefaultSaveGame>(UGameplayStatics::CreateSaveGameObject(UDefaultSaveGame::StaticClass())))
		{
			FAsyncSaveGameToSlotDelegate SavedDelegate;
			SavedDelegate.BindUObject(this, &USaveLoadGameSubsystem::HandleAutoSave_Async_End);

			// Handle any data to be saved onto the Save Game file.
			SGInst->Saved_PlayerName = PlayerName;

			UGameplayStatics::AsyncSaveGameToSlot(SGInst, SaveSlotName, PlayerControllerIndex, SavedDelegate);
			UE_LOG(LogTemp, Warning, TEXT("Asynchronous Auto Save has started."));

		}
		else
		{
			// Sets IsSaving to false in case SGInst is null. This prevents the function being 'locked'.
			IsSaving = false;
		}
	}
}

void USaveLoadGameSubsystem::HandleAutoSave_Async_End(const FString& SlotName, const int32 UserIndex, bool bSuccess)
{
	UE_LOG(LogTemp, Warning, TEXT("Asynchronous Auto Save has been complete."));

	IsSaving = false; // Sets the 'IsSaving' boolean back to false.
}

void USaveLoadGameSubsystem::HandleAutoSave_Sync()
{
	if (!IsSaving)
	{
		if (UDefaultSaveGame* SGInst = Cast<UDefaultSaveGame>(UGameplayStatics::CreateSaveGameObject(UDefaultSaveGame::StaticClass())))
		{
			IsSaving = true; // Sets the boolean 'IsSaving' to true, to prevent any further potential Auto/Manual Saves.

			UE_LOG(LogTemp, Warning, TEXT("Synchronous Auto Save has started."));

			// Handle any data to be saved onto the Save Game file.
			SGInst->Saved_PlayerName = PlayerName;

			if (UGameplayStatics::SaveGameToSlot(SGInst, SaveSlotName, PlayerControllerIndex))
			{
				IsSaving = false; // Sets the 'IsSaving' boolean back to false.
			}
			else
			{
				IsSaving = false;
			}
		}
		else
		{
			// In case SGInst isn't valid for any reason, still set the IsSaving to false.
			IsSaving = false;
		}
		UE_LOG(LogTemp, Warning, TEXT("Synchronous Auto Save has ended."));
	}
}

void USaveLoadGameSubsystem::HandleLoad_Async_Start()
{
	if (!IsLoading)
	{
		IsLoading = true;

		FAsyncLoadGameFromSlotDelegate LoadedDelegate;
		LoadedDelegate.BindUObject(this, &USaveLoadGameSubsystem::HandleLoad_Async_End);

		UE_LOG(LogTemp, Warning, TEXT("Asynchronous Auto Load has started."));

		UGameplayStatics::AsyncLoadGameFromSlot(SaveSlotName, PlayerControllerIndex, LoadedDelegate);
	}
}

void USaveLoadGameSubsystem::HandleLoad_Async_End(const FString& SlotName, const int32 UserIndex, USaveGame* LoadedGameData)
{
	IsLoading = false;

	UE_LOG(LogTemp, Warning, TEXT("Asynchronous Auto Load has ended."));
}

void USaveLoadGameSubsystem::HandleLoad_Sync()
{
	if (UDefaultSaveGame* LGInst = Cast<UDefaultSaveGame>(UGameplayStatics::LoadGameFromSlot(SaveSlotName, PlayerControllerIndex)))
	{
		PlayerName = LGInst->Saved_PlayerName;

		BroadcastLoadingWasSuccessful(true);
	}
}

void USaveLoadGameSubsystem::BroadcastLoadingWasSuccessful(bool Success)
{
	OnLoadComplete.Broadcast(Success);
}