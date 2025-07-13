// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CustomizableActor.generated.h"

USTRUCT(BlueprintType)
struct FMorphTargetEntry
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FName Morph_Name;

	UPROPERTY(BlueprintReadWrite)
	float Morph_Value;

	FMorphTargetEntry() : Morph_Name(NAME_None), Morph_Value(0.f) {}
	FMorphTargetEntry(FName in_name, float in_value) : Morph_Name(in_name), Morph_Value(in_value) {}
};

class USkeletalMeshComponent;

UCLASS()
class RACEMENUPROTOTYPE_API ACustomizableActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ACustomizableActor();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Morphs")
	void Apply_Morph(const FName morph_name, float value);

	UFUNCTION(BlueprintCallable, Category = "Customizable Morph Targets")
	TArray<FName> Get_Available_Morph_Targets() const;

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* Get_Body_Mesh() const { return Body_Mesh; }
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* Body_Mesh;

};
