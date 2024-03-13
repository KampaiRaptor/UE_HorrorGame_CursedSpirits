// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"

class UArrowComponent;

UCLASS()
class PROTYPESTARTER_API APlayerBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleDefaultsOnly, Category="Stats")
	float Health = 100.0f;

	UPROPERTY(VisibleDefaultsOnly, Category="Stats")
	bool bCanAttack = true;

	UFUNCTION(Category="Attacks")
	void Attack();

	UPROPERTY(VisibleDefaultsOnly, Category="Attacks")
	float AttackProgress = 0.0f;
	
	FTimerHandle AttackTimerHandle;

public:
	UFUNCTION(BlueprintPure, Category = "Stats")
	bool CanAttack();

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void DealDamage(float Damage);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void StartAttack(UArrowComponent* TraceLocation);

	UFUNCTION(BlueprintCallable, Category = "Stats")
	void StopAttack();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Stats")
	TObjectPtr<UArrowComponent> TraceArrowLocation;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
