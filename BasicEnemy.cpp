// Fill out your copyright notice in the Description page of Project Settings.

#include "BasicEnemy.h"
#include "Math/UnrealMathUtility.h"
#include "Components/PrimitiveComponent.h"
#include "KillFloor.h"
#include "MainPlatChar.h"


// Sets default values
ABasicEnemy::ABasicEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Creates the Static Mesh component for the main body and set it as the RootComponent
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>("Enemy Body");
	RootComponent = EnemyBody;

	//Causes EnemyBody to be affected by the Unreal Physics Engine
	EnemyBody->SetSimulatePhysics(true);

 	//Create Box collision for Enenmy and attach it to main body mesh EnemyBody
	EnemyColi = CreateDefaultSubobject<UBoxComponent>("Collision Box");
	EnemyColi->SetupAttachment(EnemyBody);
}

// Called when the game starts or when spawned
void ABasicEnemy::BeginPlay()
{
	Super::BeginPlay();
	//Function run once Decide which direction the Enemy will Move in
	MovementTo();
	EnemyColi->OnComponentBeginOverlap.AddDynamic(this, &ABasicEnemy::OnOverlapBegin);
}

// Called every frame
void ABasicEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Moving();
}


//Determines Movement Cycle/Direction through a randomized number (Not Hard Coded)
void ABasicEnemy::MovementTo() {
	
	//Randomizes int32 value then chooses a direction through the given number
	//Number checked using a switch-case statement
	SetDirection = FMath::RandRange(-1, 2); 
	//Uses MovingAs to change Direction
	switch (SetDirection)
	{
		case -1: MovingAs = FVector(4.0f,0.0f,0.0f);
			break;

		case 0: MovingAs = FVector(-4.0f, 0.0f, 0.0f);
			break;

		case 1: MovingAs = FVector(0.0f, 4.0f, 0.0f);
			break;

		case 2: MovingAs = FVector(0.0f, -4.0f, 0.0f);
			break;

	default:

		//Does when during an error or others Fail
		UE_LOG(LogTemp, Log, TEXT("Switch Case Statement for A Basic Enemy has Failed"));	
		break;
	}
}
void ABasicEnemy::Moving() {

	//Moves the actor along an axis, X or Y
	SetActorLocation(GetActorLocation() + MovingAs);
}

void ABasicEnemy::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	
	//Deactivates itself if it comes into contact with the player or th kill floor
	AMainPlatChar* Player = Cast<AMainPlatChar>(OtherActor);
	if (Player != nullptr) {
		Destroy();
	}
	
}