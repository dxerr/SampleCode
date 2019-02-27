// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/Parts/Data/PartsData.h"
#include "PartsContainer.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHARACTER_API UPartsContainer : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FORCEINLINE const TArray<FPartsData>& GetPartsData() { return Parts; }

	UPROPERTY(EditAnywhere)
	FSkeletalMeshMergeParams Params;

	UPROPERTY(EditAnywhere)
	TArray<FPartsData> Parts;
};
