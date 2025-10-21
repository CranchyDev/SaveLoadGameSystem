// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveLoadGameSubsystem.h"
#include "DefaultGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAVELOADGAMESYSTEM_API UDefaultGameInstance : public UGameInstance
{
	GENERATED_BODY()

	// Init equals more or less to a BeginPlay of an Actor.
	virtual void Init() override;
};
