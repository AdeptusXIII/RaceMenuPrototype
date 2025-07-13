// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Blueprint/WidgetTree.h"

void UMainMenuUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BTN_Start)
	{
		BTN_Start->OnClicked.AddDynamic(this, &UMainMenuUserWidget::On_Start_Clicked);
	}
	if (BTN_Exit)
	{
		BTN_Exit->OnClicked.AddDynamic(this, &UMainMenuUserWidget::On_Exit_Clicked);
	}
}

void UMainMenuUserWidget::On_Start_Clicked()
{
	
	UGameplayStatics::OpenLevel(this, "L_RaceMenu");
	
}

void UMainMenuUserWidget::On_Exit_Clicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, false);
}
