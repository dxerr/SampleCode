// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Global/GlobalDefine.h"
#include "Component/SkeletalMeshMergeComponent.h"
#include "MyCharacter.generated.h"

class UMyAnimInstance;
class FFSMManager;
class FSkillManager;
class FPartsManager;
//enum class EPartsType;

UCLASS()
class SAMPLECHARACTER_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()
	
	DECLARE_DELEGATE_OneParam(FOnAttack1, int32);
	DECLARE_DELEGATE_TwoParams(FOnAttachParts, bool, EPartsType);

	//ĳ���� ���󰡱� ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	//���� ���� ���۳�Ʈ
	USkeletalMeshMergeComponent* MergeComponent;
	//���� ���̷�Ż �޽� ����
	USkeletalMesh* CurrSkeletalMesh;
	//Anim
	UMyAnimInstance* Animation;
	//FSM
	FFSMManager* LowwerFsm;
	FFSMManager* UpperFsm;
	//Skill
	FSkillManager* SkillMgr;
	//Parts
	FPartsManager* PartsMgr;

public:
	//FORCEINLINE : Virtual ó���� �Ұ��� �Ѱ����� �˰��ִµ� ���� �����ɼ� ����..
	FORCEINLINE UMyAnimInstance* GetAnimInstance()	{ return Animation;}
	FORCEINLINE FSkillManager* GetSKillManager()	{ return SkillMgr ;}
	FORCEINLINE FPartsManager* GetPartsManager()	{ return PartsMgr; }

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void OnPartsSimpleMerge();
	void OnPartsMerge();
	void OnMoveForward(float Value);
	void OnMoveRight(float Value);
	void OnAttachParts(bool Attach, EPartsType Type);
	void OnAttack1(int32 slot);

	void TestMove();
	void TestStop();

public:	
	// Sets default values for this character's properties
	AMyCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
