// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "GameObject/ActorExtend/LocalCharacter.h"
#include "GameObject/ObjectClass/GameObjectLocal.h"

template <typename T>
class SAMPLECHARACTER_API FStateSingleLocal : public FStateTargetBase<UGameObjectLocal, T>
{
protected:
	//애님 블루프린트에 가장 최우선으로 상태를 전송해줘야한다.
	virtual void OnEnter(UGameObjectLocal* Owner) override
	{
		if (UAnimInstanceState* anim = Owner->GetLocal()->GetAnim())
		{
			anim->ChangeState(GetStateID(), 0, GetAniRandomCount());
		}
	}

	virtual void OnReEnter(UGameObjectLocal* Owner) override
	{

	}
	virtual void OnUpdate(UGameObjectLocal* Owner, float Delta) override
	{

	}
	virtual void OnExit(UGameObjectLocal* Owner) override
	{

	}
};

/**
 * 
 */
class SAMPLECHARACTER_API FStateSpawn : public FStateSingleLocal<FStateSpawn>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;
	virtual int GetAniRandomCount() override;

	virtual void OnEnter(UGameObjectLocal* Owner) override;
};

class SAMPLECHARACTER_API FStateIdle : public FStateSingleLocal<FStateIdle>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(UGameObjectLocal* Owner) override;
};

//캐릭터는 전방 이동과 후방이동으로 분류
class SAMPLECHARACTER_API FStateForwardWalk : public FStateSingleLocal<FStateForwardWalk>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(UGameObjectLocal* Owner) override;
	virtual void OnUpdate(UGameObjectLocal* Owner, float Delta) override;

	//Movement 쪽으로 이동
	void UpdateSpeed(UGameObjectLocal* Owner, float Speed);
};

class SAMPLECHARACTER_API FStateBackwardWalk : public FStateSingleLocal<FStateBackwardWalk>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(UGameObjectLocal* Owner) override;
	virtual void OnUpdate(UGameObjectLocal* Owner, float Delta) override;
};

class SAMPLECHARACTER_API FStateSideWalk : public FStateSingleLocal<FStateSideWalk>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(UGameObjectLocal* Owner) override;
	virtual void OnUpdate(UGameObjectLocal* Owner, float Delta) override;
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
	virtual void OnEnter(UGameObjectLocal* Owner) override;
	virtual void OnUpdate(UGameObjectLocal* Owner, float Delta) override;
};


//Uppper
class SAMPLECHARACTER_API FStateUpperIdle : public FStateSingleLocal<FStateUpperIdle>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(UGameObjectLocal* Owner) override;
};

class SAMPLECHARACTER_API FStateAttack : public FStateSingleLocal<FStateAttack>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(UGameObjectLocal* Owner) override;
	virtual void OnUpdate(UGameObjectLocal* Owner, float Delta) override;
};
