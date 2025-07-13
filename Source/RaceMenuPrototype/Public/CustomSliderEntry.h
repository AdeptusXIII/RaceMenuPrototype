// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CustomSliderEntry.generated.h"


class ACustomizableActor;
class USlider;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RACEMENUPROTOTYPE_API UCustomSliderEntry : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "MorphSlider")
	void Init_Morph(ACustomizableActor* in_actor, const FName& in_morph_name);

protected:

	UFUNCTION()
	void On_Slider_Value_Changed(float value);

	UPROPERTY()
	ACustomizableActor* Morph_Actor;

	UPROPERTY()
	FName Morph_Name;

	UPROPERTY(meta = (BindWidget))
	USlider* Slider_Morph_Control; //создать сответсвующий в блюпринте и назвать таким же именем

	UPROPERTY(meta = (BindWidget)) //создать сответсвующий в блюпринте и назвать таким же именем
	UTextBlock* Text_Label;

	
};
