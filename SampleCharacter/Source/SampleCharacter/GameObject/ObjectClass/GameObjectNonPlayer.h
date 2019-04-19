// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectDynamic.h"
#include "GameObjectNonPlayer.generated.h"

class APawn;
class ANpcPawn;
class FSkillBase;
/**
 * 
 */
UCLASS()
class SAMPLECHARACTER_API UGameObjectNonPlayer : public UGameObjectDynamic
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void DeInitialize() override;

public:
	virtual AActor* GetActor() override;
	virtual ANpcPawn* GetNpc();

protected:
	ANpcPawn* Actor;
};
