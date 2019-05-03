// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIModule/Classes/BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/BTFunctionLibrary.h"
#include "GameObject/Define/GameObjectDefine.h"
#include "BTFunctionLibraryExtend.generated.h"

class UGameObjectBase;

/**
BP에서 블랙보드 데이터 설정을 쉽게 하기 위한 구조체
변수이름에 해당하는 타입의 키이름을 입력하여 한번에 동기화를 맞춤
*/
USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FBTBlackboardDataParser
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Object;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Class;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Enum;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Int;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Float;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Bool;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString String;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Vector;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString Rotator;
};

/**
* 커스텀 작성한 유틸 함수에서 셋팅하여 던저주는 블랙보드 타입형 구조체
* 스태틱 변수로 들고 있어 값 설정 변경시 공유되므로(덮어써짐) 사용상 주의가 필요
*/
USTRUCT(BlueprintType)
struct SAMPLECHARACTER_API FBTBlackboardDataResult
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UObject* Object;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UClass* Class;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    uint8 Enum;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    int32 Int;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    float Float;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    bool Bool;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FString String;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FName Name;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FVector Vector;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FRotator Rotator;

    void Reset();
};

/**
 * BT 관련 유틸 확장 함수 모음
 * 프로젝트에서는 블랙보드 데이터가 픽스된 형태로 강제한다. (BT 내부에 블랙보드 포함)
 * BT를 하나의 데이터 형태로 묶어버림으로써 블프 로직을 간결하게 만든다.
 */
UCLASS()
class SAMPLECHARACTER_API UBTFunctionLibraryExtend : public UBTFunctionLibrary
{
	GENERATED_BODY()
	
private:
    template<class TDataClass>
    static TMap<int, typename TDataClass::FDataType> BlackboardRegister;
    static FBTBlackboardDataResult BlackboardData;


public:
    //언리얼 객체가 아닌 UGameObject 객체로 형변환 지원
    UFUNCTION(BlueprintPure, Category = "AI|Ex", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
    static UGameObjectBase* GetBlackboardValueAsGameObject(UBTNode* NodeOwner, const FBlackboardKeySelector& Key);

    //간편 블랙보드 데이터 동기화(내부 로직에서 FBTBlackboardDataResult를 Return값으로 지원되는 함수가 페어로 필요하다)
    UFUNCTION(BlueprintCallable, Category = "AI|Ex", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
    static void SetBlackboardData(UBTNode* NodeOwner, const FBTBlackboardDataResult& Result, const FBTBlackboardDataParser& Parser);

    //내부 로직에서 등록한 정보를 바탕으로 블랙보드 데이터 동기화
    UFUNCTION(BlueprintCallable, Category = "AI|Ex", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
    static void SetRegistBlackboardData(UBTNode* NodeOwner, const FBTBlackboardDataParser& Parser);

    //디버그용으로 현재 등록중인 데이터 정보 보기(현재 미구현)
    UFUNCTION(BlueprintCallable, Category = "AI|Ex", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner", ToolTip = "디버깅 전용"))
    static FBTBlackboardDataResult GetRegistBlackboardData();

protected:
    //블랙보드 정보 자동 갱신관련 등록
    template<class TDataClass>
    static void RegisterBlackboardData(typename TDataClass::FDataType Value);

	
    //하위 유틸 함수들
    //[Todo]
    //이 클래스를 상속받아 하위 클래스로 세분화 할지 다른 클래스에서 작성할지 고민 필요
    //FBTBlackboardDataResult 를 리턴하는 함수의 경우 함수명으로 구분하기 쉽게 작성 (접두어 BB)
public:
    //Radius : 0 미만 = 무한대
    UFUNCTION(BlueprintCallable, Category = "AI|Ex", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
    static TArray<UGameObjectBase*> FindObject(UBTNode* NodeOwner, AActor* ActorOwner, EGameObjectType ObjectType, float Radius = -1.f);

    UFUNCTION(BlueprintCallable, Category = "AI|Ex", Meta = (HidePin = "NodeOwner", DefaultToSelf = "NodeOwner"))
    static FBTBlackboardDataResult& BB_FindFirstObject(UBTNode* NodeOwner, AActor* ActorOwner, EGameObjectType ObjectType, float Radius = -1.f);
};

template<class TDataClass>
void UBTFunctionLibraryExtend::RegisterBlackboardData(typename TDataClass::FDataType Value)
{
    int key = sizeof(TDataClass);
    if (BlackboardRegister<TDataClass>.Contains(key))
    {
        BlackboardRegister<TDataClass>[key] = Value;
    }
    else
    {
        BlackboardRegister<TDataClass>.Add(key, Value);
    }
};
