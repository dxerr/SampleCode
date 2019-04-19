// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectDynamic.h"

class APawn;
class ANpcPawn;
class FSkillBase;
/**
 * 
 */
class SAMPLECHARACTER_API FGameObjectNonPlayer : public FGameObjectDynamic
{
public:
	virtual void Initialize() override;
	virtual void DeInitialize() override;

public:
	virtual AActor* GetActor() override;
	virtual ANpcPawn* GetNpc();

protected:
	ANpcPawn* Actor;
};
