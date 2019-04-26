// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonAIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardData.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "GameInstanceExtend.h"
#include "GameObject/ObjectClass/GameObjectBase.h"


ACommonAIController::ACommonAIController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{	
	BlackboardData = CreateDefaultSubobject<UBlackboardData>(TEXT("BlackboardData"));
}

void ACommonAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (nullptr == BlackboardData)
	{
		BlackboardData = NewObject<UBlackboardData>();
	}
	
}

bool ACommonAIController::RunBehaviorTree(UBehaviorTree* BTAsset)
{
	if (BlackboardData)
	{
		BTAsset->BlackboardAsset = BlackboardData;
	}

	return Super::RunBehaviorTree(BTAsset);
}

bool ACommonAIController::UseBlackboardEx(UBlackboardData* BlackboardAsset, UBlackboardComponent*& BlackboardComponent)
{
	if (BlackboardAsset)
	{
		BlackboardData = BlackboardAsset;
	}
	return UseBlackboard(BlackboardData, BlackboardComponent);
}

