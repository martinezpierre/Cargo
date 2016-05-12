// Fill out your copyright notice in the Description page of Project Settings.

#include "Cargo.h"
#include "CargoIA.h"


// Sets default values
ACargoIA::ACargoIA()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACargoIA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACargoIA::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACargoIA::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

