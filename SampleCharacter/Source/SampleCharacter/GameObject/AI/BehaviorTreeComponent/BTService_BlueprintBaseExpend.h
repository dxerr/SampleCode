// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "GameObject/Define/GameObjectDefine.h"
#include "BTService_BlueprintBaseExpend.generated.h"


class UGameObjectBase;

/**
 * 링크 에러가 발생할경우
 * <ProjectName>.Build.cs 에서 다음 두 항목을 추가 : "AIModule", "GameplayTasks"
 * PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "GameplayTasks" });
 */
UCLASS(Blueprintable)
class SAMPLECHARACTER_API UBTService_BlueprintBaseExpend : public UBTService_BlueprintBase
{
	GENERATED_BODY()
	
public: 
    UFUNCTION(BlueprintCallable, Category = "AI|Ex")
    FORCEINLINE AActor* GetActorOwner() { return ActorOwner ; }

    UFUNCTION(BlueprintCallable, Category = "AI|Ex")
    UBlackboardData* GetBlackboardData();
};
