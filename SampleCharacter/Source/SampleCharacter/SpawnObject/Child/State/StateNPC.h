// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateBase.h"
#include "SpawnObject/Child/Component/Animation/AnimInstanceState.h"
#include "SpawnObject/Child/NonePcObject.h"

template <typename T>
class SAMPLECHARACTER_API FStateSingleNpc : public StateSingleton<T>, public FStateTargetBase<ANonePcObject>
{
protected:
	//�ִ� �������Ʈ�� ���� �ֿ켱���� ���¸� ����������Ѵ�.
	virtual void OnEnter(ANonePcObject* Owner) override
	{
		UAnimInstanceState* anim = Owner->GetAnim();
		anim->ChangeState(GetStateID());
	}

	virtual void OnReEnter(ANonePcObject* Owner) override
	{

	}
	virtual void OnUpdate(ANonePcObject* Owner, float Delta) override
	{

	}
	virtual void OnExit(ANonePcObject* Owner) override
	{

	}
};

/**
 * 
 */
class SAMPLECHARACTER_API FStateNpcIdle : public FStateSingleNpc<FStateNpcIdle>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnEnter(ANonePcObject* Owner) override;
};

class SAMPLECHARACTER_API FStateNpcBeaten : public FStateSingleNpc<FStateNpcBeaten>
{
public:
	virtual int GetStateID() override;
	virtual FString Name() override;

	virtual void OnUpdate(ANonePcObject* Owner, float Delta) override;
};
