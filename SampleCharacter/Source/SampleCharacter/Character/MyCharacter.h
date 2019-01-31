// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/GlobalDefine.h"
#include "Component/SkeletalMeshMergeComponent.h"
#include "MyCharacter.generated.h"	


UCLASS()
class SAMPLECHARACTER_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	//ĳ���� ���󰡱� ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//Animation
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* IdleMontage;
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* AttackMontage;
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* RunMontage;


	//�ִϸ��̼� Ÿ�̸� ����
	TMap<int32, float> MapAnimationTime;

	//�ִϸ��̼� End�̺�Ʈ ó��
	TMap<int32, FOnMontageEnded> MapAnimationEnd;

	//���� ���� ���۳�Ʈ
	USkeletalMeshMergeComponent* MergeComponent;

	//���� ���̷�Ż �޽� ����
	USkeletalMesh* CurrSkeletalMesh;

	class UMyAnimInstance* Animation;

public:
	// Sets default values for this character's properties
	AMyCharacter();


protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void OnPartsSimpleMerge();
	void OnPartsMerge();
	void OnMoveForward(float Value);
	void OnMoveRight(float Value);
	void OnAttack1();

	void TestMove();
	void TestStop();

protected:
	void OnAttackEnd(UAnimMontage* Montage, bool bInterrupted);

protected:
	void SetAniTimer(int32 ClassID, float Timer);
	void SetAniEndEvent(int32 ClassID, FOnMontageEnded EndEvent);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
