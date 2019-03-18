// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseObject.h"
#include "ActorObject.generated.h"

UCLASS()
class SAMPLECHARACTER_API AActorObject : public AActor, public FBaseObject
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorObject();

	virtual void* cast() override
	{
		return static_cast<AActor*>(this);
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
