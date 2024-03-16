// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerBase.h"
#include "Components/ArrowComponent.h"
#include "Components/PointLightComponent.h"
#include "Engine/DamageEvents.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
APlayerBase::APlayerBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PointLight=CreateDefaultSubobject<UPointLightComponent>(TEXT("PointLight"));
	PointLight->SetupAttachment(RootComponent);
	SetActorTickInterval(0.05f);
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
	AutoHeal();
	DecreaseLightRadius();
}

void APlayerBase::Attack()
{

	FHitResult Hit;
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	const FVector Start = TraceArrowLocation->GetComponentLocation();
	const FVector End = TraceArrowLocation->GetForwardVector() * 200 + Start;

	GetWorld()->SweepSingleByChannel(Hit, Start, End, FQuat::Identity, ECollisionChannel::ECC_Visibility, FCollisionShape::MakeSphere(20.f), CollisionParams);

	if (Hit.bBlockingHit)
	{
		Hit.GetActor()->TakeDamage(10.0f, FDamageEvent(), GetController(), this);
	}
	//DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f);
}

void APlayerBase::AutoHeal()
{
	if (GetCharacterMovement()->Velocity.Length() <= 1.0f && bCanAttack == true)
	{
		if (Health < 100)
		{
			Health += 0.2f;
		}
	}
}

void APlayerBase::DecreaseLightRadius()
{
	if (PointLight->AttenuationRadius <= 250.0f)
	{
		return;
	}
	const float Radius = PointLight->AttenuationRadius;
	PointLight->SetAttenuationRadius(Radius -10.0f * (Radius*0.0005f));
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
		Death();
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

void APlayerBase::AddLightRadius(float Intensity)
{
	PointLight->SetAttenuationRadius(PointLight->AttenuationRadius + Intensity);
}

TArray<float> APlayerBase::GetStats()
{
	TArray<float> Stats;
	Stats.Add(Health);
	Stats.Add(PointLight->AttenuationRadius);
	return Stats;
}

void APlayerBase::DI_SpiritKilled_Implementation()
{
	IDamageInterface::DI_SpiritKilled_Implementation();
}

void APlayerBase::DI_DrainHealth_Implementation()
{
	DealDamage(0.1f);
	return IDamageInterface::DI_DrainHealth_Implementation();
}

// Called to bind functionality to input
void APlayerBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

