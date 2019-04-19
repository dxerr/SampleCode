// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GameObject/Parts/Data/PartsDataBase.h"
#include "PlayerControllerExpend.generated.h"

class FGameObjectBase;
class FGameObjectLocal;

/**
 * [Todo] 추후 글로벌 Input 관련 클래스로 작업할것
 * 임시로 UGameInstanceExtend 클래스에서 생성/관리
 */
UCLASS()
class SAMPLECHARACTER_API APlayerControllerExpend : public APlayerController
{
	GENERATED_BODY()
};
