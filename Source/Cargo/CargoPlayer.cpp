// Fill out your copyright notice in the Description page of Project Settings.

#include "Cargo.h"
#include "CargoPlayer.h"


// Sets default values
ACargoPlayer::ACargoPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACargoPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACargoPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void ACargoPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

