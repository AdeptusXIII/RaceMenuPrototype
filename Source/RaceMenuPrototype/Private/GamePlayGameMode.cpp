// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayGameMode.h"
#include "MainCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "RaceMenuGameInstance.h"
#include "Kismet/GameplayStatics.h"

AGamePlayGameMode::AGamePlayGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> player_pawn_class_finder(TEXT("/Game/Logic/MainCharacter/BP_MainCharacter"));
	if (player_pawn_class_finder.Succeeded())
	{
		DefaultPawnClass = player_pawn_class_finder.Class;
	}
}

void AGamePlayGameMode::BeginPlay()
{
	// получение гейм инстанса
	URaceMenuGameInstance* game_instance = Cast<URaceMenuGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (!game_instance) return;

	ACharacter* character = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	AMainCharacter* main_character = Cast<AMainCharacter>(character);

	if (main_character)
	{
		main_character->Apply_Morphs(game_instance->Get_Saved_Morphs());
		UE_LOG(LogTemp, Warning, TEXT("Morphs applied to MainCharacter"));
	}
}
