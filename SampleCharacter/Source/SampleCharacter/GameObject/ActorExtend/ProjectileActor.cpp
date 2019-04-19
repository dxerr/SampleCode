// Fill out your copyright notice in the Description page of Project Settings.

#include "ProjectileActor.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
}

//[Todo]
//현재는 임시 프로퍼티값 설정
//추후 타입에 맞는 데이터 구조체를 드리븐 받아 설정하든 에디터에서 설정하든 정해야될듯
void AProjectileActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	//임시 생명 주기 설정
	SetLifeSpan(2.f);

	//임시 중력 설정 (BP에서 설정함)
	
}

// Called when the game starts or when spawned
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

