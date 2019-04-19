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
	FORCEINLINE bool IsState(int stateID)
	{
		return (nullptr != Current && Current->GetStateID() == stateID);
	}

	//region
	void Initialize(UGameObjectBase* owner);
	void DeInitialize();

	template <class Owner>
	void Update(Owner* owner, float delta);
	template <class State>
	bool ChangeState(FStateChangeFailed const& failDelegate = nullptr);
	//FTimerManager를 통한 이벤트 처리 일정 시간후 이전 스테이트로 전환
	void ChangePrevState(float Time);

private:
	bool ChangeState(FStateBase* state, FStateChangeFailed const& failDelegate = nullptr);
	void CallbakChangePrevState(FStateBase* State);

private:
	UGameObjectBase* Owner;
	FStateBase* Current;
	FStateBase* Prev;
};

template <class Object>
void FFSMManager::Update(Object* owner, float delta)
{
	if (nullptr != Current)
	{
		Current->Update(owner, delta);
	}
}

template <class State>
bool FFSMManager::ChangeState(FStateChangeFailed const& failDelegate)
{
	State* state = State::GetInstance();
	return ChangeState(state, failDelegate);
}