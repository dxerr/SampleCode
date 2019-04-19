// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectBase.h"

class AProjectileActor;
/**
 * 
 */
class SAMPLECHARACTER_API FGameObjectProjectile : public FGameObjectBase
{
public:
	virtual void Initialize() override;
	virtual void DeInitialize() override;
	virtual AActor* GetActor() override;

protected:
	virtual void ActorSpawned(AActor* spawn) override;

protected:
	AProjectileActor* Actor;
};
