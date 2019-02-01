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
 * 
 */
UCLASS()
class SAMPLECHARACTER_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

private:
	ECharacterStateBase			CurrStateType;
	ECharacterStateUpperBase	CurrUpperStateType;
	FCurrentUpperAniData		CurrUpperAni;

protected:
	UAnimMontage* currentSocialAction;

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

	UFUNCTION(BlueprintCallable, Category = "MyAnimation")
	UAnimMontage* GetCurrentSocialAction() const;

	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	ECharacterStateBase GetCurrentStateType();

	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	UAnimMontage* CurrBlendAnimation() const;

	UFUNCTION(BlueprintPure,Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsState(ECharacterStateBase State);
	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsUpperState(ECharacterStateUpperBase State);
	UFUNCTION(BlueprintCallable, Category = "MyAnimation")
	bool IsUpperBlend();
	
	UFUNCTION(BlueprintNativeEvent, Category = "MyAnimation")
	void OnSocialPlay(int Index);
	void OnSocialPlay_Implementation(int Index);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyAnimation")
	void ChangeState(ECharacterStateBase ChangeState);
	void ChangeState_Implementation(ECharacterStateBase ChangeState);

	//���� ������ ���� �°� ����
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "MyAnimation")
	void ChangeUpperState(ECharacterStateUpperBase ChangeState, int Id);
	void ChangeUpperState_Implementation(ECharacterStateUpperBase ChangeState, int Id);

public:
	UMyAnimInstance();
};

//Proxy
USTRUCT()
struct SAMPLECHARACTER_API FAnimMyInstanceProxy : public FAnimInstanceProxy
{
	GENERATED_BODY()


};
