// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Equipment/Weapon/Weapon.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/Slay.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Interface/HitInterface.h"
#include "Kismet/GameplayStatics.h"
#include "DataAsset/KatanaSoundAsset.h"
#include "Camera/CameraShake.h"
#include "SwordofVengeance/DebugMacro.h"

// Sets default values
AWeapon::AWeapon() 
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(GetItemMesh());
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);

	BoxCollisionStart = CreateDefaultSubobject<USceneComponent>(TEXT("BoxCollisionStart"));
	BoxCollisionStart->SetupAttachment(GetItemMesh());
	BoxCollisionEnd = CreateDefaultSubobject<USceneComponent>(TEXT("BoxCollisionEnd"));
	BoxCollisionEnd->SetupAttachment(GetItemMesh());
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::EnabledBoxCollision(ECollisionEnabled::Type NewType)
{
	if (BoxCollision)
	{
		BoxCollision->SetCollisionEnabled(NewType);
	}
	//BoxCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	//BoxCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Ignore);
}

void AWeapon::DisabledBoxCollision(ECollisionEnabled::Type NewType)
{
	if (BoxCollision)
	{
		BoxCollision->SetCollisionEnabled(NewType);

		IgnoreActors.Empty();
	}
}

void AWeapon::GlobalTimerFuncion()
{
	Debug::Log("GlobalTimer");

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}

void AWeapon::OnBoxCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = BoxCollisionStart->GetComponentLocation();
	const FVector End = BoxCollisionEnd->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	for (AActor* Actor : IgnoreActors)
	{
		IgnoreActors.AddUnique(Actor);
	}

	FHitResult HitResult;

	UKismetSystemLibrary::BoxTraceSingle(
		this,
		Start,
		End,
		FVector(2.5f, 2.5f, 2.5f),
		BoxCollision->GetComponentRotation(),
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		HitResult,
		true,
		FColor::Red,
		FColor::Green,
		5.f);

	if (HitResult.GetActor())
	{
		if (HitResult.GetActor()->GetClass()->ImplementsInterface(UHitInterface::StaticClass()))
		{
			IHitInterface* Inteface = Cast<IHitInterface>(HitResult.GetActor());
			if (Inteface)
			{
				Inteface->GetHit(HitResult.ImpactPoint);

				IgnoreActors.AddUnique(HitResult.GetActor());
			}
		}
		UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.05f);

		GetWorld()->GetTimerManager().SetTimer(GlobalTimer, FTimerDelegate::CreateLambda([&]()
			{

				Debug::Log("GlobalTimer");

				UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

			}), 0.005f, false);
	}
}

void AWeapon::EndBoxCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

//void AWeapon::PlaySound(const EWeaponSound& Sound)
//{
//	if (KatanaSoundAsset == nullptr)
//	{
//		return;
//	}
//
//	USoundBase* SoundBase = nullptr;
//
//	switch (Sound)
//	{
//	case EWeaponSound::EWS_DrawSword:
//		SoundBase = KatanaSoundAsset->DrawSwordSound;
//		break;
//	default:
//		break;
//	}
//
//	if (SoundBase)
//	{
//		UGameplayStatics::PlaySoundAtLocation(this, KatanaSoundAsset->DrawSwordSound, GetActorLocation());
//	}
//
//}
