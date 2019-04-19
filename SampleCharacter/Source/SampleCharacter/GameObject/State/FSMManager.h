// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Global/GlobalDefine.h"
#include "StateBase.h"
#include "Define/StateParams.h"
#include "GameObject/ObjectClass/GameObjectBase.h"

/**
 * 
 */
class SAMPLECHARACTER_API FFSMManager
{
public:
	FORCEINLINE FStateBase* CurrentState() const { return Current; }
	FORCEINLINE FStateBase* PrevState() const { return Prev; }
	FORCEINLINE bool IsState(int StateID)
	{
		return (nullptr != Current && Current->GetStateID() == StateID);
	}

	//region
	void Initialize(FGameObjectBase* owner);
	void DeInitialize();

	void Update(float Delta);
	//FTimerManager를 통한 이벤트 처리 일정 시간후 이전 스테이트로 전환
	void ChangePrevState(float Time);

	template <typename T>
	bool ChangeState(FStateChangeFailed const& FailDelegate = nullptr);

private:
	bool ChangeState(FStateBase* State, FStateChangeFailed const& FailDelegate = nullptr);
	void CallbakChangePrevState(FStateBase* State);

private:
	FGameObjectBase* Owner;

	FStateBase* Current;
	FStateBase* Prev;
};

template <typename T>
bool FFSMManager::ChangeState(FStateChangeFailed const& FailDelegate)
{
	T* state = T::GetInstance();

	return ChangeState(state, FailDelegate);
}

