// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/SkillData.h"
#include "Character/Skill/SkillDataContainer.h"

class AMyCharacter;

/**
 * 
 */
class SAMPLECHARACTER_API FSkillManager
{
public:
	FSkillManager();
	virtual ~FSkillManager();

	void Initialize(AMyCharacter* Character);
	void LoadData(const TCHAR * Path);

	const FSkill* GetSkillData(int ID);

	void UseSKill(int ID);

	const FSkill* CurrentSkillData;

private:
	AMyCharacter* Owner;
	USkillDataContainer* SkillFactory;
};
