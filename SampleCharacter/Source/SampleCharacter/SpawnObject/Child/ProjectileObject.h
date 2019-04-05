// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnObject/ActorObject.h"
#include "ProjectileObject.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHARACTER_API AProjectileObject : public AActorObject
{
	GENERATED_BODY()
	
public:
	AProjectileObject();

	UFUNCTION()
	void OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit);
};
