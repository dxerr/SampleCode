#pragma once

#include "CoreMinimal.h"
#include "GameObject/Parts/Data/PartsDataBase.h"
#include "Runtime/Engine/Classes/Engine/DataAsset.h"
#include "PartsDataContainerBase.generated.h"


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
