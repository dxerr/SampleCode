// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnObject/PawnObject.h"
#include "NonePcObject.generated.h"

class FFSMManager;
class UAnimInstanceState;

/**
 * 
 */
UCLASS()
class SAMPLECHARACTER_API ANonePcObject : public APawnObject
{
	GENERATED_BODY()
	
public:
	ANonePcObject();
	
private:
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh;
	
protected:
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;

public:
	FORCEINLINE UAnimInstanceState* GetAnim() { return Animation; }

private:
	//Anim
	UAnimInstanceState* Animation;
	//FSM
	FFSMManager* Fsm;
};
