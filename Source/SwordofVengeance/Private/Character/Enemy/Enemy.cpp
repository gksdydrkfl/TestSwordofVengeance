// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/Enemy/Enemy.h"
#include "Components/CapsuleComponent.h"
#include "SwordofVengeance/DebugMacro.h"
#include "Kismet/GameplayStatics.h"


AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetMesh()->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);
	GetMesh()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_Camera, ECollisionResponse::ECR_Ignore);
}

void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AEnemy::IsTargetable()
{
	return true;
}

void AEnemy::GetHit(const FVector& HitImpact)
{
	const FVector DotVector1(GetActorForwardVector());
	const FVector ImpactLocation(HitImpact.X, HitImpact.Y, GetActorLocation().Z);
	const FVector DotVector2 = (ImpactLocation - GetActorLocation()).GetSafeNormal();

	const double DotVector = FVector::DotProduct(DotVector1, DotVector2);
	double Angle = FMath::Acos(DotVector);
	Angle = FMath::RadiansToDegrees(Angle);

	const FVector CrossVector = FVector::CrossProduct(DotVector1, DotVector2);

	if (CrossVector.Z < 0)
	{
		Angle *= -1.f;
	}
	
	FName SectionName;

	if (Angle < 45.f && Angle >= -45.f)
	{
		SectionName = FName("Forward");
	}
	else if (Angle > 45.f && Angle <= 135.f)
	{
		SectionName = FName("Right");
	}
	else if (Angle < -45.f && Angle >= -135.f)
	{
		SectionName = FName("Left");
	}
	else
	{
		SectionName = FName("Backward");
	}

	GetMesh()->GetAnimInstance()->Montage_Play(ReactMontage);

	GetMesh()->GetAnimInstance()->Montage_JumpToSection(SectionName, ReactMontage);

	if (HitParticles)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticles, HitImpact);
	}
}

