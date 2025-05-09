#pragma once

#include "CoreMinimal.h"
#include "WeaponData.generated.h"

USTRUCT(BlueprintType)
struct WEAPONSYSTEM_API FWeaponData : public FTableRowBase
{
	GENERATED_BODY();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<USkeletalMesh> Mesh;
};
