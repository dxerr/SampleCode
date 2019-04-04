// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

struct FSkillActionDataBase;
class FBaseObject;

/**
 * FSkillActionDataBase ������ ������� ��ų �׼� ó�� ���
 */
class SAMPLECHARACTER_API FSkillActionNodeBase
{
public:
	FSkillActionNodeBase(const FSkillActionDataBase* Data);
	virtual ~FSkillActionNodeBase();

public:
	float GetRate();

	virtual void Process(FBaseObject* Owner) {}
	virtual void Action(FBaseObject* Owner) {}

	//���� �ֱ� ����
	virtual bool Update(FBaseObject* Owner) { return false;  }

protected:
	const FSkillActionDataBase* SkillData;
};
