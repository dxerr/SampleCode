// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/SkeletalMeshMerge.h"
#include "Components/SkeletalMeshComponent.h"
#include "SampleCharacter/Character/Define/PartsMergeDefine.h"
#include "SkeletalMeshMergeComponent.generated.h"

/**
 * 
 */
UCLASS(editinlinenew, meta = (BlueprintSpawnableComponent), ClassGroup = Rendering)
class SAMPLECHARACTER_API USkeletalMeshMergeComponent : public UActorComponent
{  
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Piece")
	TArray<USkeletalMesh*> PieceMeshes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Params")
	struct FSkeletalMeshMergeParams Params;

private:
	void ToMergeParams(const TArray<FSkelMeshMergeSectionMapping_BP>& InSectionMappings, TArray<FSkelMeshMergeSectionMapping>& OutSectionMappings);
	void ToMergeParams(const TArray<FSkelMeshMergeUVTransformMapping>& InUVTransformsPerMesh, TArray<FSkelMeshMergeUVTransforms>& OutUVTransformsPerMesh);

	USkeletalMesh* MergeToParams(const FSkeletalMeshMergeParams& Params);

public:
	USkeletalMesh* MergeToPieceMesh();
	USkeletalMesh* MergeToParams();
};
