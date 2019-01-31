// Fill out your copyright notice in the Description page of Project Settings.
#include "MyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/Component/MyAnimInstance.h"
#include "State/StateIdle.h"

#if GAME_LOG_DEFINED
DEFINE_LOG_CATEGORY(GameLog);
#endif

// Sets default values
AMyCharacter::AMyCharacter()
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

	
}

void AMyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Animation = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	MergeComponent = FindComponentByClass<USkeletalMeshMergeComponent>();

	GetCharacterMovement()->SetMovementMode(MOVE_None);

	auto controller = UGameplayStatics::GetPlayerController(this, 0);
	if (controller)
	{
		controller->SetViewTarget(this);
	}
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->IsMovingOnGround() && GetVelocity().Equals(FVector::ZeroVector))
	{
		TestStop();
	}
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//TestMerge
	PlayerInputComponent->BindAction("PartsMerge", IE_Released, this, &AMyCharacter::OnPartsMerge);
	PlayerInputComponent->BindAction("PartsSimpleMerge", IE_Released, this, &AMyCharacter::OnPartsSimpleMerge);

	//key
	PlayerInputComponent->BindAction("Attack1", IE_Released, this, &AMyCharacter::OnAttack1);

	//Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::OnMoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &AMyCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AMyCharacter::AddControllerPitchInput);
}

void AMyCharacter::OnPartsSimpleMerge()
{
	if (nullptr != MergeComponent)
	{
		CurrSkeletalMesh = MergeComponent->MergeToPieceMesh();
		if (CurrSkeletalMesh)
		{
			auto mesh = GetMesh();
			CurrSkeletalMesh->Skeleton = mesh->SkeletalMesh->Skeleton;
			mesh->SetSkeletalMesh(CurrSkeletalMesh);
		}
	}
}

void AMyCharacter::OnPartsMerge()
{
	if (nullptr != MergeComponent)
	{
		CurrSkeletalMesh = MergeComponent->MergeToParams();
		if (CurrSkeletalMesh)
		{
			auto mesh = GetMesh();
			mesh->SetSkeletalMesh(CurrSkeletalMesh);
		}
	}
}

void AMyCharacter::OnAttack1()
{
	Animation->ChangeUpperState(ECharacterStateUpperBase::Attack, 1);
	/*
	UAnimInstance* ani = GetMesh()->GetAnimInstance();
	auto newmontage = ani->PlaySlotAnimationAsDynamicMontage(AttackMontage, TEXT("UpperBody"), 0.1f, 0.1f, 1.0f, 30.0f);
	float len = ani->Montage_Play(newmontage);
	SetAniTimer(AttackMontage->GetUniqueID(), len);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AMyCharacter::OnAttackEnd);
	ani->Montage_SetEndDelegate(EndDelegate);*/


}

void AMyCharacter::OnMoveForward(float Value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(dir, Value);
	if (!FMath::IsNearlyZero(Value) && GetCharacterMovement()->MovementMode == MOVE_None)
	{
		TestMove();
	}
}

void AMyCharacter::OnMoveRight(float Value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(dir, Value);
}

void AMyCharacter::TestMove()
{
	Animation->ChangeState(ECharacterStateBase::Walk);
	
	GetCharacterMovement()->SetMovementMode(MOVE_Walking);

	/*
	UAnimInstance* ani = GetMesh()->GetAnimInstance();
	float len = ani->Montage_Play(RunMontage);
	SetAniTimer(RunMontage->GetUniqueID(), len);*/

	GAME_LOG("Move Playing");
}

void AMyCharacter::TestStop()
{
	Animation->ChangeState(ECharacterStateBase::Idle);

	GetCharacterMovement()->SetMovementMode(MOVE_None);

	/*UAnimInstance* ani = GetMesh()->GetAnimInstance();
	float len = ani->Montage_Play(IdleMontage);
	SetAniTimer(IdleMontage->GetUniqueID(), len);*/

	GAME_LOG("Stop Playing");
}

void AMyCharacter::SetAniTimer(int32 ClassID, float Timer)
{
	float& time = MapAnimationTime.FindOrAdd(ClassID);
	time = Timer;
}

void AMyCharacter::SetAniEndEvent(int32 ClassID, FOnMontageEnded EndEvent)
{
	FOnMontageEnded& event = MapAnimationEnd.FindOrAdd(ClassID);
	event = EndEvent;
}

void AMyCharacter::OnAttackEnd(UAnimMontage* Montage, bool bInterrupted)
{
	TestStop();
}

