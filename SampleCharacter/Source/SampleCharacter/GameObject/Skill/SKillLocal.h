// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SkillBase.h"
#include "Process/SkillActionNodeBase.h"

class ALocalPlayerObject;
/**
 * 
 */
class SAMPLECHARACTER_API FSKillLocal : public FSkillBase
{
public:
	FSKillLocal();
	virtual ~FSKillLocal();

	virtual void Initialize(UGameObjectBase* Owner) override;

	virtual void LoadData(const TCHAR * Path) override;
	virtual void UseSKill(int ID) override;

	virtual void OnSKillNode() override;
	virtual void RunSkillNode(float DeltaTime) override;

	TArray<FSkillActionNodeBase*>* GetSKillNodes(int ID);

private:
	void LoadSKillNode();
	FSkillActionNodeBase* CreateSkillNode(const FSkillActionDataBase& Data) const;

private:
	//스킬 액션 정보들
	TMap<int, TArray<FSkillActionNodeBase*>> MapSkillNodes;
	TArray<FSkillActionNodeBase*> RunSkillNodes;
	TArray<FSkillActionNodeBase*> UseSkillNodes;
};
