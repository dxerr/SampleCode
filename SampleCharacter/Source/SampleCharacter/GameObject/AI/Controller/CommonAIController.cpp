// Fill out your copyright notice in the Description page of Project Settings.

#include "CommonAIController.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackBoardComponent.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BlackboardData.h"
#include "Runtime/AIModule/Classes/BehaviorTree/BehaviorTree.h"
#include "GameInstanceExtend.h"
#include "GameObject/ObjectClass/GameObjectBase.h"


ACommonAIController::ACommonAIController(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer)
{	
}

void ACommonAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
#if WITH_EDITOR

#endif
    
}

void ACommonAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);
}

bool ACommonAIController::RunBehaviorTree(UBehaviorTree* BTAsset)
{
    //블랙보드 설정


    UseBlackboard(BTAsset->BlackboardAsset, Blackboard);

	return Super::RunBehaviorTree(BTAsset);
}
