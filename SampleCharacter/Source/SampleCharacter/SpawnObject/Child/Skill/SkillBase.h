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
	virtual ~FSkillBase() = default;

	virtual void Initialize(FBaseObject* owner);
	virtual void DeInitialize();
	virtual void LoadData(const TCHAR * Path);

	virtual void UseSKill(int ID);

	//CurrentSkillData ����ü ������� ��ų ���� Ȱ��ȭ
	//��ų ��� ����Ⱑ ���� �ʿ��Ҽ��ִ�.
	virtual void OnSKillNode();
	virtual void RunSkillNode(float DeltaTime);
	virtual void EndSKillNode();

	const FSkillDataBase* GetSkillData(int ID);
	struct RunSKillInfo* CurrentSkillData = nullptr;

protected:
	FBaseObject* Owner;
	USkillDataContainerBase* SkillFactory;
};

struct RunSKillInfo
{
	const FSkillDataBase* Data;
	float Timer;

	RunSKillInfo(const FSkillDataBase* SkillData)
	{
		Data = SkillData;
		Timer = 0.f;
	}

	UAnimMontage* GetAni()
	{
		return Data->ResAni;
	}

	bool IsEnd()
	{
		return Data->Duration < Timer;
	}

	float GetRate()
	{
		return Timer / Data->Duration;
	}
};
