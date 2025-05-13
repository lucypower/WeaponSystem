#include "StatComponent.h"

UStatComponent::UStatComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UStatComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

void UStatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UStatComponent::ChangeWeaponStats(float Damage, float AmmoCount, float MaxAmmoCount)
{
	WeaponDamage = Damage;
	Ammo = AmmoCount;
	MaxAmmo = MaxAmmoCount;
}

void UStatComponent::UpdateAmmoCount(float AmmoCount)
{
	Ammo = AmmoCount;
}

