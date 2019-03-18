// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"

class ALocalPlayerObject;

/**
 * 
 */
class SAMPLECHARACTER_API FSKillLocal : public FSkillBase
{
public:
	FSKillLocal();
	virtual ~FSKillLocal();

	virtual void UseSKill(int ID) override;
};
