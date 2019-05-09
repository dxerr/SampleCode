// Fill out your copyright notice in the Description page of Project Settings.


#include "BTFunctionLibraryExtend.h"
#include "AIModule/Classes/BehaviorTree/BTNode.h"
#include "AIModule/Classes/BehaviorTree/BlackboardComponent.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Class.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Enum.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Int.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_String.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Name.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType_Rotator.h"
#include "GameInstanceExtend.h"
#include "GameObject/ObjectClass/GameObjectBase.h"


#define DEF_SETBLACKBOARDDATA(bc, name, p, v)       if(!p.##name.IsEmpty()) { bc->SetValueAs##name(*p.##name, v.##name); }
#define DEF_SETREGBLACKBOARDDATA(bc, name, p, v)    if (!p.##name.IsEmpty()) { int key = sizeof(UBlackboardKeyType_##name); \
                                                    if (v<UBlackboardKeyType_##name>.Contains(key)) \
                                                        { bc->SetValueAs##name(*p.##name, v<UBlackboardKeyType_##name>[key]); } }
#define DEF_CLEARBLACKBOARDDATA(bc, name, p)        if(!p.##name.IsEmpty()) { bc->ClearValue(*p.##name); }


template<class TDataClass> TMap<int, typename TDataClass::FDataType> UBTFunctionLibraryExtend::BlackboardRegister;
FBTBlackboardDataResult UBTFunctionLibraryExtend::BlackboardData;

void FBTBlackboardDataResult::Reset()
{
    Object  = NULL;
    Class   = NULL;
    Enum    = 0;
    Int     = 0; 
    Float   = 0.f;
    Bool    = false;
    Name    = TEXT("");
    Vector  = FVector::ZeroVector;
    Rotator = FRotator::ZeroRotator;
    String.Empty();
}

FBTBlackboardDataResult UBTFunctionLibraryExtend::GetRegistBlackboardData()
{
    FBTBlackboardDataResult result;
#if WITH_EDITOR
#endif
    return result;
}


UGameObjectBase* UBTFunctionLibraryExtend::GetBlackboardValueAsGameObject(UBTNode* NodeOwner, const FBlackboardKeySelector& Key)
{
    return Cast<UGameObjectBase>(Super::GetBlackboardValueAsObject(NodeOwner, Key));
}

UObject* UBTFunctionLibraryExtend::GetBlackboardValueAsObjectEx(UBTNode* NodeOwner, const FName& KeyName)
{
    UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner);
    return BlackboardComp ? BlackboardComp->GetValueAsObject(KeyName) : nullptr;
}

AActor* UBTFunctionLibraryExtend::GetBlackboardValueAsActorEx(UBTNode* NodeOwner, const FName& KeyName)
{
    return Cast<AActor>(GetBlackboardValueAsObjectEx(NodeOwner, KeyName));
}

UClass* UBTFunctionLibraryExtend::GetBlackboardValueAsClassEx(UBTNode* NodeOwner, const FName& KeyName)
{
    UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner);
    return BlackboardComp ? BlackboardComp->GetValueAsClass(KeyName) : nullptr;
}

uint8 UBTFunctionLibraryExtend::GetBlackboardValueAsEnumEx(UBTNode* NodeOwner, const FName& KeyName)
{
    UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner);
    return BlackboardComp ? BlackboardComp->GetValueAsEnum(KeyName) : 0;
}

int32 UBTFunctionLibraryExtend::GetBlackboardValueAsIntEx(UBTNode* NodeOwner, const FName& KeyName)
{
    UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner);
    return BlackboardComp ? BlackboardComp->GetValueAsInt(KeyName) : 0;
}

float UBTFunctionLibraryExtend::GetBlackboardValueAsFloatEx(UBTNode* NodeOwner, const FName& KeyName)
{
    UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner);
    return BlackboardComp ? BlackboardComp->GetValueAsFloat(KeyName) : 0.0f;
}

bool UBTFunctionLibraryExtend::GetBlackboardValueAsBoolEx(UBTNode* NodeOwner, const FName& KeyName)
{
    UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner);
    return BlackboardComp ? BlackboardComp->GetValueAsBool(KeyName) : false;
}

FString UBTFunctionLibraryExtend::GetBlackboardValueAsStringEx(UBTNode* NodeOwner, const FName& KeyName)
{
    UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner);
    return BlackboardComp ? BlackboardComp->GetValueAsString(KeyName) : FString();
}

FName UBTFunctionLibraryExtend::GetBlackboardValueAsNameEx(UBTNode* NodeOwner, const FName& KeyName)
{
    UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner);
    return BlackboardComp ? BlackboardComp->GetValueAsName(KeyName) : NAME_None;
}

FVector UBTFunctionLibraryExtend::GetBlackboardValueAsVectorEx(UBTNode* NodeOwner, const FName& KeyName)
{
    UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner);
    return BlackboardComp ? BlackboardComp->GetValueAsVector(KeyName) : FVector::ZeroVector;
}

FRotator UBTFunctionLibraryExtend::GetBlackboardValueAsRotatorEx(UBTNode* NodeOwner, const FName& KeyName)
{
    UBlackboardComponent* BlackboardComp = GetOwnersBlackboard(NodeOwner);
    return BlackboardComp ? BlackboardComp->GetValueAsRotator(KeyName) : FRotator::ZeroRotator;
}

UGameObjectBase* UBTFunctionLibraryExtend::GetBlackboardValueAsGameObjectEx(UBTNode* NodeOwner, const FName& KeyName)
{
    return Cast<UGameObjectBase>(GetBlackboardValueAsObjectEx(NodeOwner, KeyName));
}

