// Fill out your copyright notice in the Description page of Project Settings.

#include "Cargo.h"
#include "CargoInteractable.h"
#include "CargoCharacter.h"
#include "CargoPlayer.h"

ACargoInteractable::ACargoInteractable()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	detection = CreateDefaultSubobject<USphereComponent>(TEXT("Detection"));
	detection->AttachTo(RootComponent);
	detection->SetSphereRadius(300);

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	mesh->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void ACargoInteractable::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACargoInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> actors;

	GetOverlappingActors(actors);

	for (auto It = actors.CreateConstIterator(); It; ++It)
	{
		auto player = Cast<ACargoPlayer>(*It);
		if (player) {

			player->currentInteractable = this;

			//UE_LOG(LogTemp, Warning, TEXT("Player detected"));
		}
	}

	nbActors = actors.Num();
}

void ACargoInteractable::Interact(ACargoPlayer* user)
{

}




