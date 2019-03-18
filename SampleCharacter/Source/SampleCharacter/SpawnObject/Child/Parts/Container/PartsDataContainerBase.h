// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SpawnObject/Child/Parts/Data/PartsDataBase.h"
#include "PartsDataContainerBase.generated.h"

/**
 *
 */
UCLASS()
class SAMPLECHARACTER_API UPartsDataContainerBase : public UDataAsset
{
	GENERATED_BODY()

public:
	FORCEINLINE const TArray<FPartsDataBase>& GetPartsData() { return Parts; }

	UPROPERTY(EditAnywhere)
	FSkeletalMeshMergeParams Params;

	UPROPERTY(EditAnywhere)
	TArray<FPartsDataBase> Parts;
};
