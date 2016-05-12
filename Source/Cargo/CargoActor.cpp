// Fill out your copyright notice in the Description page of Project Settings.

#include "Cargo.h"
#include "CargoActor.h"


// Sets default values
ACargoActor::ACargoActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACargoActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACargoActor::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

