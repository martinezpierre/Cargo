// Fill out your copyright notice in the Description page of Project Settings.

#include "Cargo.h"
#include "CargoPlayer.h"
#include "UnrealNetwork.h"
#include "CargoInteractable.h"

// Sets default values
ACargoPlayer::ACargoPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Set this actor to be replicate.
	bReplicates = true;
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

	thirdPersonStaticMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("ThirdPersonStaticMesh"));
	thirdPersonStaticMesh->AttachTo(RootComponent);
	thirdPersonStaticMesh->SetOnlyOwnerSee(false);
	thirdPersonStaticMesh->SetOwnerNoSee(true);
	thirdPersonStaticMesh->CastShadow = true;

	firstPersonStaticMesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("FirstPersonStaticMesh"));
	firstPersonStaticMesh->AttachTo(firstPersonCamera);
	firstPersonStaticMesh->SetOnlyOwnerSee(true);
	firstPersonStaticMesh->SetOwnerNoSee(false);
	firstPersonStaticMesh->CastShadow = false;

	cameraSpringArm = ObjectInitializer.CreateDefaultSubobject<USpringArmComponent>(this, TEXT("CameraSpringArm"));
	cameraSpringArm->AttachTo(RootComponent);
	cameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	cameraSpringArm->TargetArmLength = 400.f;
	cameraSpringArm->bEnableCameraLag = true;
	cameraSpringArm->CameraLagSpeed = 3.0f;

	thirstPersonCamera = ObjectInitializer.CreateDefaultSubobject<UCameraComponent>(this, TEXT("ThirdPersonCamera"));
	thirstPersonCamera->AttachTo(cameraSpringArm, USpringArmComponent::SocketName);

	holdPlace = ObjectInitializer.CreateDefaultSubobject<UArrowComponent>(this, TEXT("HoldPlace"));
	holdPlace->AttachTo(firstPersonStaticMesh);

	hitLength = 50.0f;
	stunned = false;
	isCarrying = false;
	pickUpLength = 500.0f;
	pickedUpRagdoll = nullptr;
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

	InputComponent->BindAction("Fire", IE_Pressed, this, &ACargoPlayer::Fire);
	InputComponent->BindAction("Action", IE_Pressed, this, &ACargoPlayer::Action);


}

void ACargoPlayer::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ACargoPlayer, stunned);
	DOREPLIFETIME(ACargoPlayer, pickUpLength);

}

USkeletalMeshComponent* ACargoPlayer::GetThirdPersonStaticMesh()
{
	return thirdPersonStaticMesh;
}

//Move the player forward and backward 
void ACargoPlayer::MoveForward(float value)
{ 
	if ((Controller != NULL) && (value != 0.0f) && !stunned)
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
	if ((Controller != NULL) && (value != 0.0f) && !stunned)
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

bool ACargoPlayer::IsStunned()
{
	return stunned;
}

void ACargoPlayer::Fire()
{
	if (Role < ROLE_Authority && !stunned)
	{
		ServerFire();
	}
}

void ACargoPlayer::ServerFire_Implementation()
{
	//location the PC is focused on
	const FVector Start = firstPersonCamera->GetComponentLocation();
	//1000 units in facing direction of PC (500 units in front of the camera)
	const FVector End = Start + (firstPersonCamera->GetForwardVector() * hitLength);
	FHitResult HitInfo;
	FCollisionQueryParams QParams;
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams OParams =	FCollisionQueryParams::DefaultQueryParam;

	if (GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECollisionChannel::ECC_Visibility))
	{
		auto MyPC = Cast<ACargoPlayer>(HitInfo.GetActor());
		if (MyPC && !MyPC->IsStunned())
		{
			UE_LOG(LogTemp, Warning, TEXT("Player hit !"));
			MyPC->BecomeARagdoll();
			MyPC->ChangeThirdPersonMeshVisibility();
			MyPC->ServerBecomeARagdoll();
		}
	}
}

bool ACargoPlayer::ServerFire_Validate()
{
	return true;
}

