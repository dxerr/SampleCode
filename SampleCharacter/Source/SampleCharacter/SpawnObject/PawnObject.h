// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BaseObject.h"
#include "PawnObject.generated.h"

UCLASS()
class SAMPLECHARACTER_API APawnObject : public APawn, public FBaseObject
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APawnObject();

	virtual void* cast() override
	{
		return static_cast<APawn*>(this);
	}


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
