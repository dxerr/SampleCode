// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "SpawnObject/Child/SKill/Data/SkillDataBase.h"
#include "SkillDataContainerBase.generated.h"

/**
 * 
 */
 /**
  * ��ų ������������ ����ִ� Ŭ����
  * ���� ����� ������ ����
  * �ش� Ŭ������ �Ű�ü�� Game ĳ���͹� SkillEditor���� �����Ҽ��ְ� �����Ұ�
  */
UCLASS()
class SAMPLECHARACTER_API USkillDataContainerBase : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE const TArray<FSkillDataBase>& GetSkillData() { return Skills; }

	const FSkillDataBase* FindData(int ID);

	UPROPERTY(EditAnywhere)
	TArray<FSkillDataBase> Skills;
};
