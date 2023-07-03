// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Equipment/Weapon/Katana.h"
#include "Components/BoxComponent.h"

AKatana::AKatana()
{

}

void AKatana::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnBoxCollision);
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &AWeapon::EndBoxCollision);
}

