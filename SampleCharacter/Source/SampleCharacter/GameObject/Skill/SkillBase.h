// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Data/SkillDataBase.h"

class UGameObjectBase;
class USkillDataContainerBase;

/**
 * 
 */
class SAMPLECHARACTER_API FSkillBase
{
public:

	virtual void Initialize(UGameObjectBase* Owner);
	virtual void DeInitialize();
	virtual void LoadData(const TCHAR * Path);

	virtual void Update(float Delta);

	virtual void UseSKill(int ID);

	//CurrentSkillData 구조체 기반으로 스킬 실행 활성화
	//스킬 노드 제어기가 따로 필요할수있다.
	virtual void OnSKillNode();
	virtual void RunSkillNode(float DeltaTime);
	virtual void EndSKillNode();

	const FSkillDataBase* GetSkillData(int ID);
	struct RunSKillInfo* CurrentSkillData = nullptr;

protected:
	UGameObjectBase* Owner;
	USkillDataContainerBase* SkillFactory;
};

//발동 스킬(액션) 구조체
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
