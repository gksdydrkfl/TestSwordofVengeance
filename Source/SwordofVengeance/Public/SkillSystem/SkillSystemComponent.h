// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Skill/Skill.h"
#include "SkillSystemComponent.generated.h"

class USkill;
class ASlay;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SWORDOFVENGEANCE_API USkillSystemComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USkillSystemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;



private:

	UPROPERTY(VisibleAnywhere)
	TMap<ESkillType, USkill*> Skills;

	UPROPERTY(VisibleAnywhere)
	USkill* NewSkill;
public:

	FORCEINLINE TMap<ESkillType, USkill*> GetSkills() const { return Skills; }

	void Init(ASlay* Slay);

	void StartSkill(const ESkillType& SkillType);

	USkill* GetSkill(const ESkillType& SkillType);

};
