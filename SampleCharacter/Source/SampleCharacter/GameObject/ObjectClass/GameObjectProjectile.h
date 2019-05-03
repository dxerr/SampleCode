// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectBase.h"
#include "GameObjectProjectile.generated.h"

class AProjectileActor;
/**
 * 발사체 클래스
 */
UCLASS()
class SAMPLECHARACTER_API UGameObjectProjectile : public UGameObjectBase
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void DeInitialize() override;

    virtual EGameObjectType GetObjectType() const override;
	virtual AActor* GetActor() const override;

protected:
	virtual void ActorSpawned(AActor* Spawn) override;

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = GameObject, Meta = (AllowPrivateAccess = true))
	AProjectileActor* Actor;
};
