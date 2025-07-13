// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CustomizableActor.h"
#include "RaceMenuGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RACEMENUPROTOTYPE_API URaceMenuGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "Morphs") // сохран€ет текущие морфы
	void Set_Saved_Morphs(const TArray<FMorphTargetEntry>& new_morphs);

	UFUNCTION(BlueprintCallable, Category = "Morphs") // возврат текущих морфоф
	const TArray < FMorphTargetEntry>& Get_Saved_Morphs() const;



	UPROPERTY(BlueprintReadWrite, VisibleAnywhere) // €чейка дл€ хранени€ текущих значений морфов
		TMap<FName, float> Morph_Values;

protected:

	UPROPERTY()
	TArray<FMorphTargetEntry> Saved_Morph_Targets;
};
