// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item/Equipment/Weapon/Weapon.h"
#include "Katana.generated.h"

UENUM(BlueprintType)
enum class EWeaponSound : uint8
{
	EWS_DrawSword		UMETA(DisplayName = "DrawSword"),
	EWS_SwordSwing1		UMETA(DisplayName = "SwordSwing1"),
	EWS_SwordSwing2		UMETA(DisplayName = "SwordSwing2"),
	EWS_Battojutsu		UMETA(DisplayName = "Battojutsu")
};

UCLASS()
class SWORDOFVENGEANCE_API AKatana : public AWeapon
{
	GENERATED_BODY()
	
public:

	AKatana();
	
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	UKatanaSoundAsset* KatanaSoundAsset;

	EWeaponSound WeaponSound;

public:

	FORCEINLINE void SetWeaponSound(EWeaponSound Sound) { WeaponSound = Sound; };

public:
	void PlaySound();
};
