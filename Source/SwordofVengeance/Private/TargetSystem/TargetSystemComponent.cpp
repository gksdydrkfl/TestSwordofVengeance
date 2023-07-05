#include "TargetSystem/TargetSystemComponent.h"
#include "SwordofVengeance/DebugMacro.h"
#include "EngineUtils.h"
#include "TargetSystem/TargetSystemInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Character/Slay.h"
#include "Item/Equipment/Weapon/Weapon.h"
#include "Components/WidgetComponent.h"

UTargetSystemComponent::UTargetSystemComponent() :
	bRockOn(false),
	OwnerActor(nullptr),
	NearTarget(nullptr),
	TargetableActors(APawn::StaticClass())

{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UTargetSystemComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerActor = GetOwner();

	if (OwnerActor)
	{
		AController* Controller = Cast<APawn>(OwnerActor)->GetController();
		if (Controller)
		{
			OwnerController = Cast<APlayerController>(Controller);
		}
	}

	TargetLockOff();
}


// Called every frame
void UTargetSystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bRockOn == false)
	{
		return;
	}

	UpdateControllerRotation();
}

bool UTargetSystemComponent::TargetLockOn()
{
	NearTarget = nullptr;

	TArray<AActor*> Actors;

	Actors = GetAllActors();

	if (Actors.Num() <= 0)
	{
		return false;
	}

	TArray<AActor*> HitActors;

	for (AActor* Actor : Actors)
	{
		bool bHitTarget = LineTraceForTarget(HitActors, Actor);

		if (bHitTarget)
		{
			HitActors.Add(Actor);
		}
	}

	NearTarget = FindNearTarget(HitActors);

	if (NearTarget == nullptr)
	{
		return false;
	}

	SetControllerRotation(true);

	bRockOn = true;

	if (LockedOnWidgetClass)
	{
		LockOnWidgetComponent = NewObject<UWidgetComponent>(NearTarget, MakeUniqueObjectName(NearTarget, UWidgetComponent::StaticClass(), FName("TargetLockOn")));
		if (LockOnWidgetComponent)
		{
			UMeshComponent* MeshComponent = NearTarget->FindComponentByClass<UMeshComponent>();
			if (MeshComponent)
			{
				LockOnWidgetComponent->SetWidgetClass(LockedOnWidgetClass);
				LockOnWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
				LockOnWidgetComponent->SetupAttachment(MeshComponent, FName("spine_02"));
				LockOnWidgetComponent->SetDrawSize(FVector2D(32.f, 32.f));
				LockOnWidgetComponent->RegisterComponent();
			}

		}
	}


	return true;
}

void UTargetSystemComponent::TargetLockOff()
{
	bRockOn = false;

	SetControllerRotation(false);

	NearTarget = nullptr;

	DestroyWidgetComponent();
}

void UTargetSystemComponent::UpdateControllerRotation()
{
	if (OwnerController == nullptr)
	{
		return;
	}
	if (OwnerActor == nullptr)
	{
		return;
	}
	if (NearTarget == nullptr)
	{
		return;
	}

	FVector End = NearTarget->GetActorLocation();
	FVector Start = OwnerActor->GetActorLocation();
	FVector Direction = (End - Start).GetSafeNormal();
	FRotator OwnerRotation = FRotationMatrix::MakeFromX(Direction).Rotator();

	const float Distance = (NearTarget->GetActorLocation() - OwnerActor->GetActorLocation()).Size();
	if (Distance > TargetMaxDistance)
	{
		TargetLockOff();

		//AHero* Hero = Cast<AHero>(OwnerActor);

		//if (Hero)
		//{
		//	TSubclassOf<UAnimInstance> NonCombatAnimClassLayers = Hero->GetCurrentWeapon()->GetNonCombatAnimClassLayers();
		//	if (NonCombatAnimClassLayers)
		//	{
		//		Hero->SetLinkAnimClassLayers(NonCombatAnimClassLayers);
		//	}
		//}

		return;
	}
	const float PitchValue = (Distance * PitchDistanceCoefficient + PitchDistanceOffset) * -1.f;
	const float PitchOffset = FMath::Clamp(PitchValue, PitchMin, PitchMax);

	OwnerRotation.Pitch = PitchOffset;

	FRotator CurrnetRotation = OwnerController->GetControlRotation();

	const FRotator NewRotation = FMath::RInterpTo(CurrnetRotation, OwnerRotation, GetWorld()->GetDeltaSeconds(), 10.f);

	OwnerController->SetControlRotation(NewRotation);
}

bool UTargetSystemComponent::GetRockOn() const
{
	return bRockOn;
}

float UTargetSystemComponent::GetDistanceForTarget(AActor* TargetActor) const
{
	const FVector TargetVector = TargetActor->GetActorLocation();
	const FVector OwnerVector = OwnerActor->GetActorLocation();

	return (TargetVector - OwnerVector).Size();
}

TArray<AActor*> UTargetSystemComponent::GetAllActors()
{
	TArray<AActor*> Actors;

	for (TActorIterator<AActor> Enemy(GetWorld(), TargetableActors); Enemy; ++Enemy)
	{
		AActor* Actor = *Enemy;

		if (Actor->GetClass()->ImplementsInterface(UTargetSystemInterface::StaticClass()))
		{

			ITargetSystemInterface* Inteface = Cast<ITargetSystemInterface>(Actor);
			if (Inteface->IsTargetable())
			{
				Actors.Add(Actor);
			}
		}
	}

	return Actors;
}

bool UTargetSystemComponent::LineTraceForTarget(TArray<AActor*>& HitActors, const AActor* Actor)
{
	FHitResult HitResult;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(OwnerActor);

	const FVector Start = OwnerActor->GetActorLocation();

	const FVector End = Actor->GetActorLocation();

	GetWorld()->LineTraceSingleByChannel(
		HitResult,
		Start,
		End,
		ECollisionChannel::ECC_Pawn,
		Params);

	AActor* HitActor = HitResult.GetActor();

	if (HitActor == Actor)
	{
		return true;
	}

	return false;
}

AActor* UTargetSystemComponent::FindNearTarget(const TArray<AActor*> HitActors)
{
	float ClosestDistance = TargetMaxDistance;

	AActor* ReturnActor = nullptr;

	for (AActor* Actor : HitActors)
	{
		float Distance = GetDistanceForTarget(Actor);

		UE_LOG(LogTemp, Warning, TEXT("%s : %f"), *Actor->GetName(), Distance);

		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ReturnActor = Actor;
		}
	}

	return ReturnActor;
}

void UTargetSystemComponent::SetControllerRotation(bool bValue)
{
	if (OwnerActor == nullptr)
	{
		return;
	}

	if (OwnerController == nullptr)
	{
		return;
	}

	APawn* OwnerPawn = Cast<APawn>(OwnerActor);

	if (OwnerPawn == nullptr)
	{
		return;
	}

	OwnerController->SetIgnoreLookInput(bValue);

	OwnerPawn->bUseControllerRotationYaw = bValue;

	//UCharacterMovementComponent* CharacterMovementComponent = OwnerPawn->FindComponentByClass<UCharacterMovementComponent>();
	//if (CharacterMovementComponent)
	//{
	//	CharacterMovementComponent->bOrientRotationToMovement = !bValue;
	//}
}

void UTargetSystemComponent::DestroyWidgetComponent()
{
	if (LockOnWidgetComponent)
	{
		LockOnWidgetComponent->DestroyComponent();
	}
}
