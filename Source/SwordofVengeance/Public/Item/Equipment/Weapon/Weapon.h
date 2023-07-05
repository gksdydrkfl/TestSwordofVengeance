// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item/Item.h"
#include "Weapon.generated.h"




class UBoxComponent;
class ASlay;
class UKatanaSoundAsset;

UCLASS()
class SWORDOFVENGEANCE_API AWeapon : public AItem
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

	ASlay* Slay;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> IgnoreActors;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = true))
	UBoxComponent* BoxCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	USceneComponent* BoxCollisionStart;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	USceneComponent* BoxCollisionEnd;


public:

	FORCEINLINE TSubclassOf<UAnimInstance> GetNonCombatAnimClassLayers() { return NonCombatAnimClassLayers; }
	FORCEINLINE TSubclassOf<UAnimInstance> GetCombatAnimClassLayers() { return CombatAnimClassLayers; }

	void EnabledBoxCollision(ECollisionEnabled::Type NewType);
	void DisabledBoxCollision(ECollisionEnabled::Type NewType);

	FORCEINLINE void SetCharacter(ASlay* NewSlay) { Slay = NewSlay; }

public:

	UFUNCTION()
	void OnBoxCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndBoxCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	//void PlaySound(const EWeaponSound& Sound);
};
