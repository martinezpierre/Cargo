// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "CargoActor.h"
#include "CargoInteractable.generated.h"

/**
 * 
 */
UCLASS()
class CARGO_API ACargoInteractable : public ACargoActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACargoInteractable();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
	
	virtual void Activate();

private:

	class USphereComponent* detection;
};
