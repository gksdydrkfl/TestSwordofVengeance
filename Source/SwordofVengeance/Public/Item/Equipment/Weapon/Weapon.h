// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS()
class SWORDOFVENGEANCE_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:

	AWeapon();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Animation Layer", meta = (AllowPrivateAccess = true))
	TSubclassOf<UAnimInstance> NonCombatAnimClassLayers;

	UPROPERTY(EditDefaultsOnly, Category = "Animation Layer", meta = (AllowPrivateAccess = true))
	TSubclassOf<UAnimInstance> CombatAnimClassLayers;

public:

	FORCEINLINE TSubclassOf<UAnimInstance> GetNonCombatAnimClassLayers() { return NonCombatAnimClassLayers; }
	FORCEINLINE TSubclassOf<UAnimInstance> GetCombatAnimClassLayers() { return CombatAnimClassLayers; }

};
