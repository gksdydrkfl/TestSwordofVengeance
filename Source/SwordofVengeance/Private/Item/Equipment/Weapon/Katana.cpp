// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Equipment/Weapon/Katana.h"
#include "Components/BoxComponent.h"
#include "DataAsset/KatanaSoundAsset.h"
#include "Kismet/GameplayStatics.h"

AKatana::AKatana()
{
	ItemName = FName("Katana");
}

void AKatana::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxCollision);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AWeapon::EndBoxCollision);
}

void AKatana::PlaySound()
{
	if (KatanaSoundAsset == nullptr)
	{
		return;
	}

	USoundBase* SoundBase = nullptr;

	switch (WeaponSound)
	{
	case EWeaponSound::EWS_DrawSword:
		SoundBase = KatanaSoundAsset->DrawSwordSound;
		break;
	case EWeaponSound::EWS_SwordSwing1:
		SoundBase = KatanaSoundAsset->SwordSwingSound[0];
		break;
	case EWeaponSound::EWS_SwordSwing2:
		SoundBase = KatanaSoundAsset->SwordSwingSound[1];
		break;
	case EWeaponSound::EWS_Battojutsu:
		SoundBase = KatanaSoundAsset->BattojutsuSound;
		break;
	default:
		break;
	}

	if (SoundBase)
	{
		UGameplayStatics::PlaySoundAtLocation(this, SoundBase, GetActorLocation());
	}

}