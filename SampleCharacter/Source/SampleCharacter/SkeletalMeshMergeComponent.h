// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartsMergeDefine.h"
#include "Public/SkeletalMeshMerge.h"
#include "Components/SkeletalMeshComponent.h"
#include "SkeletalMeshMergeComponent.generated.h"

/**
 * 
 */
UCLASS(editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class SAMPLECHARACTER_API USkeletalMeshMergeComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Piece")
	TArray < USkeletalMesh*> PieceMeshes;

	UPROPERTY(EditAnywhere, Category = "Params")
	struct FSkeletalMeshMergeParams Params;

	void OnRegister() override;
	void OnUnregister() override;

public:
	void MergeToPieceMesh();
	USkeletalMesh* MergeToParams();

private:
	void ToMergeParams(const TArray<FSkelMeshMergeSectionMapping_BP>& InSectionMappings, TArray<FSkelMeshMergeSectionMapping>& OutSectionMappings);
	void ToMergeParams(const TArray<FSkelMeshMergeUVTransformMapping>& InUVTransformsPerMesh, TArray<FSkelMeshMergeUVTransforms>& OutUVTransformsPerMesh);

	USkeletalMesh* MergeToParams(const FSkeletalMeshMergeParams& Params);
};
