// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceMenuPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "CustomizableActor.h"
#include "CustomizationUI.h"
#include "Kismet/GameplayStatics.h"

ARaceMenuPlayerController::ARaceMenuPlayerController()
{
	bShowMouseCursor = true;
}
//---------------------------------------------------------------------------------------------------------------
void ARaceMenuPlayerController::Set_Target_Actor(ACustomizableActor* in_actor)
{
	Target_Actor = in_actor;
}
//---------------------------------------------------------------------------------------------------------------
void ARaceMenuPlayerController::On_UI_Ready(UCustomizationUI* in_ui)
{
	Customization_UI = in_ui;
}
void ARaceMenuPlayerController::OnPossess(APawn* in_pawn)
{
	Super::OnPossess(in_pawn);

	if (UEnhancedInputLocalPlayerSubsystem* subsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (Input_Context)
		{
			subsystem->AddMappingContext(Input_Context, 0);
			UE_LOG(LogTemp, Warning, TEXT("Enhanced Input Mapping Context added in OnPossess"));
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Current Controller: %s"), *GetClass()->GetName());
}
//---------------------------------------------------------------------------------------------------------------
void ARaceMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("GameMode: %s"), *GetClass()->GetName());

	FInputModeGameAndUI mode;
	mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	mode.SetHideCursorDuringCapture(false);
	SetInputMode(mode);
	/*if (UEnhancedInputLocalPlayerSubsystem* subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (Input_Context)
		{
			subsystem->ClearAllMappings();
			subsystem->AddMappingContext(Input_Context, 0);
		
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("RACE MENU PLAYER CONTROLLER BEGIN PLAY"));*/
}
//---------------------------------------------------------------------------------------------------------------
void ARaceMenuPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UE_LOG(LogTemp, Warning, TEXT("SetupInputComponent called"));

	// привязка функций вращения к кнопкам
	if (UEnhancedInputComponent* enhanced_input = Cast<UEnhancedInputComponent>(InputComponent))
	{
		if(IA_Rotate_Actor)
		{
			enhanced_input->BindAction(IA_Rotate_Actor, ETriggerEvent::Triggered, this, &ARaceMenuPlayerController::Start_Rotation);
			enhanced_input->BindAction(IA_Rotate_Actor, ETriggerEvent::Completed, this, &ARaceMenuPlayerController::Stop_Rotation);
		}
	}
}
//---------------------------------------------------------------------------------------------------------------
void ARaceMenuPlayerController::PlayerTick(float delta_time)
{
	Super::PlayerTick(delta_time);

	if (bIs_Rotating)
	{
		Rotate_Actor();
	}
}
//---------------------------------------------------------------------------------------------------------------
void ARaceMenuPlayerController::Start_Rotation(const FInputActionValue& value)
{
	UE_LOG(LogTemp, Warning, TEXT("Start_Rotation called"));
	bIs_Rotating = true;
}
//---------------------------------------------------------------------------------------------------------------
void ARaceMenuPlayerController::Stop_Rotation()
{
	bIs_Rotating = false;
}
//---------------------------------------------------------------------------------------------------------------
void ARaceMenuPlayerController::Rotate_Actor()
{
	if (!Target_Actor) return;

	UE_LOG(LogTemp, Warning, TEXT("Rotate_Actor called"));

	float mouse_x, mouse_y; 
	GetInputMouseDelta(mouse_x, mouse_y);
	if (FMath::Abs(mouse_x) > KINDA_SMALL_NUMBER)
	{
		FRotator current_rotation = Target_Actor->GetActorRotation();
		current_rotation.Yaw += mouse_x * Rotation_Speed;
		Target_Actor->SetActorRotation(current_rotation);
	}
	
}

