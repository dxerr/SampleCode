// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectDynamic.h"

class ACharacter;
class FFSMManager;
class FSkillBase;

/**
 * Player류에 해당 하는 base클래스
 * SKill, FSM의 상태는 두단계이상으로 분류
 */
class SAMPLECHARACTER_API FGameObjectPlayer : public FGameObjectDynamic
{
public:
	virtual void Initialize() override;
	virtual void DeInitialize() override;

public:
	virtual AActor* GetActor() override = 0;
	virtual ACharacter* GetCharacter() = 0;

	//virtual TWeakPtr<FFSMManager> GetBaseFSM() = 0;
	virtual FFSMManager* GetUpperFSM();
	virtual FSkillBase* GetSkill();

public:
	virtual void Update(float delta) override;

protected:
	FFSMManager* UpperFsm;
	FSkillBase* Skill;
};
