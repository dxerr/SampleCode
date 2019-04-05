// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpawnObject/CharacterObject.h"
#include "Parts/Data/PartsDataBase.h" //EPartsType
#include "LocalPlayerObject.generated.h"

//���� ����
class UAnimInstanceState;
class FSKillLocal;
class FPartsLocal;
class FFSMManager;

UCLASS()
class SAMPLECHARACTER_API ALocalPlayerObject : public ACharacterObject
{
	GENERATED_BODY()
	
	DECLARE_DELEGATE_OneParam(FOnAttack1, int32);
	DECLARE_DELEGATE_OneParam(FOnAttachParts, EPartsType);
	
	//ĳ���� ���󰡱� ī�޶�
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

protected:
	//Input Binding
	

	void OnMoveForward();
	void OnMoveBackward();
	void OnMoveLeft();
	void OnMoveRight();
	void OnMoveStop();
	void OnMoveRotate(float Value);
	void OnAttachParts(EPartsType Type);
	void OnAttack1(int32 slot);

public:
	// Sets default values for this character's properties
	ALocalPlayerObject();
	~ALocalPlayerObject();

protected:
	virtual void PostInitializeComponents() override;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginDestroy() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	//Anim
	UAnimInstanceState* Animation;
	//FSM
	FFSMManager* LowwerFsm;
	FFSMManager* UpperFsm;
	//Skill
	FSKillLocal* SkillMgr;
	//Parts
	FPartsLocal* PartsMgr;

public:
	//FORCEINLINE : Virtual ó���� �Ұ��� �Ѱ����� �˰��ִµ� ���� �����ɼ� ����..
	FORCEINLINE UAnimInstanceState* GetAnim() { return Animation; }
	FORCEINLINE FSKillLocal* GetSKill() { return SkillMgr; }
	FORCEINLINE FPartsLocal* GetParts() { return PartsMgr; }
	FORCEINLINE FFSMManager* GetLowwerState() { return LowwerFsm; }
	FORCEINLINE FFSMManager* GetUpperState() { return UpperFsm; }

	//Movement�� �̰��ʿ�
	float MovementForce;
	FORCEINLINE void SetMoveSpeed(float val) { MovementForce = val; }
};
