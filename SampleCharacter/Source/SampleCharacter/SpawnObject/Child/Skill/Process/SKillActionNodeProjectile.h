// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillActionNodeBase.h"

class FBaseObject;
/**
 * 
 */
class SAMPLECHARACTER_API FSKillActionNodeProjectile : public FSkillActionNodeBase
{
public:
	FSKillActionNodeProjectile(const FSkillActionDataBase* Data);

public:
	virtual void Process(FBaseObject* Owner) override;
	virtual void Action(FBaseObject* Owner) override;

protected:
	
};
