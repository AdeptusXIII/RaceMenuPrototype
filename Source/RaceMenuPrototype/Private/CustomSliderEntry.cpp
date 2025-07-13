// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomSliderEntry.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "CustomizableActor.h"

void UCustomSliderEntry::Init_Morph(ACustomizableActor* in_actor, const FName& in_morph_name)
{
	Morph_Actor = in_actor;
	Morph_Name = in_morph_name;

	if (Text_Label)
	{
		Text_Label->SetText(FText::FromName(Morph_Name));
	}

	if (Slider_Morph_Control)
	{
		Slider_Morph_Control->OnValueChanged.AddDynamic(this, &UCustomSliderEntry::On_Slider_Value_Changed);
	}
}
//---------------------------------------------------------------------------------------------------------------
void UCustomSliderEntry::On_Slider_Value_Changed(float value)
{
	if (Morph_Actor && !Morph_Name.IsNone())
	{
		Morph_Actor->Apply_Morph(Morph_Name, value);
	}
}
//---------------------------------------------------------------------------------------------------------------