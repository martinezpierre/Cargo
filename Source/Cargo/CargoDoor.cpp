// Fill out your copyright notice in the Description page of Project Settings.

#include "Cargo.h"
#include "CargoDoor.h"
#include "UnrealNetwork.h"

ACargoDoor::ACargoDoor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	detectionRadius = 100;
}

// Called when the game starts or when spawned
void ACargoDoor::BeginPlay()
{
	Super::BeginPlay();

	canOpen = false;

	closedPos = mesh->GetComponentLocation();

	openPos = closedPos + FVector(0,0,400);

}

// Called every frame
void ACargoDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetDoorPosition();
}


void ACargoDoor::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACargoDoor, canOpen);

}

void ACargoDoor::Interact(ACargoPlayer* user)
{
	Super::Interact(user);

	OpenDoorMulticast(10,true);

	UE_LOG(LogTemp, Warning, TEXT("Player detected"));
}

void ACargoDoor::SetDoorPosition()
{
	if (nbActors <= 0)
	{
		canOpen = false;
	}

	if (canOpen && mesh->GetComponentLocation() != openPos)
	{
		FVector newPos = mesh->GetComponentLocation() + step;

		mesh->SetWorldLocation(newPos, false);
	}
	else if (!canOpen && mesh->GetComponentLocation() != closedPos)
	{
		FVector newPos = mesh->GetComponentLocation() - step;

		mesh->SetWorldLocation(newPos, false);
	}
}

void ACargoDoor::OpenDoor(float speed, bool b)
{
	canOpen = b;

	step = (openPos - closedPos) / 1000 * speed;
}

void ACargoDoor::OpenDoorMulticast(float speed, bool b)
{
	canOpen = b;

	step = (openPos - closedPos) / 1000 * speed;

	ServerOpenDoorMulticast(speed, b);
}

void ACargoDoor::ServerOpenDoorMulticast_Implementation(float speed, bool b)
{
	canOpen = b;

	step = (openPos - closedPos) / 1000 * speed;
}

bool ACargoDoor::ServerOpenDoorMulticast_Validate(float speed, bool b)
{
	return true;
}

