// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomizationUI.generated.h"

/**
 * 
 */
class UScrollBox;
class ACustomizableActor;
class UCustomSliderEntry;
class UButton;
class URaceMenuGameInstance;

UCLASS()
class RACEMENUPROTOTYPE_API UCustomizationUI : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Morph")
	void InitCustomization(ACustomizableActor* in_actor, const TArray<FName>& in_morph_names);

protected:

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& geometry, float in_delta_time ) override;

	UFUNCTION()
	void On_Save_Morphs_Clicked();

	UFUNCTION()
	void On_Start_Game_Clicked();

	UFUNCTION()
	void On_Return_To_Menu_Clicked();

	// левая панель слайдеров
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ScrB_MorphScroll;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Target Slider Class")
	TSubclassOf<class UCustomSliderEntry> Slider_Entry_Class;

	// правая панель кнопок

	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Save_Morphs;

	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Start_Game;

	UPROPERTY(meta = (BindWidget))
	UButton* BTN_Return_To_Menu;

	// вспомагательные переменные

	UPROPERTY()
	ACustomizableActor* Morph_Actor;

	UPROPERTY()
	TArray<FName> Morph_Names;

	UPROPERTY()
	URaceMenuGameInstance* Race_Menu_Game_Instance;

};
