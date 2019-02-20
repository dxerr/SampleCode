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
 * ���� �������� ������ FSM�� ���������� �ִԺ������Ʈ�� ����
 * Upper�ִϸ��̼ǿ� �ش��ϴ� �ִϸ��̼� ������ ������ �ִԺ������Ʈ�� ����
 */
UCLASS()
class SAMPLECHARACTER_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	//���� ����
	//FSMManager���� ���� ���� �ϰ� ������ ���̽��� ����� ���� �߸𸣰��� ��
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
	//������Ʈ �Ķ� ������ ����
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyAnimation")
	FStateBaseParams		Params;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "MyAnimation")
	FStateUpperBaseParams	UpperParams;

	//����ü�� �Լ� ����/���Ǻΰ� �����ϴ� ������ �Ʒ� ��ġ�� ������� ������ ������ �߻�
	//���漱���� �غ��� �ذ���� �ʾ���..
	UPROPERTY(EditAnywhere, Category = "MyAnimation")
	TArray<FSocialActionAniData> SocialActions;

public:
	//FSMManager �ִ� �������Ʈ FSM �Ķ���� ����ȭ
	//FSMManager���� ���� �����ϰ� ������.. ���� �߸𸣰���..
	//������1. AMyCharacter ��ü ������ �Ϸ��ص� �����ͻ� ������ ����(CDO)
	//������2. �ִ� �������Ʈ ���� �Ķ���� �˻�� ������ ������ ���� ����(AMyCharacter ����ȯ ��� ����)
	void ChangeState(int state);

	//�ִ� �÷�����Ʈ FSM����ȭ ���� �Լ�
	UFUNCTION(BlueprintPure,Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsState(ECharacterStateBase State);
	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsUpperState(ECharacterStateUpperBase State);
	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsUpperBlend();

	//���� 
	void PlayUpperAni(ECharacterStateUpperBase ChangeState, int Id);

public:
	UMyAnimInstance();
};