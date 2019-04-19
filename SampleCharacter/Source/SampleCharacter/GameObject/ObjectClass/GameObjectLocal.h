// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectPlayer.h"
#include "GameObjectLocal.generated.h"

class ALocalCharacter;
class UInputBindingLocalPlayer;

/**
 * 
 */
UCLASS()
class SAMPLECHARACTER_API UGameObjectLocal : public UGameObjectPlayer
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void DeInitialize() override;

public:
	virtual AActor* GetActor() override;
	virtual ACharacter* GetCharacter() override;
	ALocalCharacter* GetLocal();


	virtual FFSMManager* GetBaseFSM() override;
	virtual FFSMManager* GetUpperFSM() override;
	virtual FSkillBase* GetSkill()  override;
	virtual FPartsBase* GetParts() override;

public:
	virtual void Update(float delta) override;

protected:
	virtual void ActorSpawned(AActor* Spawn) override;

public:
	//Movement로 이관필요
	float MovementForce;
	FORCEINLINE void SetMoveSpeed(float val) { MovementForce = val; }
	//

private:
 	ALocalCharacter* Actor;
	UInputBindingLocalPlayer* InputBinding;
};