void ACargoPlayer::BecomeARagdoll()
{

	/*if (Role < ROLE_Authority)
	{*/
		ServerBecomeARagdoll();
	//}
}

void ACargoPlayer::ServerBecomeARagdoll_Implementation()
{
	thirdPersonStaticMesh->SetSimulatePhysics(true);
	thirdPersonStaticMesh->SetCollisionProfileName("Ragdoll");
	GetCapsuleComponent()->SetCollisionProfileName("NoCollision");
	stunned = true;
}


bool ACargoPlayer::ServerBecomeARagdoll_Validate()
{
	return true;
}

void ACargoPlayer::ChangeThirdPersonMeshVisibility()
{
	ServerChangeThirdPersonMeshVisibility();
}

void ACargoPlayer::ServerChangeThirdPersonMeshVisibility_Implementation()
{
	thirdPersonStaticMesh->SetOwnerNoSee(false);
	firstPersonStaticMesh->SetVisibility(false);
	firstPersonCamera->Deactivate();
}

bool ACargoPlayer::ServerChangeThirdPersonMeshVisibility_Validate()
{
	return true;
}

void ACargoPlayer::Action()
{

	/*//location the PC is focused on
	const FVector Start = firstPersonCamera->GetComponentLocation();
	//1000 units in facing direction of PC (500 units in front of the camera)
	const FVector End = Start + (firstPersonCamera->GetForwardVector() * pickUpLength);
	FHitResult HitInfo;
	FCollisionQueryParams QParams;
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams OParams = FCollisionQueryParams::DefaultQueryParam;

	if (GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECollisionChannel::ECC_Visibility))
	{
		auto ragdoll = Cast<ACargoPlayer>(HitInfo.GetActor());
		if (ragdoll && ragdoll->IsStunned())
		{
			UE_LOG(LogTemp, Warning, TEXT("pickup Ragdoll"));
			pickedUpRagdoll = ragdoll;
			UpdatePickedUpRagdoll();
		}
		
		auto object = Cast<ACargoInteractable>(HitInfo.GetActor());

		if (object) 
		{
			UE_LOG(LogTemp, Warning, TEXT("interact 1"));
			object->Interact(this);
		}
	}*/

	if (Role < ROLE_Authority && !stunned)
	{
		ServerAction();
	}
}

void ACargoPlayer::ServerAction_Implementation()
{
	//Action();
	//location the PC is focused on
	const FVector Start = firstPersonCamera->GetComponentLocation();
	//1000 units in facing direction of PC (500 units in front of the camera)
	const FVector End = Start + (firstPersonCamera->GetForwardVector() * pickUpLength);
	FHitResult HitInfo;
	FCollisionQueryParams QParams;
	ECollisionChannel Channel = ECollisionChannel::ECC_Visibility;
	FCollisionQueryParams OParams = FCollisionQueryParams::DefaultQueryParam;

	if (GetWorld()->LineTraceSingleByChannel(HitInfo, Start, End, ECollisionChannel::ECC_Visibility))
	{
		auto ragdoll = Cast<ACargoPlayer>(HitInfo.GetActor());
		if (ragdoll && ragdoll->IsStunned())
		{
			UE_LOG(LogTemp, Warning, TEXT("pickup Ragdoll"));
			pickedUpRagdoll = ragdoll;
			UpdatePickedUpRagdoll();
		}

		auto object = Cast<ACargoInteractable>(HitInfo.GetActor());

		if (object)
		{
			UE_LOG(LogTemp, Warning, TEXT("interact 1"));
			object->Interact(this);
		}
	}
}

bool ACargoPlayer::ServerAction_Validate()
{
	return true;
}

void ACargoPlayer::UpdatePickedUpRagdoll()
{
	ServerUpdatePickedUpRagdoll();
}

void ACargoPlayer::ServerUpdatePickedUpRagdoll_Implementation()
{
	if (pickedUpRagdoll)
	{
		pickedUpRagdoll->SetActorLocation(holdPlace->GetComponentLocation());
	}
}

bool ACargoPlayer::ServerUpdatePickedUpRagdoll_Validate()
{
	return true;
}
