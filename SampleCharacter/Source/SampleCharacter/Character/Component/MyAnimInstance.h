// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SAMPLECHARACTER_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlendMontage")
	UAnimMontage* UpperMontage;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "BlendMontage")
	UAnimMontage* LowerMontage;


public:
	UFUNCTION(BlueprintNativeEvent, Category = "Ani Functions")
	void OnPlayAni(const UAnimMontage* Upper, const UAnimMontage* Lowwer);

	void OnPlayAni_Implementation(const UAnimMontage* Upper, const UAnimMontage* Lowwer);

};
