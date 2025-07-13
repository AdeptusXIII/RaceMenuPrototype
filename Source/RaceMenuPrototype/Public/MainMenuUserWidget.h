// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuUserWidget.generated.h"

class UButton;

UCLASS()
class RACEMENUPROTOTYPE_API UMainMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeConstruct() override;

	// Кнопки из блюпринтов
	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Start;

	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Exit;

	// функции кнопок
	UFUNCTION()
	void On_Start_Clicked();

	UFUNCTION()
	void On_Exit_Clicked();
};
