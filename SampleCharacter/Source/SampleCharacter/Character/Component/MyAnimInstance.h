// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstanceProxy.h"
#include "Animation/AnimInstance.h"
#include "Character/State/StateParams/StateParamBase.h"
#include "Global/GlobalDefine.h"
#include "MyAnimInstance.generated.h"


USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FSocialActionAniData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* Ani;
};

struct SAMPLECHARACTER_API FCurrentUpperAniData
{
	UAnimMontage* Ani;
	float Duration;
	double Timer;

	ECharacterStateUpperBase	ReturnState;

	bool IsEnd()
	{
		if (nullptr == Ani) { return false; }
		return FApp::GetCurrentTime() - Timer > Duration;
	}

	void Clear()
	{
		Ani = nullptr;
		Duration = 0.f;
		Timer = -1.f;
	}

	void OnMontageStart(UAnimMontage* Montage, bool bInterruped)
	{
		Ani = Montage;
		Timer = FApp::GetCurrentTime();
		Duration = Montage->CalculateSequenceLength();
	}

	void OnMontageEnded(UAnimMontage* Montage, bool bInterruped)
	{
	}
};

/**
 * 내부 로직에서 구현한 FSM의 상태정보를 애님블루프린트에 전달
 * Upper애니메이션에 해당하는 애니메이션 시퀀스 정보를 애님블루프린트에 전달
 */
UCLASS()
class SAMPLECHARACTER_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	//상태 정보
	//FSMManager에서 직접 참조 하고 싶은데 나이스한 방법을 아직 잘모르겠음 ㅠ
	ECharacterStateBase			BaseStateType;
	ECharacterStateUpperBase	UpperStateType;
	//UpperResource
	ECharacterStateUpperBase	UpperAnis;

	UAnimMontage* SocialAnis;
	

	//ECharacterStateBase			CurrStateType;
	FCurrentUpperAniData		CurrUpperAni;

protected:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayUpperAnimation(UAnimMontage* Animation);

public:
	//스테이트 파람 데이터 구성
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyAnimation")
	FStateBaseParams		Params;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyAnimation")
	FStateUpperBaseParams	UpperParams;

	//구조체의 함수 선언/정의부가 참조하는 곳보다 아래 위치해 있을경우 컴파일 에러의 발생
	//전방선언을 해봐도 해결되지 않았음..
	UPROPERTY(EditAnywhere, Category = "MyAnimation")
	TArray<FSocialActionAniData> SocialActions;

public:
	//FSMManager 애님 블루프린트 FSM 파라미터 동기화
	//FSMManager에서 직접 참조하고 싶지만.. 아직 잘모르겠음..
	//문제점1. AMyCharacter 객체 참조를 하려해도 에디터상 문제가 생김(CDO)
	//문제점2. 애님 블루프린트 상태 파라미터 검사시 쓰레드 세이프 하지 않음(AMyCharacter 형변환 노드 사용시)
	void ChangeState(int state);

	//애님 플루프린트 FSM동기화 참조 함수
	UFUNCTION(BlueprintPure,Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsState(ECharacterStateBase State);
	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsUpperState(ECharacterStateUpperBase State);
	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsUpperBlend();

	//임의 
	void PlayUpperAni(ECharacterStateUpperBase ChangeState, int Id);

public:
	UMyAnimInstance();
};