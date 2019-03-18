// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SpawnObject/Child/State/Define/StateParams.h"
#include "AnimInstanceLocal.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHARACTER_API UAnimInstanceLocal : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	//���� ����
	//FSMManager���� ���� ���� �ϰ� ������ ���̽��� ����� ���� �߸𸣰��� ��
	EStateBase			BaseStateType;
	EStateUpperBase		UpperStateType;

public:
	//FSMManager �ִ� �������Ʈ FSM �Ķ���� ����ȭ
	//FSMManager���� ���� �����ϰ� ������.. ���� �߸𸣰���..
	//������1. AMyCharacter ��ü ������ �Ϸ��ص� �����ͻ� ������ ����(CDO)
	//������2. �ִ� �������Ʈ ���� �Ķ���� �˻�� ������ ������ ���� ����(AMyCharacter ����ȯ ��� ����)
	void ChangeState(int state);

	void PlayUpperAni(UAnimMontage* res);

	//�ִ� �÷�����Ʈ FSM����ȭ ���� �Լ�
	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsState(EStateBase State);
	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsStates(const TArray<EStateBase>& States);
	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsUpperState(EStateUpperBase State);
	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsUpperBlend();
	UFUNCTION(BlueprintPure, Category = "MyAnimation", meta = (BlueprintThreadSafe))
	bool IsMoveState();
};
