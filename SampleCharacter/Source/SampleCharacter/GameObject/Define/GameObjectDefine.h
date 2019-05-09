// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObjectDefine.generated.h"

/**
 * 오브젝트 클래스 관련 EunmType/Define 모음
 */


/**
* Bit Mask Define
*/
#define CHECK_FLAG_TYPE(Type, Flag)     (((Type) & static_cast<uint8>(Flag)) > 0)
#define SET_FLAG_TYPE(Type, Flag)       (Type |= static_cast<uint8>(Flag))
#define REMOVE_FLAG_TYPE(Type, Flag)    (Type &= ~static_cast<uint8>(Flag))
#define CLEAR_FLAG_TYPE(Type)           (Type = 0x000)


//UENUM이 uint8밖에 지원하지 않는다 Base 타입은 None으로 두어 일단 하나의 여분을 챙겨둔다.
//확장성에 제한이 많이 생길것 같아서, 추후 확장이 필요할 경우 bitMask를 포기..
//포기하였을 경우 동급 레이어에 해당 하는 타입에 대한 고민 필요(ex Static, Projectile, Dynamic, Vehicle)
//즉 Base타입은 All과 같음
UENUM(BlueprintType, meta = (Bitflags))
enum class EGameObjectType : uint8
{
	Base		= 0x000,		// All
	Static		= 0x001,
	Projectile	= 0x002,
	Vehicle		= 0x004,
	Dynamic		= 0x008,
	Player		= 0x010,
	NonPlayer	= 0x020,
	OtherPlayer = 0x040,
	LocalPlayer = 0x080,
};

ENUM_CLASS_FLAGS(EGameObjectType);

//[Todo] Enum Loop에 대한 더 좋은 방법이 있다면 수정한다.
static const EGameObjectType EGameObjectTypeALL[] = 
{ 
	EGameObjectType::Base, EGameObjectType::Static, EGameObjectType::Projectile, EGameObjectType::Vehicle,  
	EGameObjectType::Dynamic, EGameObjectType::Player, EGameObjectType::NonPlayer, EGameObjectType::OtherPlayer,
	EGameObjectType::LocalPlayer
};
static const int EGameObjectTypeALLCount = int(sizeof(EGameObjectTypeALL) / sizeof(*EGameObjectTypeALL));


/**
* 이동 관련 타입 설정
* None : 정지를 의미한다.
*/
UENUM(BlueprintType, meta = (Bitflags))
enum class EGameObjectMoveType : uint8
{
    None = 0x000,
    Walk = 0x001,
    Run = 0x002,
    Interpolation = 0x004,      //추후 이동 동기화 관련 필요성이 있을지도...
    Jump = 0x008,               //미사용 가능성이 있음
};

//이동 스타일 타입
UENUM(BlueprintType)
enum class EGameObjectMoveDirType : uint8
{
    Forward,
    SideStep,
    Backward,
};



