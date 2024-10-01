// LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "Player/LMADefaultCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Components/DecalComponent.h"
#include "Components/InputComponent.h"

ALMADefaultCharacter::ALMADefaultCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->SetUsingAbsoluteRotation(true);
	SpringArmComponent->TargetArmLength = ArmLenght;
	SpringArmComponent->SetRelativeRotation(FRotator(YRotation, 0.0f, 0.0f));
	SpringArmComponent->bDoCollisionTest = false;
	SpringArmComponent->bEnableCameraLag = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->SetFieldOfView(FOV);
	CameraComponent->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	MaxStamina = 100.0f;
	Stamina = MaxStamina;
	StaminaDrainRate = 10.0f;
	StaminaRegenRate = 5.0f;
	bIsSprinting = false;
	bCanSprint = true;
}
 
void ALMADefaultCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (CursorMaterial)
	{
		CurrentCursor = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), CursorMaterial, CursorSize, FVector(0));
	}
}

void ALMADefaultCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PC)
	{
		FHitResult ResultHit;
		PC->GetHitResultUnderCursor(ECC_GameTraceChannel1, true, ResultHit);
		float FindRotatorResultYaw = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), ResultHit.Location).Yaw;
		SetActorRotation(FQuat(FRotator(0.0f, FindRotatorResultYaw, 0.0f)));
		if (CurrentCursor)
		{
			CurrentCursor->SetWorldLocation(ResultHit.Location);
		}	
	}

	if (bIsSprinting && Stamina > 0)
	{
		Stamina -= StaminaDrainRate * DeltaTime;
		if (Stamina <= 0)
		{
			Stamina = 0;
			StopSprinting();
		}
		else if (!bIsSprinting && Stamina < MaxStamina)
		{
			Stamina += StaminaRegenRate * DeltaTime;
			if (Stamina > MaxStamina)
			{
				Stamina = MaxStamina;
			}
		}
	}
	bCanSprint = (Stamina > 0);
}

void ALMADefaultCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Move_Forward", this, &ALMADefaultCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move_Right", this, &ALMADefaultCharacter::MoveRight);

	PlayerInputComponent->BindAxis("ZoomCamera", this, &ALMADefaultCharacter::ZoomCamera);

	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ALMADefaultCharacter::StartSprinting);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ALMADefaultCharacter::StopSprinting);
	//PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &ALMADefaultCharacter::PauseMenu);
}

void ALMADefaultCharacter::StartSprinting()
{
	if (Stamina > 0 && bCanSprint)
	{
		bIsSprinting = true;
	}
}

void ALMADefaultCharacter::StopSprinting()
{
	bIsSprinting = false;
}

void ALMADefaultCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void ALMADefaultCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void ALMADefaultCharacter::PauseMenu(float Value)
{
}

void ALMADefaultCharacter::ZoomCamera(float Val)
{
	if (Val != 0.0f)
	{
		CurZoomDis -= Val * ZoomSpeed;
		
		CurZoomDis = FMath::Clamp(CurZoomDis, MinZoomDis, MaxZoomDis);
		
		if (SpringArmComponent)
		{
			SpringArmComponent->TargetArmLength = CurZoomDis;
		}
	}
}
