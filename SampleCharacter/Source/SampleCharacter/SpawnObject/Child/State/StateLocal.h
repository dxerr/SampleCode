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
	//�ִ� �������Ʈ�� ���� �ֿ켱���� ���¸� ����������Ѵ�.
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

//ĳ���ʹ� ���� �̵��� �Ĺ��̵����� �з�
class SAMPLECHARACTER_API FStateForwardWalk : public FStateSingleLocal<FStateForwardWalk>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(ALocalPlayerObject* Owner) override;
	virtual void OnUpdate(ALocalPlayerObject* Owner, float Delta) override;

	//Movement ������ �̵�
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
* NPC���� ��� ����
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
