#pragma once

#include "CoreMinimal.h"
#include "SkillDataBase.generated.h"

class UAnimMontage;

/**
 *
 */
USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FSkillActiontDataBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int Type;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float Time;	//실행 시간정보
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int Count;	//수집 대상 갯수
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	int Effect;	//효과 정보
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
	//추후 Editor상에서 리소스를 드래그하면 Path정보가 입력되는 형태로 구현이 필요함
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SKill")
	UAnimMontage* ResAni;
	//FString ResAni;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SKill")
	TArray<FSkillActiontDataBase> SkillAction;

	double Timer; //내부용 End체크 타이머
};
