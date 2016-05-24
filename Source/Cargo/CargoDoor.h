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

	// Called to replicate variables
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	virtual void Interact(ACargoPlayer* user) override;
	
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	int detectionRadius;

	/** Handle the fire when the player hit the left mouse button (CLIENT)*/
	void SetDoorPosition();

	/** Handle the fire when the player hit the left mouse button (CLIENT)*/
	void OpenDoor(float speed, bool b);

	/** Handle the fire when the player hit the left mouse button (CLIENT)*/
	void OpenDoorMulticast(float speed, bool b);

	/** Handle the fire when the player hit the left mouse button (SERVER)*/
	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void ServerOpenDoorMulticast(float speed, bool b);
	virtual void ServerOpenDoorMulticast_Implementation(float speed, bool b);
	virtual bool ServerOpenDoorMulticast_Validate(float speed, bool b);

	UPROPERTY(Replicated)
	bool canOpen;

	UPROPERTY(Replicated)
	FVector step;

	UPROPERTY(Replicated)
	FVector openPos;

	UPROPERTY(Replicated)
	FVector closedPos;

private:


};
