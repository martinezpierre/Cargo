// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CargoInteractable.h"
#include "GameFramework/Character.h"
#include "CargoPlayer.generated.h"

UCLASS()
class CARGO_API ACargoPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACargoPlayer();

	ACargoPlayer(const FObjectInitializer& ObjectInitializer);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	// Called to replicate variables
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	//the camera of the firstPersonView
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo - Camera")
	UCameraComponent* firstPersonCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo - Camera")
	USpringArmComponent* cameraSpringArm;
	UCameraComponent* thirstPersonCamera;

	//the mesh of the firstPersonView
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo - Character")
	USkeletalMeshComponent* firstPersonStaticMesh;

	//the mesh of the thirdPersonView
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo - Character")
	USkeletalMeshComponent* thirdPersonStaticMesh;

	USkeletalMeshComponent* GetThirdPersonStaticMesh();

	//the place where the player will hold ragdolls and objects
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo - Character")
	UArrowComponent* holdPlace;

	//length of the vector when a player fire
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo - variables")
	float hitLength;

	//length of the vector when a player want to pick up an object or a ragdoll
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "Cargo - variables")
	float pickUpLength;

	//if the player is stunned or not..
	UPROPERTY(Replicated)
	bool stunned;

	//if the player is carrying object or not..
	UPROPERTY(Replicated)
	bool isCarrying;

	ACargoPlayer* pickedUpRagdoll;

	//Move the player forward and backward 
	UFUNCTION(BlueprintCallable, Category = "Cargo - Fonctions")
	void MoveForward(float value); 
	
	//Move the player left and right 
	UFUNCTION(BlueprintCallable, Category = "Cargo - Fonctions")
	void MoveRight(float value);
	
	//Rotate the camera Up and Down
	UFUNCTION(BlueprintCallable, Category = "Cargo - Fonctions")
	void LookUp(float value);

	//Return if the player is stun, true = stunned
	UFUNCTION(BlueprintCallable, Category = "Cargo - Fonctions")
	bool IsStunned();

	/** Handle the fire when the player hit the left mouse button (CLIENT)*/
	void Fire();

	/** Handle the fire when the player hit the left mouse button (SERVER)*/
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerFire();
	virtual void ServerFire_Implementation();
	virtual bool ServerFire_Validate();

	/** Handle the fire when the player hit the left mouse button (CLIENT)*/
	void BecomeARagdoll();

	/** Handle the fire when the player hit the left mouse button (SERVER)*/
	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void ServerBecomeARagdoll();
	virtual void ServerBecomeARagdoll_Implementation();
	virtual bool ServerBecomeARagdoll_Validate();

	/** Handle the fire when the player hit the left mouse button (CLIENT)*/
	void ChangeThirdPersonMeshVisibility();

	/** Handle the fire when the player hit the left mouse button (SERVER)*/
	UFUNCTION(Reliable, client, WithValidation)
	void ServerChangeThirdPersonMeshVisibility();
	virtual void ServerChangeThirdPersonMeshVisibility_Implementation();
	virtual bool ServerChangeThirdPersonMeshVisibility_Validate();

	/** Handle the fire when the player hit the left mouse button (CLIENT)*/
	void Action();

	/** Handle the fire when the player hit the left mouse button (SERVER)*/
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerAction();
	virtual void ServerAction_Implementation();
	virtual bool ServerAction_Validate();

	/** Handle the fire when the player hit the left mouse button (CLIENT)*/
	void UpdatePickedUpRagdoll();

	/** Handle the fire when the player hit the left mouse button (SERVER)*/
	UFUNCTION(Reliable, NetMulticast, WithValidation)
	void ServerUpdatePickedUpRagdoll();
	virtual void ServerUpdatePickedUpRagdoll_Implementation();
	virtual bool ServerUpdatePickedUpRagdoll_Validate();

	ACargoInteractable* currentInteractable;

private:



};
