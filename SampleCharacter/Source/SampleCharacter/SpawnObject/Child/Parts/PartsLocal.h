// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PartsBase.h"
#include "Data/PartsDataBase.h"

class ALocalPlayerObject;

/**
 * 
 */
class SAMPLECHARACTER_API FPartsLocal : public FPartsBase
{
public:
	virtual void Initialize(FBaseObject* owner) override;

	virtual void Attach(EPartsType Type, ...) override;
	virtual void Detach(EPartsType Type, ...) override;

private:
	USkeletalMesh* MergeParts() const;

	void ToMergeParams(const TArray<FSkelMeshMergeSectionMapping_BP>& InSectionMappings, TArray<FSkelMeshMergeSectionMapping>& OutSectionMappings);
	void ToMergeParams(const TArray<FSkelMeshMergeUVTransformMapping>& InUVTransformsPerMesh, TArray<FSkelMeshMergeUVTransforms>& OutUVTransformsPerMesh);

	USkeletalMesh* MergeToParams(const FSkeletalMeshMergeParams& Params);

private:
	ALocalPlayerObject* Local;
	UActorComponent* ActorComponent;
};
