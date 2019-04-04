// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "SpawnObject/Child/SKill/Data/SkillDataBase.h"
#include "SkillDataContainerBase.generated.h"

/**
 * 
 */
 /**
  * 스킬 데이터정보를 담고있는 클래스
  * 추후 변경될 여지가 많음
  * 해당 클래스를 매개체로 Game 캐릭터및 SkillEditor에서 참조할수있게 구현할것
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
