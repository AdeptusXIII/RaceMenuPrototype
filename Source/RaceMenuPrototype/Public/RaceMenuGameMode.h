// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "RaceMenuGameMode.generated.h"

/**
 * 
 */
class ACustomizableActor;
class UCustomizationUI;

UCLASS()
class RACEMENUPROTOTYPE_API ARaceMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCustomizationUI> Customization_UI_Class;

	UPROPERTY(EditDefaultsOnly, Category = "TargetActor")
	TSubclassOf<ACustomizableActor> Customizable_Actor_Class;
};
