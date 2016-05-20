// Fill out your copyright notice in the Description page of Project Settings.

#include "Cargo.h"
#include "CargoPlayer.h"


// Sets default values
ACargoPlayer::ACargoPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Sets default values
ACargoPlayer::ACargoPlayer(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//RootComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("RootComponent"));

	//create a CameraComponent 
	firstPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("FirstPersonCamera"));
	//attach it to the root component 
	firstPersonCamera->AttachTo(RootComponent);
	firstPersonCamera->SetRelativeLocation(FVector(0.0f, 0.0f, BaseEyeHeight));
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

	InputComponent->BindAxis("MoveForward", this, &ACargoPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ACargoPlayer::MoveRight);

	InputComponent->BindAxis("Turn", this, &ACargoPlayer::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &ACargoPlayer::LookUp);

}

//Move the player forward and backward 
void ACargoPlayer::MoveForward(float value)
{ 
	if ((Controller != NULL) && (value != 0.0f)) 
	{ 
		//Find out which way is forward 
		FRotator Rotation = Controller->GetControlRotation(); 
		//limit pitch when walking or falling 
		if (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling()) 
		{ 
			Rotation.Pitch = 0.0f; 
		} 
		//add movement in that direction 
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X); 
		AddMovementInput(Direction, value); 
	} 
}

//Move the player left and right 
void ACargoPlayer::MoveRight(float value)
{
	if ((Controller != NULL) && (value != 0.0f))
	{
		//Find out which way is forward 
		FRotator Rotation = Controller->GetControlRotation();
		//add movement in that direction 
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, value);
	}
}

void ACargoPlayer::LookUp(float value)
{
	firstPersonCamera->AddLocalRotation(FRotator(value, 0.0f, 0.0f));
	/*FRotator rot = firstPersonCamera->GetComponentRotation();
	rot.Roll += value;
	rot.Roll = FMath::Clamp(rot.Roll, 10.0f, 170.0f);
	firstPersonCamera->SetRelativeRotation(rot);*/
}
