// Fill out your copyright notice in the Description page of Project Settings.


#include "ExtraDefaultPawn.h"

// Sets default values
AExtraDefaultPawn::AExtraDefaultPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AExtraDefaultPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AExtraDefaultPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AExtraDefaultPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

