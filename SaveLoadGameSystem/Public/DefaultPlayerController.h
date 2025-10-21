// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SaveLoadGameInterface.h"
#include "DefaultPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SAVELOADGAMESYSTEM_API ADefaultPlayerController : public APlayerController , public ISaveLoadGameInterface
{
	GENERATED_BODY()

	// Functions from SaveLoadGameInterface
	virtual void SetPlayerNameAfterLogin(FText NewPlayerName) override;
	
};
