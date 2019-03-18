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
	//상태 정보
	//FSMManager에서 직접 참조 하고 싶은데 나이스한 방법을 아직 잘모르겠음 ㅠ
	EStateBase			BaseStateType;
	EStateUpperBase		UpperStateType;

public:
	//FSMManager 애님 블루프린트 FSM 파라미터 동기화
	//FSMManager에서 직접 참조하고 싶지만.. 아직 잘모르겠음..
	//문제점1. AMyCharacter 객체 참조를 하려해도 에디터상 문제가 생김(CDO)
	//문제점2. 애님 블루프린트 상태 파라미터 검사시 쓰레드 세이프 하지 않음(AMyCharacter 형변환 노드 사용시)
	void ChangeState(int state);

	void PlayUpperAni(UAnimMontage* res);

	//애님 플루프린트 FSM동기화 참조 함수
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
