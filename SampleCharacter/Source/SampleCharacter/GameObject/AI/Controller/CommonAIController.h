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
	
	//블루프린트 Visible용 블랙보드 키 리스트
    struct FBlackboardKeys
    {
        TArray<FString> Keys;
        FString SelectKey;
    };

public:
	ACommonAIController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	virtual void PostInitializeComponents() override;

protected:
    virtual void OnPossess(APawn* InPawn) override;

public:
	virtual bool RunBehaviorTree(UBehaviorTree* BTAsset) override;

//블랙보드 데이터 접근용 유틸 함수
protected:
    //UFUNCTION(BlueprintCallable, Category = "AI|BehaviorTree|Ex")
    //void SetBlackboardData(FBlackboardKeys Value);
};
