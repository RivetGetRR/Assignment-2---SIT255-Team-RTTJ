// Fill out your copyright notice in the Description page of Project Settings.

#include "AdvancedEnemy.h"
#include "MainPlatChar.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
AAdvancedEnemy::AAdvancedEnemy() {
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Creates the Static Mesh component for the main body and set it as the RootComponent
	AEnemyBody = CreateDefaultSubobject<UStaticMeshComponent>("Enemy Body");
	RootComponent = AEnemyBody;

	//Create Box collision for Enenmy and attach it to main body mesh AEnemyBody
	AEnemyColi = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	AEnemyColi->SetupAttachment(AEnemyBody);

	//Causes AEnemyBody to be affected by the Unreal Physics Engine
	AEnemyBody->SetSimulatePhysics(true);

	//Set Up Timer for change
	MovementDelay = 5;
}

// Called when the game starts or when spawned
void AAdvancedEnemy::BeginPlay() {
	
	Super::BeginPlay();
	//Make sure that the Collision Box produces an event upon collsion -> Attaches the function to this component
	AEnemyColi->OnComponentBeginOverlap.AddDynamic(this, &AAdvancedEnemy::OnOverlapBegin);
	//Set Up the Timer proper/Start it
	GetWorldTimerManager().SetTimer(MoveTimer, this, &AAdvancedEnemy::UpdateTimer, 1.0f, true);
}

// Called every frame
void AAdvancedEnemy::Tick(float DeltaTime) {
	
	Super::Tick(DeltaTime);
	//Move Actor According to set direction
	Moving();
	
	
}

// Called to bind functionality to input
void AAdvancedEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent){
	
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AAdvancedEnemy::MoveTo() {

	//Randomizes int32 value then chooses a direction through the given number
	//Number checked using a switch-case statement
	switch (FMath::RandRange(-1, 2)){
		//Uses MovingWith to change Direction
	case -1: MovingWith = FVector(4.0, 0.0f, 0.0f);
		break;

	case 0:  MovingWith = FVector(-4.0, 0.0f, 0.0f);
		break;

	case 1:  MovingWith = FVector(0.0, 4.0f, 0.0f);
		break;

	case 2:  MovingWith = FVector(0.0f, -4.0f, 0.0f);
		break;

	default:

		//Does when during an error or others Fail
		UE_LOG(LogTemp, Log, TEXT("Switch Case Statement for An Advanced Enemy has Failed"));
		break;
	}
}

void AAdvancedEnemy::UpdateTimer() {
	--MovementDelay;
	//When MovementDelay Reaches Zero
	if (MovementDelay < 1) {

		CountDownFinished();
	}

}

void AAdvancedEnemy::CountDownFinished() {
	
	MoveTo();
	//Resets Timer with a random inrange number
	MovementDelay = FMath::RandRange(3, 6);
}


void AAdvancedEnemy::Moving() {
	//Moves the actor along an axis, X or Y
	SetActorLocation(GetActorLocation() + MovingWith);
}

void AAdvancedEnemy::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	//Destroys itself only if it comes into contact with the player
	AMainPlatChar* Player = Cast<AMainPlatChar>(OtherActor);
	if (Player != nullptr) {
		//Destroys Actor
		Destroy();
	}

}