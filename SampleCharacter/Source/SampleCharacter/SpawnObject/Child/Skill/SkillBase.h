// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/SkillDataBase.h"

class FBaseObject;
class USkillDataContainerBase;

/**
 * 
 */
class SAMPLECHARACTER_API FSkillBase
{
public:
	virtual void Initialize(FBaseObject* owner);
	virtual void LoadData(const TCHAR * Path);

	virtual void UseSKill(int ID);

	const FSkillDataBase* GetSkillData(int ID);
	const FSkillDataBase* CurrentSkillData;

protected:
	FBaseObject* Owner;
	USkillDataContainerBase* SkillFactory;
};
