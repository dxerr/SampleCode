// Fill out your copyright notice in the Description page of Project Settings.

#include "CharacterObject.h"

// Sets default values
ACharacterObject::ACharacterObject()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACharacterObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACharacterObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

