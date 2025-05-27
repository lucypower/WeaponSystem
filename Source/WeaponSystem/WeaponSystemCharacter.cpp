// Copyright Epic Games, Inc. All Rights Reserved.

#include "WeaponSystemCharacter.h"
#include "WeaponSystemProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Blueprint/UserWidget.h"
#include "Engine/LocalPlayer.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// AWeaponSystemCharacter

AWeaponSystemCharacter::AWeaponSystemCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));

	StatComponent = CreateDefaultSubobject<UStatComponent>(TEXT("StatComponent"));
}

void AWeaponSystemCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponSystemCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AWeaponSystemCharacter::Move);

		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AWeaponSystemCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AWeaponSystemCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LineTrace();
}

void AWeaponSystemCharacter::LineTrace()
{
	FVector StartPos = FirstPersonCameraComponent->GetComponentLocation();
	FVector ForwardVec = FirstPersonCameraComponent->GetForwardVector();
	FVector EndPos = StartPos + (ForwardVec * WeaponPickupRange);

	FHitResult OutHit;
	TArray<TEnumAsByte<EObjectTypeQuery>> TraceObjectTypes;
	TraceObjectTypes.Add(UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldDynamic));

	TArray<AActor*> IgnoreList;
	IgnoreList.Add(GetOwner());

	bool Result = UKismetSystemLibrary::LineTraceSingleForObjects(GetWorld(), StartPos, EndPos, TraceObjectTypes, false,
		IgnoreList, EDrawDebugTrace::ForOneFrame, OUT OutHit, true);
	
	
	if (Result && !WeaponPickupUI->IsVisible())
	{
		WeaponPickupUI->AddToViewport();
		
		FString f = FString(OutHit.GetActor()->GetName());
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, f);
	}
	else
	{
		if (WeaponPickupUI->IsVisible())
		{
			WeaponPickupUI->RemoveFromParent();
		}
	}
}

void AWeaponSystemCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AWeaponSystemCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