void UBTFunctionLibraryExtend::SetBlackboardData(UBTNode* NodeOwner, const FBTBlackboardDataResult& Result, const FBTBlackboardDataParser& Parser)
{
    if (UBlackboardComponent* bb = GetOwnersBlackboard(NodeOwner))
    {
        DEF_SETBLACKBOARDDATA(bb, Object, Parser, Result);
        DEF_SETBLACKBOARDDATA(bb, Class, Parser, Result);
        DEF_SETBLACKBOARDDATA(bb, Enum, Parser, Result);
        DEF_SETBLACKBOARDDATA(bb, Int, Parser, Result);
        DEF_SETBLACKBOARDDATA(bb, Float, Parser, Result);
        DEF_SETBLACKBOARDDATA(bb, Bool, Parser, Result);
        DEF_SETBLACKBOARDDATA(bb, String, Parser, Result);
        DEF_SETBLACKBOARDDATA(bb, Name, Parser, Result);
        DEF_SETBLACKBOARDDATA(bb, Vector, Parser, Result);
        DEF_SETBLACKBOARDDATA(bb, Rotator, Parser, Result);
    }
}

void UBTFunctionLibraryExtend::SetBlackboardEmptyData(UBTNode* NodeOwner, const FBTBlackboardDataParser& Parser)
{
    if (UBlackboardComponent* bb = GetOwnersBlackboard(NodeOwner))
    {
        DEF_CLEARBLACKBOARDDATA(bb, Object, Parser);
        DEF_CLEARBLACKBOARDDATA(bb, Class, Parser);
        DEF_CLEARBLACKBOARDDATA(bb, Enum, Parser);
        DEF_CLEARBLACKBOARDDATA(bb, Int, Parser);
        DEF_CLEARBLACKBOARDDATA(bb, Float, Parser);
        DEF_CLEARBLACKBOARDDATA(bb, Bool, Parser);
        DEF_CLEARBLACKBOARDDATA(bb, String, Parser);
        DEF_CLEARBLACKBOARDDATA(bb, Name, Parser);
        DEF_CLEARBLACKBOARDDATA(bb, Vector, Parser);
        DEF_CLEARBLACKBOARDDATA(bb, Rotator, Parser);
    }
}

void UBTFunctionLibraryExtend::SetRegistBlackboardData(UBTNode* NodeOwner, const FBTBlackboardDataParser& Parser)
{
    if (UBlackboardComponent* bb = GetOwnersBlackboard(NodeOwner))
    {
        DEF_SETREGBLACKBOARDDATA(bb, Object, Parser, BlackboardRegister);
        DEF_SETREGBLACKBOARDDATA(bb, Class, Parser, BlackboardRegister);
        DEF_SETREGBLACKBOARDDATA(bb, Enum, Parser, BlackboardRegister);
        DEF_SETREGBLACKBOARDDATA(bb, Int, Parser, BlackboardRegister);
        DEF_SETREGBLACKBOARDDATA(bb, Float, Parser, BlackboardRegister);
        DEF_SETREGBLACKBOARDDATA(bb, Bool, Parser, BlackboardRegister);
        DEF_SETREGBLACKBOARDDATA(bb, String, Parser, BlackboardRegister);
        DEF_SETREGBLACKBOARDDATA(bb, Name, Parser, BlackboardRegister);
        DEF_SETREGBLACKBOARDDATA(bb, Vector, Parser, BlackboardRegister);
        DEF_SETREGBLACKBOARDDATA(bb, Rotator, Parser, BlackboardRegister);
    }
}

TArray<UGameObjectBase*> UBTFunctionLibraryExtend::FindObject(UBTNode* NodeOwner, AActor* ActorOwner, EGameObjectType ObjectType, float Radius)
{
    TArray<UGameObjectBase*> finds;
    if (UGameInstanceExtend* gameInst = Cast<UGameInstanceExtend>(ActorOwner->GetGameInstance()))
    {
        finds = gameInst->GetSpawner()->FindObjects(ObjectType);
        if (Radius > 0.f)
        {
            return finds.FilterByPredicate([=](UGameObjectBase* el)
                {
                    //Movement등에서 제공되는 함수로 대체가 필요할수 있다.
                    if (AActor* a = el->GetActor())
                    {
                        if (Radius > a->GetDistanceTo(ActorOwner))
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

FBTBlackboardDataResult& UBTFunctionLibraryExtend::BB_FindFirstObject(UBTNode* NodeOwner, AActor* ActorOwner, EGameObjectType ObjectType, float Radius)
{
    TArray<UGameObjectBase*> finds = FindObject(NodeOwner, ActorOwner, ObjectType, Radius);

    BlackboardData.Reset();
    if (finds.Num() <= 0)
    {
        //블랙보드 정보 자동 갱신관련 등록
        RegisterBlackboardData<UBlackboardKeyType_Object>(NULL);
        RegisterBlackboardData<UBlackboardKeyType_Vector>(FVector::ZeroVector);

        //블랙보드 아웃 데이터 설정
        BlackboardData.Object = NULL;
        BlackboardData.Vector = FVector::ZeroVector;
    }
    else
    {
        UGameObjectBase* object = finds[0];
        FVector pos = object->GetActor()->GetActorLocation();

        //블랙보드 정보 자동 갱신관련 등록
        RegisterBlackboardData<UBlackboardKeyType_Object>(object);
        RegisterBlackboardData<UBlackboardKeyType_Vector>(pos);

        //블랙보드 아웃 데이터 설정
        BlackboardData.Object = object;
        BlackboardData.Vector = pos;
    }

    return BlackboardData;
}
