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
    virtual EGameObjectType GetObjectType() const override;
	virtual AActor* GetActor() const override;
    UFUNCTION(BlueprintCallable, Category = "GameObject")
	virtual ANpcPawn* GetNpc() const;

public:
	virtual void OnHit(UGameObjectBase* Target) override;

protected:
	virtual void ActorSpawned(AActor* Spawn) override;

protected:
	UPROPERTY(Transient, VisibleInstanceOnly, Category = GameObject, Meta = (AllowPrivateAccess = true))
	ANpcPawn* Actor;
};
