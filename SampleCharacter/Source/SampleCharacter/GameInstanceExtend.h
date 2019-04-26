// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Controller/ObjectSpawner.h"
#include "GameInstanceExtend.generated.h"

class FGameObjectLocal;
class APlayerControllerExpend;

/**
 * 임시 각 매니져 관리 클래스
 * Tick 클래스를 통해 Udpate를 제공받고 각종 매니져 클래스에 전파
 */
UCLASS()
class SAMPLECHARACTER_API UGameInstanceExtend : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UGameInstanceExtend();

	FORCEINLINE UObjectSpawner* GetSpawner()				{ return Spawner; }
	
public:
	virtual void Init() override;
	virtual void Shutdown() override;

	bool Tick(float Delta);

public:
	//로컬 캐릭터 스폰
	UFUNCTION(BlueprintCallable, meta = (Tooltip = ""), Category = Pawn)
	void SpawnPlayer(TSubclassOf<ACharacter> ActorClass, const FVector& StartPos, const FVector& Offset);

	//지형위에 스폰되는 함수 제공
	//ACharacter 클래스에는 UCharacterMovementComponent 가 제공해주고 있지만 APawn계열엔 없다.
	UFUNCTION(BlueprintCallable, meta = (Tooltip = ""), Category = Pawn)
	AActor* SpawnOnGround(TSubclassOf<AActor> ActorClass, const FVector& StartPos, const FVector& Offset);


private:
	FDelegateHandle TickDelegate;

	//스폰 관련 매니져 클래스
	UPROPERTY(Transient, VisibleInstanceOnly, Meta = (AllowPrivateAccess = true))
	UObjectSpawner* Spawner;
};
