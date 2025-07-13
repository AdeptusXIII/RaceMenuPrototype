// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceMenuGameMode.h"
#include "RaceMenuPlayerController.h"
#include "CustomizationUI.h"
#include "CustomizableActor.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h" // получение контроллера игрока


void ARaceMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	UWorld* world = GetWorld();
	if (!world) return;

	if (!Customizable_Actor_Class || !Customization_UI_Class) return;

	// Спавним актера
	FVector spawn_location = FVector(150.f, 0.f, 0.f);
	FRotator spawn_rotation = FRotator(0.f, 180.f, 0.f);

	ACustomizableActor* spawned_actor = world->SpawnActor<ACustomizableActor>(Customizable_Actor_Class, spawn_location, spawn_rotation);

	ARaceMenuPlayerController* rm_pc = Cast<ARaceMenuPlayerController>(UGameplayStatics::GetPlayerController(world, 0));
	if (rm_pc)
		rm_pc->Set_Target_Actor(spawned_actor);
	

	// Создание и отображение UI

	UCustomizationUI* ui = CreateWidget<UCustomizationUI>(GetWorld(), Customization_UI_Class);
	if (!ui) return;

	if (rm_pc)
		rm_pc->On_UI_Ready(ui);

	ui->AddToViewport();

	TArray<FName> morph_names = spawned_actor->Get_Available_Morph_Targets();

	ui->InitCustomization(spawned_actor, morph_names);

}
//---------------------------------------------------------------------------------------------------------------
