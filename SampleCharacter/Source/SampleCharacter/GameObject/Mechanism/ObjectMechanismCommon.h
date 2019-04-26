// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameObject/Define/GameObjectDefine.h"
#include "ObjectMechanismCommon.generated.h"

/**
 * 오브젝트 관련 유틸성 함수는 모두 이곳에서 로직을 작성한다.
 * BT / 내부FSM 에서도 이곳 메서드를 이용하여 통일된 동작을 유도
 */
UCLASS()
class SAMPLECHARACTER_API UObjectMechanismCommon : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
public:
    //Radius : 0 미만 = 무한대
    UFUNCTION(BlueprintCallable, Category = "AI|Ex")
    static TArray<UGameObjectBase*> FindObject(AActor* Owner, EGameObjectType ObjectType, float Radius = -1.f);
	
};
