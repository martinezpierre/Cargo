// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CargoInteractable.h"
#include "CargoDoor.generated.h"

/**
 * 
 */
UCLASS()
class CARGO_API ACargoDoor : public ACargoInteractable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ACargoDoor();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void Interact(ACargoActor* user) override;
	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int detectionRadius;
	
private:

	FVector step;

	void OpenDoor(float speed);

	void CloseDoor(float speed);

	bool canOpen;

	FVector openPos;
	FVector closedPos;

};
