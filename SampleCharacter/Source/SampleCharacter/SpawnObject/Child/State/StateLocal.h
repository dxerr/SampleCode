// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "SpawnObject/Child/Component/Animation/AnimInstanceState.h"
#include "SpawnObject/Child/LocalPlayerObject.h"

template <typename T>
class SAMPLECHARACTER_API FStateSingleLocal : public StateSingleton<T>, public FStateTargetBase<ALocalPlayerObject>
{
protected:
	

protected:
	//애님 블루프린트에 가장 최우선으로 상태를 전송해줘야한다.
	virtual void OnEnter(ALocalPlayerObject* Owner) override
	{
		UAnimInstanceState* anim = Owner->GetAnim();
		anim->ChangeState(GetStateID());
	}

	virtual void OnReEnter(ALocalPlayerObject* Owner) override
	{

	}
	virtual void OnUpdate(ALocalPlayerObject* Owner, float Delta) override
	{

	}
	virtual void OnExit(ALocalPlayerObject* Owner) override
	{

	}
};

/**
 * 
 */
class SAMPLECHARACTER_API FStateIdle : public FStateSingleLocal<FStateIdle>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(ALocalPlayerObject* Owner) override;
};

//캐릭터는 전방 이동과 후방이동으로 분류
class SAMPLECHARACTER_API FStateForwardWalk : public FStateSingleLocal<FStateForwardWalk>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(ALocalPlayerObject* Owner) override;
	virtual void OnUpdate(ALocalPlayerObject* Owner, float Delta) override;

	//Movement 쪽으로 이동
	void UpdateSpeed(ALocalPlayerObject* Owner, float Speed);
};

class SAMPLECHARACTER_API FStateBackwardWalk : public FStateSingleLocal<FStateBackwardWalk>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(ALocalPlayerObject* Owner) override;
	virtual void OnUpdate(ALocalPlayerObject* Owner, float Delta) override;
};

class SAMPLECHARACTER_API FStateSideWalk : public FStateSingleLocal<FStateSideWalk>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(ALocalPlayerObject* Owner) override;
	virtual void OnUpdate(ALocalPlayerObject* Owner, float Delta) override;
};

/*
* NPC류에 사용 예정
class SAMPLECHARACTER_API FStateWalk : public FStateSingleBase<FStateWalk>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void Update(ALocalPlayerObject* Owner, float Delta) override;
};
*/

class SAMPLECHARACTER_API FStateRun : public FStateSingleLocal<FStateRun>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual bool IsChange(int StateID) override;
	virtual void OnEnter(ALocalPlayerObject* Owner) override;
	virtual void OnUpdate(ALocalPlayerObject* Owner, float Delta) override;
};

class SAMPLECHARACTER_API FStateAttack : public FStateSingleLocal<FStateAttack>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(ALocalPlayerObject* Owner) override;
	virtual void OnUpdate(ALocalPlayerObject* Owner, float Delta) override;
};
