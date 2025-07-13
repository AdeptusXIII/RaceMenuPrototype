// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "Kismet/Gameplaystatics.h"


AMainCharacter::AMainCharacter()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	Spring_Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Spring_Arm->SetupAttachment(RootComponent);
	Spring_Arm->TargetArmLength = 300.f;
	Spring_Arm->bUsePawnControlRotation = true; //поворот вместе с камерой

	Follow_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	Follow_Camera->SetupAttachment(Spring_Arm, USpringArmComponent::SocketName);
	Follow_Camera->bUsePawnControlRotation = false; // камера не будет поворачиваться сама по себе, потому что приатачена к спрингу

	GetMesh()->SetupAttachment(RootComponent);

	APlayerController* pc = UGameplayStatics::GetPlayerController(GetWorld(), 0);    // <--- изменить в будущем на другой инпут мод
	if (pc)
	{
		FInputModeGameOnly input_mode;
		pc->SetInputMode(input_mode);
		pc->bShowMouseCursor = false;
	}

}

void AMainCharacter::Tick(float delta_time)
{
	Super::Tick(delta_time);

}


void AMainCharacter::SetupPlayerInputComponent(UInputComponent* player_input_component)
{
	Super::SetupPlayerInputComponent(player_input_component);

	if (UEnhancedInputComponent* eic = Cast<UEnhancedInputComponent>(player_input_component))
	{
		eic->BindAction(IA_Move, ETriggerEvent::Triggered, this, &AMainCharacter::Move);
		eic->BindAction(IA_Look, ETriggerEvent::Triggered, this, &AMainCharacter::Look);
		eic->BindAction(IA_Jump, ETriggerEvent::Started, this, &AMainCharacter::Jump);
		eic->BindAction(IA_Jump, ETriggerEvent::Completed, this, &AMainCharacter::Jump);
	}

}

void AMainCharacter::Apply_Morphs(const TArray<FMorphTargetEntry>& morphs)
{
	for (const FMorphTargetEntry& entry : morphs)
	{
		if (GetMesh())
		{
			GetMesh()->SetMorphTarget(entry.Morph_Name, entry.Morph_Value);
		}
	}
}

void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* pc = Cast<APlayerController>(GetController()))
	{
		if(UEnhancedInputLocalPlayerSubsystem* subsytem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(pc->GetLocalPlayer()))
		{
			subsytem->AddMappingContext(Input_Mapping, 0);
		}
	}

}

void AMainCharacter::Move(const FInputActionValue& value)
{
	const FVector2D input = value.Get<FVector2D>();
	if (Controller && (input != FVector2D::ZeroVector))
	{
		const FRotator rotation = Controller->GetControlRotation();
		const FRotator yaw_rotation(0.f, rotation.Yaw, 0.f);

		const FVector forward = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::X);
		const FVector right = FRotationMatrix(yaw_rotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(forward, input.Y);
		AddMovementInput(right, input.X);
		
	}
	UE_LOG(LogTemp, Warning, TEXT("Input: x = %f, y = %f"), input.X, input.Y);
}

void AMainCharacter::Look(const FInputActionValue& value)
{
	const FVector2D look_axis = value.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(look_axis.X);
		AddControllerPitchInput(look_axis.Y);
	}
}

void AMainCharacter::Jump()
{
	Super::Jump();
}

void AMainCharacter::StopJumping()
{
	Super::StopJumping();
}


