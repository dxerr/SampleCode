// Fill out your copyright notice in the Description page of Project Settings.

#include "SampleCharacterGameModeBase.h"
#include "Controller/PlayerControllerExpend.h"


void ASampleCharacterGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void ASampleCharacterGameModeBase::RestartPlayer(AController* NewPlayer)
{
	AActor* const StartSpot = FindPlayerStart(NewPlayer);
	if (StartSpot != nullptr)
	{
		// initialize and start it up
		InitStartSpot(StartSpot, NewPlayer);

		APlayerControllerExpend* const NewPC = Cast<APlayerControllerExpend>(NewPlayer);
		if (NewPC != nullptr)
		{
			NewPC->SetInitialLocationAndRotation(StartSpot->GetActorLocation(), StartSpot->GetActorRotation());
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Player start not found, failed to restart player"));
	}
}