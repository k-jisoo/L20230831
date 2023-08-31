// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"	
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "MyActorComponent.h"
#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MyActor.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	SetRootComponent(Box);
	Box->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(Box);
	Body->SetStaticMesh(BodyMesh);

	Left = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Left"));
	Left->SetupAttachment(Body);
	Left->SetStaticMesh(LeftMesh);
	Left->SetRelativeLocation(FVector(37.257852f, -21.f, 0.986638f));

	Right = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Right"));
	Right->SetupAttachment(Body);
	Right->SetStaticMesh(RightMesh);
	Right->SetRelativeLocation(FVector(37.257852f, 21.f, 0.986638f));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(Box);
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->bDrawDebugLagMarkers = true;
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 30.0f);


	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(Box);

	MyActorComponent = CreateDefaultSubobject<UMyActorComponent>(TEXT("MyActorComponent"));
	MyActorComponent->RotatingMeshes.Add(Left);
	MyActorComponent->RotatingMeshes.Add(Right);

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("FloatingPawnMovement"));

	BoostValue = 0.5f;
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddMovementInput(GetActorForwardVector(), BoostValue);
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	if (EnhancedInputComponent) 
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		PlayerInputComponent->BindAxis(TEXT("Pitch"), this, &AMyPawn::Pitch);
		PlayerInputComponent->BindAxis(TEXT("Roll"), this, &AMyPawn::Roll);

		PlayerInputComponent->BindAction(TEXT("Boost"), IE_Pressed, this, &AMyPawn::Boost);
		PlayerInputComponent->BindAction(TEXT("Boost"), IE_Released, this, &AMyPawn::UnBoost);
		PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AMyPawn::Fire);
	}
	else 
	{
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedBoost);
		EnhancedInputComponent->BindAction(IA_Boost, ETriggerEvent::Completed, this, &AMyPawn::EnhancedUnBoost);

		EnhancedInputComponent->BindAction(IA_Fire, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedFire);

		EnhancedInputComponent->BindAction(IA_PitchAndRoll, ETriggerEvent::Triggered, this, &AMyPawn::EnhancedPitchAndRoll);
	}
}

void AMyPawn::Pitch(float Value)
{
	AddActorLocalRotation(FRotator(Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f, 0, 0));
}

void AMyPawn::Roll(float Value)
{
	AddActorLocalRotation(FRotator(0,0, Value * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f));
}

void AMyPawn::Fire()
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(RocketTemplate, Arrow->GetComponentLocation(), Arrow->GetComponentRotation());
}

void AMyPawn::Boost()
{
	BoostValue = 1.0f;
}

void AMyPawn::UnBoost()
{
	BoostValue = 0.5f;
}

void AMyPawn::EnhancedBoost(const FInputActionValue& Value)
{
	BoostValue = 1.0f;
}

void AMyPawn::EnhancedUnBoost(const FInputActionValue& Value)
{
	BoostValue = 0.5f;
}

void AMyPawn::EnhancedFire(const FInputActionValue& Value)
{
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(RocketTemplate, Arrow->GetComponentLocation(), Arrow->GetComponentRotation());
}

void AMyPawn::EnhancedPitchAndRoll(const FInputActionValue& Value)
{
	FVector2D VectorValue = Value.Get<FVector2D>();

	AddActorLocalRotation(FRotator(VectorValue.X * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f, 0, VectorValue.Y * UGameplayStatics::GetWorldDeltaSeconds(GetWorld()) * 60.0f));
}

