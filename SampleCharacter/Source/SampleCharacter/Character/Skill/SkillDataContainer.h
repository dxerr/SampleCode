// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Character/Skill/Data/SkillData.h"
#include "SkillDataContainer.generated.h"


/**
 * ��ų ������������ ����ִ� Ŭ����
 * ���� ����� ������ ����
 * �ش� Ŭ������ �Ű�ü�� Game ĳ���͹� SkillEditor���� �����Ҽ��ְ� �����Ұ�
 */
UCLASS()
class SAMPLECHARACTER_API USkillDataContainer : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FORCEINLINE const TArray<FSkill>& GetSkillData() { return Skills; }

	const FSkill* FindData(int ID);

	UPROPERTY(EditAnywhere)
	TArray<FSkill> Skills;
};
