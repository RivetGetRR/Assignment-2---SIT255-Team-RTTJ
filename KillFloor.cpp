// Fill out your copyright notice in the Description page of Project Settings.

#include "KillFloor.h"
#include "GameFramework/Actor.h"
#include "BasicEnemy.h"


// Sets default values
AKillFloor::AKillFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the Static Mesh component for the main body and set it as the RootComponent
	MainFloor = CreateDefaultSubobject<UStaticMeshComponent>("Main Body");
	RootComponent = MainFloor;

	//Create Box collision for Enenmy and attach it to main body mesh EnemyBody
	FloorColi = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	FloorColi->SetupAttachment(MainFloor);

	
}

// Called when the game starts or when spawned
void AKillFloor::BeginPlay()
{
	Super::BeginPlay();
	
	//Make sure that the Collision Box produces an event upon collsion -> Attaches the function to this component
	FloorColi->OnComponentBeginOverlap.AddDynamic(this, &AKillFloor::OnOverlapBegin);
}

// Called every frame
void AKillFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//Function Called when BoxColi overlapps with another actor
void AKillFloor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	//Destroys the actor it comes into contact with
		OtherActor->Destroy();
		UE_LOG(LogTemp, Log, TEXT("Object Deleted by Kill Floor"));
}