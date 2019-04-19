#pragma once

#include "CoreMinimal.h"
#include "SkillDataBase.generated.h"

class UAnimMontage;

/**
 *
 */
USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FSkillActionDataBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int Type;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float Rate;	//���� Ÿ�̹� ����
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int Count;	//���� ��� ����
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int RefID;	//ȿ�� ���� ����
};

USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FSkillDataBase
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SKill")
	int ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SKill")
	float Duration;
	//���� Editor�󿡼� ���ҽ��� �巡���ϸ� Path������ �ԷµǴ� ���·� ������ �ʿ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SKill")
	UAnimMontage* ResAni;
	//FString ResAni;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SKill")
	TArray<FSkillActionDataBase> SkillAction;
};
