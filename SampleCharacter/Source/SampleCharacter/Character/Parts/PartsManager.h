// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Public/SkeletalMeshMerge.h"
#include "Data/PartsData.h"
#include "PartsContainer.h"

class UActorComponent;
class AMyCharacter;

/**
 * 
 */
class SAMPLECHARACTER_API FPartsManager
{
public:
	void Initialize(AMyCharacter* Character);
	void LoadData(const TCHAR * Path);

	void Attach(EPartsType Type, ...);
	void Detach(EPartsType Type, ...);

	const FPartsData* GetParts(EPartsType Type);

private:
	USkeletalMesh* MergeParts(const TArray<USkeletalMesh*>& Parts) const;

	void ToMergeParams(const TArray<FSkelMeshMergeSectionMapping_BP>& InSectionMappings, TArray<FSkelMeshMergeSectionMapping>& OutSectionMappings);
	void ToMergeParams(const TArray<FSkelMeshMergeUVTransformMapping>& InUVTransformsPerMesh, TArray<FSkelMeshMergeUVTransforms>& OutUVTransformsPerMesh);

	USkeletalMesh* MergeToParams(const FSkeletalMeshMergeParams& Params);


private:
	AMyCharacter* Owner;
	UActorComponent* ActorComponent;
	UPartsContainer* PartsFctory;
};
