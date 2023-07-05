#include "Character/Slay.h"
#include "DrawDebugHelpers.h"
#include "SwordOfVengeance/DebugMacro.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "DataAsset/InputActions.h"
#include "Item/Equipment/Weapon/Weapon.h"
#include "Character/Animation/SlayAnimInstance.h"
#include "MotionWarpingComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TargetSystem/TargetSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "SkillSystem/SkillSystemComponent.h"
#include "Item/Equipment/Weapon/Katana.h"
#include "SkillSystem/Skill/KatanaBaseAttack.h"

ASlay::ASlay() :
	ActionState(EActionState::EAS_None),
	CharacterState(ECharacterState::ECS_UnEquipped),
	KatanaCombo(0),
	bCanAttack(true),
	CombatStateTime(15.f),
	bBattleMode(false),
	LastInputDirection(FVector::ZeroVector),
	RollingDirection(FVector::ZeroVector),
	bRun(false)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 65.f);

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;
	GetMesh()->SetRelativeLocation(FVector(0.f, 0.f, -89.f));
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 180.f;

	MotionWarpingComp = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarpingComp"));

	TargetSystem = CreateDefaultSubobject<UTargetSystemComponent>(TEXT("TargetSystem"));

	SkillSystem = CreateDefaultSubobject<USkillSystemComponent>(TEXT("SkillSystem"));
}

void ASlay::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	SlayAnimInstance = Cast<USlayAnimInstance>(GetMesh()->GetAnimInstance());

	if (SkillSystem)
	{
		SkillSystem->Init(this);
	}

	//TODO
	//억지로 붙힌느낌 똑같은 내용의 코드를 사용함
	FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

	AWeapon* KatanaSheath = GetWorld()->SpawnActor<AWeapon>(KatanaSheathClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (KatanaSheath)
	{

		KatanaSheath->AttachToComponent(GetMesh(), AttachmentTransformRules, FName("BeltSwordSocket"));
	}

	AWeapon* Katana = GetWorld()->SpawnActor<AWeapon>(KatanaClass, FVector::ZeroVector, FRotator::ZeroRotator);
	if (Katana)
	{

		Katana->AttachToComponent(GetMesh(), AttachmentTransformRules, FName("PutSwordSocket"));

		CurrentWeapon = Katana;

		Katana->SetCharacter(this);
	}

	if (UnarmedAnimLayer && SlayAnimInstance)
	{
		SlayAnimInstance->LinkAnimClassLayers(UnarmedAnimLayer);
	}
}

void ASlay::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASlay::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (InputActions == nullptr) return;

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		/*EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);*/
		EnhancedInputComponent->BindAction(InputActions->MoveAction, ETriggerEvent::Triggered, this, &ASlay::Move);
		EnhancedInputComponent->BindAction(InputActions->LookAction, ETriggerEvent::Triggered, this, &ASlay::Look);
		EnhancedInputComponent->BindAction(InputActions->EquipWeaponAction, ETriggerEvent::Triggered, this, &ASlay::EquipWeapon);
		EnhancedInputComponent->BindAction(InputActions->AttackAction, ETriggerEvent::Triggered, this, &ASlay::Attack);
		EnhancedInputComponent->BindAction(InputActions->TargetLookOnAction, ETriggerEvent::Triggered, this, &ASlay::TargetLookOn);
		EnhancedInputComponent->BindAction(InputActions->RollingAction, ETriggerEvent::Triggered, this, &ASlay::Evasion);
		EnhancedInputComponent->BindAction(InputActions->GuardAction, ETriggerEvent::Triggered, this, &ASlay::Guard);
		EnhancedInputComponent->BindAction(InputActions->RunAction, ETriggerEvent::Triggered, this, &ASlay::Run);
	}
}

void ASlay::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void ASlay::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ASlay::EquippedWeapon()
{
	const FInputActionValue Value;

	EquipWeapon(Value);
}

void ASlay::EquipWeapon(const FInputActionValue& Value)
{
	if (CharacterState == ECharacterState::ECS_Equipped)
	{
		return;
	}

	if (SlayAnimInstance == nullptr)
	{
		return;
	}

	if (CurrentWeapon == nullptr)
	{
		return;
	}

	TSubclassOf<UAnimInstance> NonCombatAnimClassLayers = CurrentWeapon->GetNonCombatAnimClassLayers();
	if (NonCombatAnimClassLayers)
	{
		SlayAnimInstance->LinkAnimClassLayers(NonCombatAnimClassLayers);
	}

	SlayAnimInstance->PlayEquipMontage(EMontageState::EMS_Equip);

	AKatana* Katana = Cast<AKatana>(CurrentWeapon);
	if (Katana)
	{
		Katana->SetWeaponSound(EWeaponSound::EWS_DrawSword);
	}

	CharacterState = ECharacterState::ECS_Equipped;

	ActionState = EActionState::EAS_EquippingWeapon;
}

void ASlay::Attack(const FInputActionValue& Value)
{
	if (SkillSystem)
	{
		SkillSystem->StartSkill(ESkillType::EST_KatanaBaseAttack);

	}
}

void ASlay::TargetLookOn(const FInputActionValue& Value)
{
	if (TargetSystem)
	{
		if (TargetSystem->GetRockOn() == false)
		{
			if (TargetSystem->TargetLockOn() == true)
			{
				TSubclassOf<UAnimInstance> CombatAnimClassLayers = CurrentWeapon->GetCombatAnimClassLayers();

				SetLinkAnimClassLayers(CombatAnimClassLayers);
			}
		}
		else
		{
			TargetSystem->TargetLockOff();

			TSubclassOf<UAnimInstance> NonCombatAnimClassLayers = CurrentWeapon->GetNonCombatAnimClassLayers();

			SetLinkAnimClassLayers(NonCombatAnimClassLayers);
		}

	}
}

