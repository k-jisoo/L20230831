// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	RootComponent = Box;
	Box->SetBoxExtent(FVector(20.0f, 20.0f, 20.0f));
	Box->SetGenerateOverlapEvents(true);

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	Body->SetupAttachment(RootComponent);

	Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Movement"));
	Movement->ProjectileGravityScale = 0;
	Movement->InitialSpeed = 2000.0f;
	Movement->MaxSpeed = 2000.0f;
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(3.0f);

	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessBeginOverlap);
	OnActorBeginOverlap.AddDynamic(this, &AMyActor::ProcessBeginOverlap);
	OnActorBeginOverlap.RemoveDynamic(this, &AMyActor::ProcessBeginOverlap);

}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

void AMyActor::ProcessBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
}

/// <summary>
/// BP에서 구현 안되어있으면 CPP 호출. 구현되어있으면 BP만 호출
/// BP에서 부모 함수 호출을 연결하면 CPP도 호출 가능
/// </summary>
void AMyActor::CallCppToBlueIsNotValidBpCpp_Implementation()
{
}

