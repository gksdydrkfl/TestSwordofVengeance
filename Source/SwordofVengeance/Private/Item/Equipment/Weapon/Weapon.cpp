// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/Equipment/Weapon/Weapon.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Character/Slay.h"
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
	}
}

void AWeapon::OnBoxCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const FVector Start = BoxCollisionStart->GetComponentLocation();
	const FVector End = BoxCollisionEnd->GetComponentLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

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
		EDrawDebugTrace::ForDuration,
		HitResult,
		true,
		FColor::Red,
		FColor::Green,
		5.f);

	if (OtherActor == nullptr)
	{
		return;
	}
	const FVector DotVector1(OtherActor->GetActorForwardVector());
	const FVector ImpactLocation(HitResult.ImpactPoint.X, HitResult.ImpactPoint.Y, OtherActor->GetActorLocation().Z);
	const FVector DotVector2 = (ImpactLocation - OtherActor->GetActorLocation()).GetSafeNormal();

	const double DotVector = FVector::DotProduct(DotVector1, DotVector2);
	double Angle = FMath::Acos(DotVector);
	Angle = FMath::RadiansToDegrees(Angle);

	UKismetSystemLibrary::DrawDebugArrow(this, OtherActor->GetActorLocation(), OtherActor->GetActorLocation() + DotVector1 * 60.f, 5.f, FColor::Red, 5.f);
	UKismetSystemLibrary::DrawDebugArrow(this, OtherActor->GetActorLocation(), OtherActor->GetActorLocation() + DotVector2 * 60.f, 5.f, FColor::Green, 5.f);

	const FVector CrossVector = FVector::CrossProduct(DotVector1, DotVector2);
	Debug::Log(CrossVector);
	if (CrossVector.Z < 0)
	{
		Angle *= -1.f;
	}
	Debug::Log(Angle);

}

void AWeapon::EndBoxCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Debug::Log("OffBoxCollision");

}
