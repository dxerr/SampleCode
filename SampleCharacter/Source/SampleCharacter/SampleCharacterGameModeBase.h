// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SampleCharacterGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHARACTER_API ASampleCharacterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void RestartPlayer(AController* NewPlayer) override;
};
