// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObjectBlueprintLibrary.h"
#include "GameInstanceExtend.h"

UGameObjectBase* UGameObjectBlueprintLibrary::FindGameObject(UObject* WorldContextObject, EGameObjectType ObjectType)
{
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    if (UGameInstanceExtend* gameInst = Cast<UGameInstanceExtend>(World->GetGameInstance()))
    {
        return gameInst->GetSpawner()->FindObject(ObjectType);
    }
    return NULL;
}

TArray<UGameObjectBase*> UGameObjectBlueprintLibrary::FindGameObjects(UObject* WorldContextObject, EGameObjectType ObjectType)
{
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
    TArray<UGameObjectBase*> finds;
    if (UGameInstanceExtend* gameInst = Cast<UGameInstanceExtend>(World->GetGameInstance()))
    {
        finds = gameInst->GetSpawner()->FindObjects(ObjectType);
    }
    return finds;
}
