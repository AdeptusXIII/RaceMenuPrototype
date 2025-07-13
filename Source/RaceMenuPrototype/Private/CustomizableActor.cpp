// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomizableActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/MorphTarget.h"

// Sets default values
ACustomizableActor::ACustomizableActor()
{
	PrimaryActorTick.bCanEverTick = true;

	Body_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BodyMesh"));

	SetRootComponent(Body_Mesh);

}
//---------------------------------------------------------------------------------------------------------------
void ACustomizableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
//---------------------------------------------------------------------------------------------------------------
void ACustomizableActor::Apply_Morph(const FName morph_name, float value)
{
	if (Body_Mesh)
	{
		Body_Mesh->SetMorphTarget(morph_name, value);
	}
}


TArray<FName> ACustomizableActor::Get_Available_Morph_Targets() const
{
	TArray<FName> out_morph_names;

	if (!Body_Mesh) return out_morph_names;

	USkeletalMesh* skeletal_mesh = Body_Mesh->GetSkeletalMeshAsset();
	if (!skeletal_mesh) return out_morph_names;
	
	const TArray<UMorphTarget*>& morph_targets = skeletal_mesh->GetMorphTargets();

	for (const UMorphTarget* target : morph_targets)
	{
		if (target)
		{
			out_morph_names.Add(target->GetFName());
		}
	}
	

	return out_morph_names;
}
//---------------------------------------------------------------------------------------------------------------
void ACustomizableActor::BeginPlay()
{
	Super::BeginPlay();
	
}




