// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectDynamic.h"
#include "GameObjectPlayer.generated.h"

class ACharacter;
class FFSMManager;
class FSkillBase;

/**
 * Player류에 해당 하는 base클래스
 * SKill, FSM의 상태는 두단계이상으로 분류
 */
UCLASS()
class SAMPLECHARACTER_API UGameObjectPlayer : public UGameObjectDynamic
{
	GENERATED_BODY()
	
public:
	virtual void Initialize() override;
	virtual void DeInitialize() override;

public:    
    virtual EGameObjectType GetObjectType() const override;
	virtual AActor* GetActor() const override;
    UFUNCTION(BlueprintCallable, Category = "GameObject")
	virtual ACharacter* GetCharacter() const;

	//virtual TWeakPtr<FFSMManager> GetBaseFSM() = 0;
	virtual FFSMManager* GetUpperFSM() const;
	virtual FSkillBase* GetSkill() const;

public:
	virtual void Update(float Delta) override;

protected:
	FFSMManager* UpperFsm;
	FSkillBase* Skill;
};
