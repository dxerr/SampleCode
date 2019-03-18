// Fill out your copyright notice in the Description page of Project Settings.

#include "PawnObject.h"

// Sets default values
APawnObject::APawnObject()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APawnObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APawnObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APawnObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

