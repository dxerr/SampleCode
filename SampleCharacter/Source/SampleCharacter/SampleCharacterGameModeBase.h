// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SampleCharacter/SpawnObject/Handler/ObjectSpawner.h"
#include "SampleCharacterGameModeBase.generated.h"


class FObjectSpawner;
/**
 * 
 */
UCLASS()
class SAMPLECHARACTER_API ASampleCharacterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	
public:
	ASampleCharacterGameModeBase();

	TWeakPtr<FObjectSpawner> GetSpawner() { return Spawner; }

private:
	TSharedPtr<FObjectSpawner> Spawner;
};
