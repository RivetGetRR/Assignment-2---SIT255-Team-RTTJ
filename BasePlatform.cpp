// Fill out your copyright notice in the Description page of Project Settings.

#include "BasePlatform.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ABasePlatform::ABasePlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the Static Mesh component for the main body and set it as the RootComponent
	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("Main_Platform");
	RootComponent = PlatformMesh;
}

// Called when the game starts or when spawned
void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

