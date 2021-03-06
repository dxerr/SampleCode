﻿// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Controller/Input/InputBindingLocalPlayer.h"

ALocalCharacter::~ALocalCharacter()
{
	UE_LOG(LogTemp, Warning, TEXT("Destroy"));
}

// Sets default values
ALocalCharacter::ALocalCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	InputBinder = CreateDefaultSubobject<UInputBindingLocalPlayer>(TEXT("CusomInputBinder"));
}

void ALocalCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Animation = Cast<UAnimInstanceState>(GetMesh()->GetAnimInstance());
}

// Called when the game starts or when spawned
void ALocalCharacter::BeginPlay()
{
	Super::BeginPlay();


	
}

// Called every frame
void ALocalCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALocalCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputBinder->SetBinding(PlayerInputComponent);
}
