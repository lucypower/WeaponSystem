// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "StatComponent.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Kismet/KismetSystemLibrary.h"
#include "WeaponSystemCharacter.generated.h"


class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UUserWidget;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AWeaponSystemCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = StatComp, meta = (AllowPrivateAccess = "true"))
	UStatComponent* StatComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"))
	int WeaponPickupRange;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=UI, meta=(AllowPrivateAccess = "true"))
	UUserWidget* WeaponPickupUI;

	UFUNCTION()
	void LineTrace();
	
public:
	AWeaponSystemCharacter();

protected:
	virtual void BeginPlay();

public:
		
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

protected:
	void Move(const FInputActionValue& Value);

	void Look(const FInputActionValue& Value);

	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

public:
	virtual void Tick(float DeltaTime) override;
	
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
};

