// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameObject/Component/Animation/AnimInstanceState.h"
#include "LocalCharacter.generated.h"

/**
* 언리얼 엔진 로직 담당 Local캐릭터 전용 클래스
* 로컬 BP제작시 이 클래스를 기반으로 제작
*/
UCLASS()
class SAMPLECHARACTER_API ALocalCharacter : public ACharacter
{
	GENERATED_BODY()

	//캐릭터 따라가기 카메라
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//InputBinder
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UInputBindingLocalPlayer* InputBinder;

public:
	// Sets default values for this character's properties
	ALocalCharacter();
	virtual ~ALocalCharacter();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	FORCEINLINE UAnimInstanceState* GetAnim() const { return Animation; }
	FORCEINLINE UInputBindingLocalPlayer* GetInputBinder() const { return InputBinder; }

private:
	//Anim
	UAnimInstanceState* Animation;
	
};
