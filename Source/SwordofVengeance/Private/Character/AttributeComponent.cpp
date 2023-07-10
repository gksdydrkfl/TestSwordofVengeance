// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetHealth(Health - DeltaTime);
}

void UAttributeComponent::SetHealth(float NewHealth)
{
	Health = NewHealth;;

	FMath::Clamp(Health, 0, HealthMax);

	HealthDelegate.Broadcast(Health);
}

void UAttributeComponent::Init()
{
	HealthMax = 100.f;

	Health = HealthMax;

}

