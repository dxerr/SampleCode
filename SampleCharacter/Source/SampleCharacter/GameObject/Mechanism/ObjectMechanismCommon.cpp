// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectMechanismCommon.h"
#include "GameInstanceExtend.h"
#include "GameObject/ObjectClass/GameObjectBase.h"

TArray<UGameObjectBase*> UObjectMechanismCommon::FindObject(AActor* Owner, EGameObjectType ObjectType, float Radius)
{
    TArray<UGameObjectBase*> finds;
    if (UGameInstanceExtend* gameInst = Cast<UGameInstanceExtend>(Owner->GetGameInstance()))
    {
        finds = gameInst->GetSpawner()->FindObjects(ObjectType);
        if (Radius < 0.f)
        {
            return finds.FilterByPredicate([=](UGameObjectBase* el)
            {
                //Movement등에서 제공되는 함수로 대체가 필요할수 있다.
                if (AActor* a = el->GetActor())
                {
                    if (Radius > a->GetDistanceTo(Owner))
                    {
                        return true;
                    }
                }
                return false;
            });
        }
    }
    
    return finds;
}
