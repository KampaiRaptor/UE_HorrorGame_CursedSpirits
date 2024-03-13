// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBase.h"
#include "Components/ArrowComponent.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APlayerBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerBase::Attack()
{

	FHitResult Hit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	const FVector Start = TraceArrowLocation->GetComponentLocation();
	const FVector End = TraceArrowLocation->GetForwardVector() * 200 + Start;

	GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(20.f), CollisionParams);
	
	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f);
}

bool APlayerBase::CanAttack()
{
	return bCanAttack;
}

void APlayerBase::DealDamage(float Damage)
{
	Health -= Damage;
	if (Health <= 0)
	{
		//Death
	}
}

void APlayerBase::StartAttack(UArrowComponent* TraceLocation)
{
	TraceArrowLocation = TraceLocation;
	bCanAttack = false;
	GetWorldTimerManager().SetTimer(AttackTimerHandle, this, &APlayerBase::Attack, 0.01f, true);
}

void APlayerBase::StopAttack()
{
	bCanAttack = true;
	GetWorldTimerManager().ClearTimer(AttackTimerHandle);
}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

