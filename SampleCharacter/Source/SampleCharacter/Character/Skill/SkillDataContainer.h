// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Character/Skill/Data/SkillData.h"
#include "SkillDataContainer.generated.h"


/**
 * 스킬 데이터정보를 담고있는 클래스
 * 추후 변경될 여지가 많음
 * 해당 클래스를 매개체로 Game 캐릭터및 SkillEditor에서 참조할수있게 구현할것
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
