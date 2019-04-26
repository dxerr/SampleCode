// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "GameObject/Define/GameObjectDefine.h"
#include "CommonAIController.generated.h"

class UGameObjectBase;

/**
 * AAIController에서 구현된 기능 이외것을 구현해서 제공
 * 이클래스는 범용적으로 사용할수 있는 로직을 구현한다.
 * 특화된 로직들은 이클래스를 상속받아 구현
 */
UCLASS()
class SAMPLECHARACTER_API ACommonAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACommonAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void PostInitializeComponents() override;

public:
	virtual bool RunBehaviorTree(UBehaviorTree* BTAsset) override;

//BP지원 함수 모음
public:
	//BP로 이함수를 호출했을경우는 내부 블랙보드 데이터를 사용하지 않을경우이다.
	UFUNCTION(BlueprintCallable, Category = "AI|Ex")
	bool UseBlackboardEx(UBlackboardData* BlackboardAsset, UBlackboardComponent*& BlackboardComponent);
	
private:
	//블랙보드 데이터는 내부에서 사용 용도로 활용하는게 좋을것 같음
	UPROPERTY(transient, EditInstanceOnly, BlueprintReadOnly, Meta = (AllowPrivateAccess = true))
	class UBlackboardData* BlackboardData;
};
