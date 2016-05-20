// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cargo")
		UCameraComponent* firstPersonCamera;

	//Move the player forward and backward 
	UFUNCTION(BlueprintCallable, Category = "Cargo")
		void MoveForward(float value); 
	
	//Move the player left and right 
	UFUNCTION(BlueprintCallable, Category = "Cargo")
		void MoveRight(float value);
	
	//Rotate the camera Up and Down
	UFUNCTION(BlueprintCallable, Category = "Cargo")
		void LookUp(float value);

private:


};
