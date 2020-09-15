// Fill out your copyright notice in the Description page of Project Settings.

#include "DropPlatformNew.h"
#include "EngineUtils.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MainPlatChar.h"
#include "DropPlatformNew.h"

// Sets default values
ADropPlatformNew::ADropPlatformNew()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Creates the Static Mesh component for the main body and set it as the RootComponent
	DPlatform = CreateDefaultSubobject<UStaticMeshComponent>("PlatformBody");
	RootComponent = DPlatform;


	//Create Box collision for Enenmy and attach it to main body mesh EnemyBody
	BoxColi = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	BoxColi->SetupAttachment(DPlatform);
	

	//Initialise the countdown before dropping
	DropCountDown = 4;
}

// Called when the game starts or when spawned
void ADropPlatformNew::BeginPlay()
{
	Super::BeginPlay();
	
	BoxColi->OnComponentBeginOverlap.AddDynamic(this, &ADropPlatformNew::OnOverlapBegin);
	GetWorldTimerManager().SetTimer(DropperTH, this, &ADropPlatformNew::UpdateTimer, 1.0f, true);

	
}

// Called every frame
void ADropPlatformNew::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DropNow) {
		DropDown();
	}
}
//Advances Timer 
void ADropPlatformNew::UpdateTimer() {
	if (Activated) {
		--DropCountDown;
		if (DropCountDown < 1) {
			//Once Timer Is complete the DropNow is set to true: Actor commanded to fall
			DropNow = true;
		}
	}

}

void ADropPlatformNew::DropDown() {
	//Drops this amount every tick, does this beacuse it is called under the Tick Function
	 SetActorLocation(GetActorLocation() - FVector(0.0f, 0.0f, 5.0f)); //reduced height is set to Actor
	 

	/*
	 //Original Method of destroying Actor after Dropping
	 if (Holder.Z < -20.0f) {
		 DropNow = false;
		 DroppingFinished();

	 }
	 */
}

//No longer really required due to implementation of Kill Floor
void ADropPlatformNew::DroppingFinished() {
	ADropPlatformNew::Destroy();
}

//OverLap Begins this is called
void ADropPlatformNew::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	//Once Overlapped, it will allow the countdown to decrease/Advance
	//Casting to check whether the actor is of the correct Class: MainPlatChar
	AMainPlatChar* ACTOR = Cast<AMainPlatChar>(OtherActor);
	if (ACTOR != nullptr) {
		UE_LOG(LogTemp, Log, TEXT("Triggered By Player, Now Falling")); //Message To indicate this
		Activated = true;
	}

}