// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Controller/Input/InputBindingBase.h"
#include "GameObject/Parts/Data/PartsDataBase.h"
#include "InputBindingLocalPlayer.generated.h"

class UGameObjectLocal;
/**
 * 
 */
UCLASS(DefaultToInstanced)
class SAMPLECHARACTER_API UInputBindingLocalPlayer : public UInputBindingBase
{
	GENERATED_BODY()
	
	DECLARE_DELEGATE_OneParam(FOnAttack1, int32);
	DECLARE_DELEGATE_OneParam(FOnAttachParts, EPartsType);

public:
	virtual void Initialize() override;
	virtual void Initialize(UGameObjectLocal* target);
	virtual void SetBinding(UInputComponent* input) override;

protected:
	//Local Character Bind
	void OnAttachParts(EPartsType Type);
	void OnAttack1(int32 slot);
	void OnMoveForward();
	void OnMoveBackward();
	void OnMoveLeft();
	void OnMoveRight();
	void OnMoveStop();
	void OnMoveRotate(float Value);
	void OnMoveRotateYaw(float Value);
	void OnMoveRotatePitch(float Value);
	//

protected:
	UGameObjectLocal* Target;
};
