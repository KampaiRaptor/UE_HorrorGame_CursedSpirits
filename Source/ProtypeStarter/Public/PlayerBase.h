// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DamageInterface.h"
#include "GameFramework/Character.h"
#include "PlayerBase.generated.h"

class UArrowComponent;
class UPointLightComponent;

UCLASS()
class PROTYPESTARTER_API APlayerBase : public ACharacter, public IDamageInterface
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
	
	FTimerHandle AttackTimerHandle;

	UFUNCTION(Category="Stats")
	void AutoHeal();

	UFUNCTION(Category="Attacks")
	void DecreaseLightRadius();
	
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Attacks")
	TObjectPtr<UPointLightComponent> PointLight;

	UFUNCTION(BlueprintCallable, Category = "Attacks")
	void AddLightRadius(float Intensity);

	UFUNCTION(BlueprintPure, Category = "Stats")
	TArray<float> GetStats();

	void DI_SpiritKilled_Implementation() override;
	void DI_DrainHealth_Implementation() override;

	UFUNCTION(BlueprintImplementableEvent, Category="attacks")
	void Death();
	
protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
