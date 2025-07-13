// Fill out your copyright notice in the Description page of Project Settings.


#include "RaceMenuGameInstance.h"

void URaceMenuGameInstance::Set_Saved_Morphs(const TArray<FMorphTargetEntry>& new_morphs)
{
	Saved_Morph_Targets = new_morphs;
}

const TArray<FMorphTargetEntry>& URaceMenuGameInstance::Get_Saved_Morphs() const
{
	return Saved_Morph_Targets;
}
