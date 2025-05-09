#include "TargetDummy.h"

ATargetDummy::ATargetDummy()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATargetDummy::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATargetDummy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health <= 0)
	{
		Destroy();
	}
}

float ATargetDummy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, FString::SanitizeFloat(DamageAmount));

	Health -= DamageAmount;

	return Health;
}
