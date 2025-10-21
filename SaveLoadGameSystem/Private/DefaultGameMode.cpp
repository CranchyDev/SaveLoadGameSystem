// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultGameMode.h"


ADefaultGameMode::ADefaultGameMode()
{
	DefaultPawnClass = AExtraDefaultPawn::StaticClass();
	PlayerControllerClass = ADefaultPlayerController::StaticClass();
}

void ADefaultGameMode::BeginPlay()
{
	// Starts the Auto Save Timer.
	GetWorldTimerManager().SetTimer(AutoSaveTimer, this, &ADefaultGameMode::BeginAutoSave, 60.0f, true);
}

void ADefaultGameMode::CacheSaveSubsystem()
{
	if (USaveLoadGameSubsystem* Subsystem = GetGameInstance()->GetSubsystem<USaveLoadGameSubsystem>())
	{
		CachedSaveSubsystem = Subsystem;
	}
}

void ADefaultGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	CacheSaveSubsystem();

	if (CachedSaveSubsystem)
	{
		CachedSaveSubsystem->LoadGameAfterSuccessfulPostLogin(NewPlayer);
		UE_LOG(LogTemp, Warning, TEXT("CachedSaveSubsystem is ready."));

	}
}

void ADefaultGameMode::BeginAutoSave()
{
	if (CachedSaveSubsystem)
	{
		CachedSaveSubsystem->HandleAutoSave_Async_Start();
	}
	else
	{
		CacheSaveSubsystem();
		
		CachedSaveSubsystem->HandleAutoSave_Async_Start();
	}
}


