// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FSkillActionDataBase;
class UGameObjectBase;

/**
 * FSkillActionDataBase 데이터 기반으로 스킬 액션 처리 담당
 */
class SAMPLECHARACTER_API FSkillActionNodeBase
{
public:
	FSkillActionNodeBase(const FSkillActionDataBase& Data);
	virtual ~FSkillActionNodeBase();

public:
	float GetRate();

	virtual void Process(UGameObjectBase* Owner) {}
	virtual void Action(UGameObjectBase* Owner) {}

	//생명 주기 관장
	virtual bool Update(UGameObjectBase* Owner) { return false;  }

protected:
	float Rate;
};
