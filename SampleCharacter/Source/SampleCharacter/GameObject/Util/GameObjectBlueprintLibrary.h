// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameObject/ObjectClass/GameObjectBase.h"
#include "GameObjectBlueprintLibrary.generated.h"

/**
 * GameObject 관련 BP 제공 유틸함수 모음
 */
UCLASS()
class SAMPLECHARACTER_API UGameObjectBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	//캐릭터 찾기
    UFUNCTION(BlueprintPure, Category = "GameObject", Meta = (WorldContext = "WorldContextObject"))
    static UGameObjectBase* FindGameObject(UObject* WorldContextObject, EGameObjectType ObjectType);

    UFUNCTION(BlueprintPure, Category = "GameObject", Meta = (WorldContext = "WorldContextObject"))
    static TArray<UGameObjectBase*> FindGameObjects(UObject* WorldContextObject, EGameObjectType ObjectType);	
};
