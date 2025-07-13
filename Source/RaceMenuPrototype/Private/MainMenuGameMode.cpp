// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuUserWidget.h"

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* pc = UGameplayStatics::GetPlayerController(this, 0);

	if (pc)
	{
		pc->bShowMouseCursor = true;

		FInputModeUIOnly input_mode;
		input_mode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		pc->SetInputMode(input_mode);
	}

	if (Main_Menu_Widget_Class)
	{
		UMainMenuUserWidget* menu = CreateWidget<UMainMenuUserWidget>(GetWorld(), Main_Menu_Widget_Class);
		if (menu)
		{
			menu->AddToViewport();
		}
	}
}
