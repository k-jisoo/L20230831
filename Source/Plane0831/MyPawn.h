// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyPawn.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UArrowComponent;
class UMyActorComponent;
class UFloatingPawnMovement;

UCLASS()
class PLANE0831_API AMyPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void Pitch(float Value);
	
	void Roll(float Value);

	void Boost();

	void UnBoost();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UBoxComponent* Box;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Body;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Left;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UStaticMeshComponent* Right;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UCameraComponent* Camera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UArrowComponent* Arrow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UMyActorComponent* MyActorComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Component")
	UFloatingPawnMovement* FloatingPawnMovement;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset")
	UStaticMesh* BodyMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset")
	UStaticMesh* LeftMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Asset")
	UStaticMesh* RightMesh;
	
public:
	float BoostValue;
};
