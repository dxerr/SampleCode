// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SkeletalMeshMergeComponent.h"
#include "Global/GlobalDefine.h"
#include "MyCharacter.generated.h"	


UCLASS()
class SAMPLECHARACTER_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

	//캐릭터 따라가기 카메라
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

	//애니메이션 길이 체크
	TMap<int32, float> MapAnimationTime;

	//파츠 머지 컴퍼넌트
	USkeletalMeshMergeComponent* MergeComponent;

	//최종 스켈레탈 메시 정보
	USkeletalMesh* CurrSkeletalMesh;

public:
	// Sets default values for this character's properties
	AMyCharacter();


protected:
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
	void SetAniTimer(int32 ClassID, float Timer);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
