// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/SkeletalMeshMerge.h"
#include "PartsMergeDefine.h"
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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	struct FSkeletalMeshMergeParams Params;

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	void OnPartsMerge();

public:
	void ToMergeParams(const TArray<FSkelMeshMergeSectionMapping_BP>& InSectionMappings, TArray<FSkelMeshMergeSectionMapping>& OutSectionMappings);
	void ToMergeParams(const TArray<FSkelMeshMergeUVTransformMapping>& InUVTransformsPerMesh, TArray<FSkelMeshMergeUVTransforms>& OutUVTransformsPerMesh);

	USkeletalMesh* MergeMeshes(const FSkeletalMeshMergeParams& Params);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
