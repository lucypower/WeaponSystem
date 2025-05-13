#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class WEAPONSYSTEM_API UStatComponent : public UActorComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Weapon, meta=(AllowPrivateAccess=true))
	int Ammo;

	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Weapon, meta=(AllowPrivateAccess=true))
	int MaxAmmo;

	
protected:
	virtual void BeginPlay() override;

public:

	UStatComponent();
	
	UPROPERTY(VisibleAnywhere, BluePrintReadOnly, Category = Weapon, meta=(AllowPrivateAccess=true))
	int WeaponDamage;
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void ChangeWeaponStats(float Damage, float AmmoCount, float MaxAmmoCount);

	void UpdateAmmoCount(float AmmoCount);
};
