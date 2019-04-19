// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectBase.h"
#include "GameObjectProjectile.generated.h"

class AProjectileActor;
/**
 * 
 */
UCLASS()
class SAMPLECHARACTER_API UGameObjectProjectile : public UGameObjectBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void DeInitialize() override;
	virtual AActor* GetActor() override;

protected:
	virtual void ActorSpawned(AActor* spawn) override;

protected:
	AProjectileActor* Actor;
};
