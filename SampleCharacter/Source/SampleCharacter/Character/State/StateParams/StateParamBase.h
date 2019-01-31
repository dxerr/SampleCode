// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StateParamBase.generated.h"

//Lowwer State Define
UENUM()
enum class ECharacterStateBase : uint8
{
	None,
	Idle = 1,
	Walk,
	Run,

	BaseMax,
};

//Upper State Define
UENUM()
enum class  ECharacterStateUpperBase : uint8
{
	None,
	Attack = 1,

	BaseMax,
};

/**
 * 
 */
USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FStateParam
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ECharacterStateBase EStateType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Priority;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool Loop;

public:
	FStateParam() {}
	FStateParam(ECharacterStateBase Statetype)
	{
		EStateType = Statetype;
	}
};


USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FStateBaseParams
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere)
	TArray<FStateParam> Params;

public:
	FStateBaseParams()
	{
		//Params Enum 정의
		for (int32 e = 0; e < (int32)ECharacterStateBase::BaseMax; ++e)
		{
			if (Params.FindByPredicate([=](const FStateParam& el) {
				return static_cast<int32>(el.EStateType) == e; }))
			{
				continue;
			}

			ECharacterStateBase type(static_cast<ECharacterStateBase>(e));
			Params.Add(type);
		}
	}
};

//Upper State Struct
USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FStateUpperElement
{
	GENERATED_USTRUCT_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UAnimMontage* ResAni;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int ID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	int Priority;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool Loop;
};

USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FStateUpperParam
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	ECharacterStateUpperBase EStateType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TArray<FStateUpperElement> OriElements;
	
	TMap<int, FStateUpperElement> Elements;

public:
	FStateUpperParam()  {}									//미선언시 error C2512
	FStateUpperParam(ECharacterStateUpperBase Statetype) 
	{
		EStateType = Statetype;
	}

	void Init()
	{
		//저장소 옮기기
		Elements.Empty();
		for (auto el : OriElements) { Elements.Add(el.ID, el); }
	}
};

USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FStateUpperBaseParams
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FStateUpperParam> Params;

public:
	FStateUpperBaseParams()
	{
		//Params Enum 정의
		/*
		for (int32 e = 0; e < (int32)ECharacterStateUpperBase::BaseMax; ++e)
		{
			if (Params.FindByPredicate([=](const FStateUpperParam& el) {
				return static_cast<int32>(el.EStateType) == e; }))
			{
				continue;
			}

			ECharacterStateUpperBase type(static_cast<ECharacterStateUpperBase>(e));
			Params.Add(type);
		}*/

		//초기화
		for (auto &param : Params) 
		{ 
			param.Init(); 
		}
	}
};