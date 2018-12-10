// Fill out your copyright notice in the Description page of Project Settings.
#include "MyCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/SpringArmComponent.h"

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

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();

	MergeComponent = FindComponentByClass<USkeletalMeshMergeComponent>();

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
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//TestMerge
	PlayerInputComponent->BindAction("PartsMerge", IE_Released, this, &AMyCharacter::OnPartsMerge);
	PlayerInputComponent->BindAction("PartsSimpleMerge", IE_Released, this, &AMyCharacter::OnPartsSimpleMerge);
	//Movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AMyCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMyCharacter::MoveRight);

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

void AMyCharacter::MoveForward(float Value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(dir, Value);

	//Test 애니메이션 재생
	UAnimInstance* ani = GetMesh()->GetAnimInstance();
	UAnimMontage* montage = ani->GetCurrentActiveMontage();
	ani->PlaySlotAnimationAsDynamicMontage(montage, TEXT("Move"));

	GAME_LOG("Move Test Log");
}

void AMyCharacter::MoveRight(float Value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(dir, Value);
}