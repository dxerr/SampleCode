// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameObject/Movement/MovementBase.h"
#include "GameObject/ObjectClass/GameObjectLocal.h"

/**
 * 
 */
class SAMPLECHARACTER_API FMovementLocal : public FMovementBase
{
public:
    virtual void Initialize(UGameObjectBase* Owner);
    virtual void DeInitialize();

    virtual void Update(float Delta);

public:
    inline UCharacterMovementComponent* GetCharMovement() const { return CharMovement; }

protected:
    virtual void OnStop() override;
    virtual void OnMove() override;

protected:
    UGameObjectLocal* Local;
    UCharacterMovementComponent* CharMovement;
};
