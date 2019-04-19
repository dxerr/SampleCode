// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GameObject/Parts/Data/PartsDataBase.h"
#include "InputBinderLocal.generated.h"

class UInputComponent;
class FGameObjectLocal;
/**
* 내캐릭터 입력 바인딩 처리 클래스
*공통 입력 처리는 추후 상위 클래스에서 처리
*[Todo] UObject 클래스가 아니라도 바인딩 시킬수 있는 방법 확인
*/
// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInputBinderLocal : public UInterface
{
	GENERATED_BODY()
	
	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
	DECLARE_DELEGATE_OneParam(FOnAttack1, int32);
	DECLARE_DELEGATE_OneParam(FOnAttachParts, EPartsType);

public:
	void InitBind(FGameObjectLocal* Owner, UInputComponent* InputComponent);

private:
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

private:
	FGameObjectLocal* Local;
};

/**
 * 
 */
class SAMPLECHARACTER_API IInputBinderLocal 
{
	GENERATED_BODY()
};
