// Fill out your copyright notice in the Description page of Project Settings.

#include "Cargo.h"
#include "CargoDoor.h"

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

	closedPos = GetActorLocation();

	openPos = closedPos + FVector(0,0,400);

	Interact(nullptr);

}

// Called every frame
void ACargoDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (nbActors <= 0) 
	{
		canOpen = false;
	}

	if (canOpen && GetActorLocation()!= openPos) 
	{
		FVector newPos = GetActorLocation() + step;

		SetActorLocation(newPos,false);
	}
	else if (!canOpen && GetActorLocation() != closedPos) 
	{
		FVector newPos = GetActorLocation() - step;

		SetActorLocation(newPos, false);
	}
}

void ACargoDoor::Interact(ACargoActor* user)
{
	Super::Interact(user);

	OpenDoor(10);

	//UE_LOG(LogTemp, Warning, TEXT("Player detected"));
}

void ACargoDoor::OpenDoor(float speed)
{
	canOpen = true;

	step = (openPos-closedPos) / 1000 * speed;

}

void ACargoDoor::CloseDoor(float speed)
{
	canOpen = false;

	step = (openPos - closedPos) / 1000 * speed;

}




