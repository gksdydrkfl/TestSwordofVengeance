// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TargetSystemComponent.generated.h"

class UWidgetComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class SWORDOFVENGEANCE_API UTargetSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UTargetSystemComponent();

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	bool bRockOn;

	AActor* OwnerActor;
	UPROPERTY(VisibleAnywhere)
		AActor* NearTarget;

	TSubclassOf<AActor> TargetableActors;

	APlayerController* OwnerController;

	const float PitchDistanceCoefficient = -0.2f;

	const float PitchDistanceOffset = 60.f;

	const float PitchMin = -45.f;

	const float PitchMax = -15.f;

	const float TargetMaxDistance = 1500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (AllowPrivateAccess = true))
	TSubclassOf<UUserWidget> LockedOnWidgetClass;

	UWidgetComponent* LockOnWidgetComponent;
public:

	bool GetRockOn() const;

	float GetDistanceForTarget(AActor* TargetActor) const;

	TArray<AActor*> GetAllActors();

	bool LineTraceForTarget(TArray<AActor*>& HitActors, const AActor* Actor);

	AActor* FindNearTarget(const TArray<AActor*> HitActors);

	bool TargetLockOn();

	void TargetLockOff();

	void UpdateControllerRotation();

	void SetControllerRotation(bool bValue);

	void DestroyWidgetComponent();

};