void ASlay::Evasion(const FInputActionValue& Value)
{
	if (ActionState == EActionState::EAS_Attacking ||
		ActionState == EActionState::EAS_Evasion)
	{
		return;
	}

	if (SlayAnimInstance && Controller)
	{
		ActionState = EActionState::EAS_Evasion;

		if (TargetSystem)
		{
			bool bRockOn = TargetSystem->GetRockOn();

			if (bRockOn == false)
			{
				//LaunchCharacter(GetActorForwardVector() * 2000.f, false, false);
				//Debug::Log(GetActorForwardVector() * 2000.f);
			}
			SlayAnimInstance->PlayRollingMontage(bRockOn);
		}
	}
}

void ASlay::Guard(const FInputActionValue& Value)
{
	SlayAnimInstance->PlayGuardMontage();
}

void ASlay::Run(const FInputActionValue& Value)
{
	bRun = !bRun;

	bRun ? GetCharacterMovement()->MaxWalkSpeed = 450.f : GetCharacterMovement()->MaxWalkSpeed = 180.f;
}




void ASlay::AttachWeaponToSocket(const FName& SocketName)
{
	if (CurrentWeapon)
	{
		FAttachmentTransformRules AttachmentTransformRules(EAttachmentRule::SnapToTarget, true);

		CurrentWeapon->AttachToComponent(GetMesh(), AttachmentTransformRules, SocketName);
	}
}



void ASlay::UpdateMotionWarping()
{

	if (TargetSystem == nullptr)
	{
		return;
	}

	if (MotionWarpingComp == nullptr)
	{
		return;
	}

	FVector LastLocation = GetLastMovementInputVector();

	if (LastLocation.IsZero() || TargetSystem->GetRockOn())
	{
		MotionWarpingComp->RemoveWarpTarget(FName("TargetWarp"));

		LastLocation = GetActorForwardVector();
	}

	//FHitResult HitResult;
	//const FVector Start = GetActorLocation() + (LastLocation * 34.f);
	//const FVector End = Start + (LastLocation * 100.f);

	//TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	//TEnumAsByte<EObjectTypeQuery> ColiisionWorldStatic = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_WorldStatic);
	//TEnumAsByte<EObjectTypeQuery> CollisionPawn = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_Pawn);

	//ObjectTypes.Add(ColiisionWorldStatic);
	//ObjectTypes.Add(CollisionPawn);

	//TArray<AActor*> IgnoreActor;


	//IgnoreActor.Add(this);

	//UKismetSystemLibrary::SphereTraceSingleForObjects(
	//	GetWorld(),
	//	Start,
	//	End,
	//	34.f,
	//	ObjectTypes,
	//	false,
	//	IgnoreActor,
	//	EDrawDebugTrace::Type::ForDuration,
	//	HitResult,
	//	true
	//);

	//if (HitResult.bBlockingHit)
	//{
	//	MotionWarpingTargectDistance = HitResult.Distance;
	//}
	//else
	//{
	//	MotionWarpingTargectDistance = 100.f;
	//}

	const FVector Location = GetActorLocation();
	const FVector TargetLocation = (LastLocation.GetSafeNormal() * MotionWarpingTargectDistance) + Location;
	const FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX(LastLocation.GetSafeNormal());

	MotionWarpingComp->AddOrUpdateWarpTargetFromLocationAndRotation(
		FName("TargetWarp"),
		TargetLocation,
		TargetRotation);
}

void ASlay::SetCombatMode()
{
	bBattleMode = true;

	GetWorldTimerManager().SetTimer(
		CombatTimerHandle,
		this,
		&ASlay::SetNonCombatMode,
		CombatStateTime,
		false);
}

void ASlay::SetNonCombatMode()
{
	CharacterState = ECharacterState::ECS_UnEquipped;

	bBattleMode = false;

	if (SlayAnimInstance == nullptr)
	{
		return;
	}

	SlayAnimInstance->PlayEquipMontage(EMontageState::EMS_UnEquip);

	if (UnarmedAnimLayer)
	{
		SlayAnimInstance->LinkAnimClassLayers(UnarmedAnimLayer);
	}
}

bool ASlay::CanAttackingState(const FInputActionValue& Value)
{
	if (ActionState == EActionState::EAS_Evasion)
	{
		return false;
	}

	if (CharacterState == ECharacterState::ECS_UnEquipped)
	{
		const FInputActionValue& FInputActionValue(Value);

		EquipWeapon(Value);

		return false;
	}

	if (bCanAttack == false)
	{
		return false;
	}

	if (MotionWarpingComp == nullptr)
	{
		return false;
	}

	if (ActionState == EActionState::EAS_EquippingWeapon)
	{
		return false;
	}

	return true;
}

void ASlay::SetLinkAnimClassLayers(const TSubclassOf<UAnimInstance>& InClass)
{
	if (SlayAnimInstance && InClass)
	{
		SlayAnimInstance->LinkAnimClassLayers(InClass);

		CurrentAnimLayer = InClass;
	}
}

TSubclassOf<UAnimInstance> ASlay::GetLinkAnimClassLayers() const
{
	return CurrentAnimLayer;
}

//TODO
bool ASlay::IsTargetable()
{
	return true;
}
