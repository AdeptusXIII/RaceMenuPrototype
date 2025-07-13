// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "RaceMenuPlayerController.generated.h"


/**
 * 
 */
class UInputMappingContext;
class UInputAction;
class ACustomizableActor;
class UCustomizationUI;

UCLASS()
class RACEMENUPROTOTYPE_API ARaceMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ARaceMenuPlayerController();
	
	void Set_Target_Actor(ACustomizableActor* in_actor);
	void On_UI_Ready(UCustomizationUI* in_ui);

	virtual void OnPossess(APawn* in_pawn) override;

protected:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float delta_time) override;

	// логика enhanced input
	void Start_Rotation(const FInputActionValue& value);
	void Stop_Rotation();
	void Rotate_Actor();

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* Input_Context;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* IA_Rotate_Actor;

	UPROPERTY()
	ACustomizableActor* Target_Actor;

	UPROPERTY()
	UCustomizationUI* Customization_UI;

	UPROPERTY(EditAnywhere, Category = "Rotation")
	float Rotation_Speed = 1.5f;

	bool bIs_Rotating = false;

};
