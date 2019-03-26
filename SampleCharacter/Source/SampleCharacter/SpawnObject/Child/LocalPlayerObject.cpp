// Fill out your copyright notice in the Description page of Project Settings.

#include "LocalPlayerObject.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Component/Animation/AnimInstanceState.h"
#include "State/FSMManager.h"
#include "State/StateLocal.h"
#include "Skill/SKillLocal.h"
#include "Parts/PartsLocal.h"

// Sets default values
ALocalPlayerObject::ALocalPlayerObject()
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

void ALocalPlayerObject::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	Animation = Cast<UAnimInstanceState>(GetMesh()->GetAnimInstance());
	if (!LowwerFsm)
	{
		LowwerFsm = new FFSMManager();
		LowwerFsm->Initialize(this);
	}
	if (!UpperFsm)
	{
		UpperFsm = new FFSMManager();
		UpperFsm->Initialize(this);
	}

	if (!SkillMgr)
	{
		SkillMgr = new FSKillLocal();
		SkillMgr->Initialize(this);
		SkillMgr->LoadData(TEXT("SkillDataContainerBase'/Game/Resource/DataAsset/LocalSkills.LocalSkills'"));
	}

	if (!PartsMgr)
	{
		PartsMgr = new FPartsLocal();
		PartsMgr->Initialize(this);
		PartsMgr->LoadData(TEXT("PartsDataContainerBase'/Game/Resource/DataAsset/LocalParts.LocalParts'"));
	}
}

// Called when the game starts or when spawned
void ALocalPlayerObject::BeginPlay()
{
	Super::BeginPlay();

	LowwerFsm->ChangeState<FStateIdle>();
	//파츠 장착
	PartsMgr->AttachAll();

	auto controller = UGameplayStatics::GetPlayerController(this, 0);
	if (controller)
	{
		controller->SetViewTarget(this);
	}
}

// Called every frame
void ALocalPlayerObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (LowwerFsm)
	{
		LowwerFsm->Update(DeltaTime);
	}

	if (UpperFsm)
	{
		UpperFsm->Update(DeltaTime);
	}
}

// Called to bind functionality to input
void ALocalPlayerObject::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction<FOnAttachParts>("AttachPartsH", IE_Released, this, &ALocalPlayerObject::OnAttachParts, EPartsType::HEAD);
	PlayerInputComponent->BindAction<FOnAttachParts>("AttachPartsB", IE_Released, this, &ALocalPlayerObject::OnAttachParts, EPartsType::BODY);
	PlayerInputComponent->BindAction<FOnAttachParts>("AttachPartsG", IE_Released, this, &ALocalPlayerObject::OnAttachParts, EPartsType::GLOVE);
	PlayerInputComponent->BindAction<FOnAttachParts>("AttachPartsL", IE_Released, this, &ALocalPlayerObject::OnAttachParts, EPartsType::LEG);
	PlayerInputComponent->BindAction<FOnAttachParts>("AttachPartsHair", IE_Released, this, &ALocalPlayerObject::OnAttachParts, EPartsType::HAIR);
	PlayerInputComponent->BindAction<FOnAttachParts>("AttachPartsFace", IE_Released, this, &ALocalPlayerObject::OnAttachParts, EPartsType::FACE);

	//key
	PlayerInputComponent->BindAction<FOnAttack1>("Attack1", IE_Released, this, &ALocalPlayerObject::OnAttack1, 1);
	PlayerInputComponent->BindAction<FOnAttack1>("Attack2", IE_Released, this, &ALocalPlayerObject::OnAttack1, 2);
	PlayerInputComponent->BindAction<FOnAttack1>("Attack3", IE_Released, this, &ALocalPlayerObject::OnAttack1, 3);

	//Movement
	PlayerInputComponent->BindAction("MoveForward", IE_Pressed, this, &ALocalPlayerObject::OnMoveForward);
	PlayerInputComponent->BindAction("MoveBackward", IE_Pressed, this, &ALocalPlayerObject::OnMoveBackward);
	PlayerInputComponent->BindAction("MoveLeft", IE_Pressed, this, &ALocalPlayerObject::OnMoveLeft);
	PlayerInputComponent->BindAction("MoveRight", IE_Pressed, this, &ALocalPlayerObject::OnMoveRight);
	PlayerInputComponent->BindAction("MoveStop", IE_Released, this, &ALocalPlayerObject::OnMoveStop);

	PlayerInputComponent->BindAxis("MoveRotate", this, &ALocalPlayerObject::AddControllerYawInput);
	PlayerInputComponent->BindAxis("Turn", this, &ALocalPlayerObject::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ALocalPlayerObject::AddControllerPitchInput);
}

void ALocalPlayerObject::OnAttachParts(EPartsType Type)
{
	if (PartsMgr)
	{
		PartsMgr->IsEquip(Type) ? PartsMgr->Detach(Type) : PartsMgr->Attach(Type);
	}

	GetActorRotation();
}

void ALocalPlayerObject::OnAttack1(int32 slot)
{
	if (SkillMgr)
	{
		SkillMgr->UseSKill(slot);
		UpperFsm->ChangeState<FStateAttack>();
	}

	//UpperFsm->ChangeState<FStateAttack>();
	//Animation->ChangeUpperState(ECharacterStateUpperBase::Attack, 1);
	/*
	UAnimInstance* ani = GetMesh()->GetAnimInstance();
	auto newmontage = ani->PlaySlotAnimationAsDynamicMontage(AttackMontage, TEXT("UpperBody"), 0.1f, 0.1f, 1.0f, 30.0f);
	float len = ani->Montage_Play(newmontage);
	SetAniTimer(AttackMontage->GetUniqueID(), len);

	FOnMontageEnded EndDelegate;
	EndDelegate.BindUObject(this, &AMyCharacter::OnAttackEnd);
	ani->Montage_SetEndDelegate(EndDelegate);*/


}

void ALocalPlayerObject::OnMoveStop()
{
	LowwerFsm->ChangeState<FStateIdle>();
}

void ALocalPlayerObject::OnMoveForward()
{
	LowwerFsm->ChangeState<FStateForwardWalk>();
}

void ALocalPlayerObject::OnMoveBackward()
{
	LowwerFsm->ChangeState<FStateBackwardWalk>();
}

void ALocalPlayerObject::OnMoveLeft()
{
	MovementForce = -0.5f; //Movement 구현으로 추후 대체되야함

	LowwerFsm->ChangeState<FStateSideWalk>();
}

void ALocalPlayerObject::OnMoveRight()
{
	MovementForce = 0.5f; //Movement 구현으로 추후 대체되야함

	LowwerFsm->ChangeState<FStateSideWalk>();
}

void ALocalPlayerObject::OnMoveRotate(float Value)
{
	FVector dir = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(dir, Value);
}