// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillActionNodeBase.h"

class UGameObjectBase;
/**
 * 
 */
class SAMPLECHARACTER_API FSKillActionNodeProjectile : public FSkillActionNodeBase
{
public:
	FSKillActionNodeProjectile(const FSkillActionDataBase& Data);

public:
	virtual void Process(UGameObjectBase* Owner) override;
	virtual void Action(UGameObjectBase* Owner) override;
};
