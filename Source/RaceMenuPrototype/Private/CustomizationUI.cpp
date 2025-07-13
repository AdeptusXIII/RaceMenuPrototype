// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomizationUI.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "CustomSliderEntry.h"
#include "CustomizableActor.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "RaceMenuGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UCustomizationUI::NativeConstruct()
{
	Super::NativeConstruct();

	if (BTN_Save_Morphs)
		BTN_Save_Morphs->OnClicked.AddDynamic(this, &UCustomizationUI::On_Save_Morphs_Clicked);
	if (BTN_Start_Game)
		BTN_Start_Game->OnClicked.AddDynamic(this, &UCustomizationUI::On_Start_Game_Clicked);
	if (BTN_Return_To_Menu)
		BTN_Return_To_Menu->OnClicked.AddDynamic(this, &UCustomizationUI::On_Return_To_Menu_Clicked);

	Race_Menu_Game_Instance = Cast<URaceMenuGameInstance>(GetGameInstance());
}
//---------------------------------------------------------------------------------------------------------------
void UCustomizationUI::NativeTick(const FGeometry& geometry, float in_delta_time)
{
	Super::NativeTick(geometry, in_delta_time);
}
//---------------------------------------------------------------------------------------------------------------
void UCustomizationUI::On_Save_Morphs_Clicked()
{
	if (!Morph_Actor || !Race_Menu_Game_Instance) return;

	TArray<FName> morph_names = Morph_Actor->Get_Available_Morph_Targets();
	TArray<FMorphTargetEntry> entries;

	for (const FName& morph : morph_names)
	{
		float value = Morph_Actor->Get_Body_Mesh()->GetMorphTarget(morph);
		entries.Add(FMorphTargetEntry(morph, value));
	}

	Race_Menu_Game_Instance->Set_Saved_Morphs(entries);

	UE_LOG(LogTemp, Warning, TEXT("Morphs saved: %d"), entries.Num());
}
//---------------------------------------------------------------------------------------------------------------
void UCustomizationUI::On_Start_Game_Clicked()
{
	if (!Race_Menu_Game_Instance) return;

	TArray<FMorphTargetEntry> saved_moprhs = Race_Menu_Game_Instance->Get_Saved_Morphs();

	// todo сохранить в USaveGame

	UGameplayStatics::OpenLevel(this, "L_Gameplay");

}
//---------------------------------------------------------------------------------------------------------------
void UCustomizationUI::On_Return_To_Menu_Clicked()
{
	UGameplayStatics::OpenLevel(this, "L_MainMenu");
}
//---------------------------------------------------------------------------------------------------------------
void UCustomizationUI::InitCustomization(ACustomizableActor* in_actor, const TArray<FName>& in_morph_names)
{
	Morph_Actor = in_actor;
	Morph_Names = in_morph_names;

	if (Morph_Actor && Slider_Entry_Class)
	{
		for (const FName& morph_name : Morph_Names)
		{
			// создание вложенного класса виджета внутри текущего класса в игре
			UCustomSliderEntry* entry = CreateWidget<UCustomSliderEntry>(this, Slider_Entry_Class);
			if (entry)
			{
				entry->Init_Morph(Morph_Actor, morph_name);
				UScrollBoxSlot* new_slot = Cast<UScrollBoxSlot>(ScrB_MorphScroll->AddChild(entry));
				if (new_slot)
				{
					new_slot->SetPadding(FMargin(5.0f));
					new_slot->SetHorizontalAlignment(HAlign_Fill);
				}
			}
		}
	}
}
//---------------------------------------------------------------------------------------------------------------